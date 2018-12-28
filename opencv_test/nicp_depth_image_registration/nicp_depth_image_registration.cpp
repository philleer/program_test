#include <iostream>

#include <opencv2/highgui/highgui.hpp>

#include <nicp/imageutils.h>
#include <nicp/pinholepointprojector.h>
#include <nicp/depthimageconverterintegralimage.h>
#include <nicp/statscalculatorintegralimage.h>
#include <nicp/alignerprojective.h>

int main(int argc, char **argv) {
  // Print usage
  if(argc < 4) {
    std::cout << "USAGE: ";
    std::cout << "nicp_depth_image_registration referenceDepthFilename currentDepthFilename imageScaling" << std::endl;
    std::cout << "   referenceDepthFilename [string] \t-->\t input reference depth image" << std::endl;
    std::cout << "   currentDepthFilename   [string] \t-->\t input depth image to register" << std::endl;
    std::cout << "   imageScaling              [int] \t-->\t scaling factor to apply to the input depth images" << std::endl;
    return 0;
  }
  std::string referenceDepthFilename = std::string(argv[1]);
  std::string currentDepthFilename = std::string(argv[2]);
  float imageScaling = atof(argv[3]);
  if(imageScaling <= 0.0f) {
    std::cout << std::endl << "ERROR: image scaling factor can not be <= 0" << std::endl;
    return 0;
  }
  if(imageScaling > 2.0f) {
    std::cout << std::endl
	      << "WARNING: big image scaling factor could lead to a bad "
	      << "registration result, in particualr if the distance between "
	      << "the two point clouds to align is not small enough" << std::endl;
  }

  Eigen::Matrix3f cameraMatrix;
  cameraMatrix <<
    525.0f,   0.0f, 319.5f,
      0.0f, 525.0f, 239.5f,
      0.0f,   0.0f,   1.0f;

  // Create the PinholePointProjector
  nicp::PinholePointProjector pointProjector;
  pointProjector.setMinDistance(0.01f);
  pointProjector.setMaxDistance(4.5f);
  pointProjector.setCameraMatrix(cameraMatrix);
  pointProjector.setImageSize(480, 640);
  pointProjector.setTransform(Eigen::Isometry3f::Identity());
  pointProjector.scale(1.0f / imageScaling);

  // Create StatsCalculator and InformationMatrixCalculator
  nicp::StatsCalculatorIntegralImage statsCalculator;
  nicp::PointInformationMatrixCalculator pointInformationMatrixCalculator;
  nicp::NormalInformationMatrixCalculator normalInformationMatrixCalculator;

  statsCalculator.setMinImageRadius(20 / imageScaling);
  statsCalculator.setMaxImageRadius(40 / imageScaling);
  statsCalculator.setMinPoints(40 / imageScaling);
  statsCalculator.setCurvatureThreshold(0.2f);
  statsCalculator.setWorldRadius(0.1f);

  pointInformationMatrixCalculator.setCurvatureThreshold(0.02f);

  normalInformationMatrixCalculator.setCurvatureThreshold(0.02f);

  // Create DepthImageConverter
  nicp::DepthImageConverterIntegralImage converter(&pointProjector, &statsCalculator,
						  &pointInformationMatrixCalculator,
						  &normalInformationMatrixCalculator);

  // Create CorrespondenceFinder
  nicp::CorrespondenceFinderProjective correspondenceFinder;
  correspondenceFinder.setImageSize(pointProjector.imageRows(), pointProjector.imageCols());
  correspondenceFinder.setInlierDistanceThreshold(0.5f);
  correspondenceFinder.setInlierNormalAngularThreshold(0.95f);
  correspondenceFinder.setFlatCurvatureThreshold(0.02f);

  // Create Linearizer and Aligner
  nicp::Linearizer linearizer;
  nicp::AlignerProjective aligner;

  linearizer.setInlierMaxChi2(9e3);
  linearizer.setRobustKernel(true);
  linearizer.setZScaling(true);
  linearizer.setAligner(&aligner);

  aligner.setOuterIterations(10);
  aligner.setLambda(1e3);
  aligner.setProjector(&pointProjector);
  aligner.setCorrespondenceFinder(&correspondenceFinder);
  aligner.setLinearizer(&linearizer);

  // Get clouds from depth images
  Eigen::Isometry3f initialGuess = Eigen::Isometry3f::Identity();
  Eigen::Isometry3f sensorOffset = Eigen::Isometry3f::Identity();
  nicp::RawDepthImage rawDepth;
  nicp::DepthImage depth, scaledDepth;
  nicp::Cloud referenceCloud, currentCloud, globalCloud;

  rawDepth = cv::imread(referenceDepthFilename, -1);
  if(!rawDepth.data) {
    std::cerr << "Error: impossible to read image file " << referenceDepthFilename << std::endl;
    return -1;
  }
  nicp::DepthImage_convert_16UC1_to_32FC1(depth, rawDepth, 0.001f);
  nicp::DepthImage_scale(scaledDepth, depth, imageScaling);
  converter.compute(referenceCloud, scaledDepth, sensorOffset);

  rawDepth = cv::imread(currentDepthFilename, -1);
  if(!rawDepth.data) {
    std::cerr << "Error: impossible to read image file " << currentDepthFilename << std::endl;
    return -1;
  }
  nicp::DepthImage_convert_16UC1_to_32FC1(depth, rawDepth, 0.001f);
  nicp::DepthImage_scale(scaledDepth, depth, imageScaling);
  converter.compute(currentCloud, scaledDepth, sensorOffset);

  // Perform the registration
  aligner.setReferenceCloud(&referenceCloud);
  aligner.setCurrentCloud(&currentCloud);
  aligner.setInitialGuess(initialGuess);
  aligner.setSensorOffset(sensorOffset);
  aligner.align();

  // Write the result
  Eigen::Isometry3f T = aligner.T();
  std::cout << std::endl << "Transformation: " << std::endl << T.matrix() << std::endl;
  referenceCloud.save("reference_cloud.nicp", Eigen::Isometry3f::Identity(), 1, true);
  currentCloud.save("current_cloud.nicp", Eigen::Isometry3f::Identity(), 1, true);
  globalCloud.add(referenceCloud, Eigen::Isometry3f::Identity());
  globalCloud.add(currentCloud, T);
  globalCloud.save("global_cloud.nicp", Eigen::Isometry3f::Identity(), 1, true);

  return 0;
}
