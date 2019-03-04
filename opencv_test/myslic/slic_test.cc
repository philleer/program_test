#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include "slic.h"

int main (int argc, char * argv[]) {
	if ( argc < 4 ) {
		std::cerr << "Input not right!\n"
				<< "./myslic path_to_image number_of_superpixels quality path_to_svae_result" << std::endl;
	}

	cv::Mat image = cv::imread(argv[1], 1);
	while(image.cols > 1000)
		cv::resize(image, image, cv::Size(image.cols * 0.5, image.rows * 0.5), CV_INTER_LINEAR);
	cv::Mat lab_image = image.clone();
	cv::cvtColor(image, lab_image, CV_BGR2Lab);

	int w = image.cols, h = image.rows;
	int nr_supperpixels = atoi(argv[2]);
	int nc = atoi(argv[3]);
	double step = sqrt((w * h) / (double) nr_supperpixels);

	Slic slic;
	slic.generate_superpixels(lab_image, step, nc);
	slic.create_connectivity(lab_image);

	cv::Mat image_clone = image.clone();	
	slic.display_contours(image_clone, CV_RGB(255, 0, 0));


	// cd build && ./myslic ../temple0040.png 2000 256 ./result_temple.png
	// if (image.cols > 799) {
	// 	int scale = 800 / image.cols;
	// 	cv::resizeWindow("result", image.cols * scale, image.rows * scale);
	// }
	cv::imshow("result", image_clone);
	cv::waitKey(0);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(100);
	cv::imwrite("a15result_cache.jpg", image_clone, compression_params);
	slic.colour_with_cluster_means(image);
	cv::imwrite(argv[4], image, compression_params);

	return 0;
}
