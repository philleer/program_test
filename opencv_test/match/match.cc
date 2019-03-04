#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
	Mat image1 = imread(argv[1]);
	Mat image2 = imread(argv[2]);
	
	resize(image1, image1, Size(image1.cols*0.3, image1.rows*0.3), INTER_LINEAR);
	resize(image2, image2, Size(image2.cols*0.3, image2.rows*0.3), INTER_LINEAR);
	
	Mat gray1 = image1.clone();
	Mat gray2 = image2.clone();
	cvtColor(image1, gray1, CV_BGR2GRAY);
	cvtColor(image2, gray2, CV_BGR2GRAY);

	// surf
	Ptr<Feature2D> target = xfeatures2d::SURF::create(600);
	vector<KeyPoint> kp1, kp2;
	target->detect(gray1, kp1);
	target->detect(gray2, kp2);

	Mat des1, des2;
	target->compute(gray1, kp1, des1);
	target->compute(gray2, kp2, des2);

	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	vector<vector<DMatch> > matchpoints;
	vector<Mat> train_desc(1, des1);
	matcher.add(train_desc);
	matcher.train();
	matcher.knnMatch(des1, des2, matchpoints, 2);
		
	cout << "surf total match points: " << matchpoints.size() << endl;

	for ( size_t i = 0; i < matchpoints.size(); i++ )
	{
		if(matchpoints[i][0].distance < 0.4 * matchpoints[i][1].distance)
		{
				matches.push_back(matchpoints[i][0]);
		}
	}

	// matcher.match(des1, des2, matches);
	// nth_element(matches.begin(), matches.begin()+29, matches.end());
	// matches.erase(matches.begin()+30, matches.end());

	Mat result;
	drawMatches(image1, kp1, image2, kp2, matches, result);
	imshow("surf_result", result);
	imwrite("surf_match.jpg", result);

	//=============== sift ===============//
	Ptr<Feature2D> tarsift = xfeatures2d::SIFT::create(600);
	vector<KeyPoint> sikp1, sikp2;
	tarsift->detect(gray1, sikp1);
	tarsift->detect(gray2, sikp2);
	Mat sides1, sides2;
	target->compute(gray1, sikp1, sides1);
	target->compute(gray2, sikp2, sides2);

	FlannBasedMatcher simatcher;
	vector<vector<DMatch> > simatchpoints;
	vector<DMatch> simatches;
	vector<Mat> sitrain_desc(1, sides1);
	simatcher.add(sitrain_desc);
	simatcher.train();

	simatcher.knnMatch(sides1, sides2, simatchpoints, 2);
	cout << "sift total match points: " << simatchpoints.size() << endl;
	for (size_t i = 0; i < simatchpoints.size(); i++)
	{
			if(simatchpoints[i][0].distance < 0.4 * simatchpoints[i][1].distance)
			{
					simatches.push_back(simatchpoints[i][0]);
			}
	}
	Mat siresult;
	drawMatches(image1, sikp1, image2, sikp2, simatches, siresult);
	imshow("sift match", siresult);
	imwrite("sift_result.jpg", siresult);

	//=============== orb ===============//
	Ptr<ORB> tarorb = ORB::create(680);
	vector<KeyPoint> orbkp1, orbkp2;
	Mat orbdes1, orbdes2;
	tarorb->detect(gray1, orbkp1);
	tarorb->detect(gray2, orbkp2);
	tarorb->compute(gray1, orbkp1, orbdes1);
	tarorb->compute(gray2, orbkp2, orbdes2);

	cv::flann::Index flannIndex(orbdes1, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);
	vector<DMatch> orbmatches;
	Mat matchIndex(orbdes2.rows, 2, CV_32SC1), matchDistance(orbdes2.rows, 2, CV_32FC1);
	flannIndex.knnSearch(orbdes2, matchIndex, matchDistance, 2, flann::SearchParams());

	for (int i = 0; i < matchDistance.rows; i++)
	{
			if(matchDistance.at<float>(i,0) < 0.4 * matchDistance.at<float>(i, 1))
			{
					DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
					orbmatches.push_back(dmatches);
			}
	}
	Mat orbresult;
	drawMatches(image1, orbkp1, image2, orbkp2, orbmatches, orbresult);
	imshow("orb match", orbresult);
	imwrite("orb_result.jpg", orbresult);

	//=============== harris ===============//
	vector<Point2f> corners;
	int max_corners = 100;
	double quality_level = 0.01;
	double min_distance = 10;
	int block_size = 3;
	bool use_harris = false;
	double k = 0.04;
	goodFeaturesToTrack(gray1, corners, max_corners, quality_level, min_distance, Mat(), block_size, use_harris, k);
	TermCriteria criteria = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 40, 0.01);

	cornerSubPix(gray1, corners, Size(5, 5), Size(-1, -1), criteria);
	Mat imagecopy = image1.clone();
	for (size_t i = 0; i < corners.size(); i++)
	{
		circle(image1, corners[i], 5, cv::Scalar(0, 255, 0), 2, 8, 0);
	}
	
	vector<Point2f> corners2;
	goodFeaturesToTrack(gray2, corners2, max_corners, quality_level, min_distance, Mat(), block_size, use_harris, k);
	cornerSubPix(gray2, corners2, Size(5, 5), Size(-1, -1), criteria);
	for (size_t i = 0; i < corners2.size(); i++)
	{
		circle(image2, corners2[i], 5, cv::Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("subpixel corner", image1);
	imshow("subpixel corner2", image2);
	/** TODO **/
	// harris corner detection and matching
	
	/*
	Ptr<FastFeatureDetector> tarhar = FastFeatureDetector::create(600);
	vector<KeyPoint> harkp1, harkp2;
	Mat hardes1, hardes2;
	tarhar->detect(gray1, harkp1);
	tarhar->detect(gray2, harkp2);

	xfeatures2d::SiftDescriptorExtractor Descriptor;
	Descriptor.compute(gray1, harkp1, hardes1);
	Descriptor.compute(gray2, harkp2, hardes2);
	BFMatcher harmatcher;
	vector<vector<DMatch> > harmatchpoints;
	vector<DMatch> harmatches;
	vector<Mat> hartrain_desc(1, hardes1);
	harmatcher.add(hartrain_desc);
	harmatcher.train();
	harmatcher.knnMatch(hardes1, hardes2, harmatchpoints, 2);
	cout << "harris total match points: " << harmatchpoints.size() << endl;

	for (size_t i = 0; i < harmatchpoints.size(); i++)
	{
			if(harmatchpoints[i][0].distance < 0.4 * harmatchpoints[i][1].distance)
			{
					harmatches.push_back(harmatchpoints[i][0]);
			}

	}

	Mat harresult;
	drawMatches(image1, harkp1, image2, harkp2, harmatches, harresult);
	imshow("harris match", harresult);
	*/

	waitKey(0);
	return 0;
}
