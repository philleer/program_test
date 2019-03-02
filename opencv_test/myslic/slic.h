#ifndef SLIC_H
#define SLIC_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>

#define vec2dd std::vector<std::vector<double> >
#define vec2di std::vector<std::vector<int> >
#define vec2db std::vector<std::vector<bool> >
#define NR_ITERATIONS 10

class Slic {
	private:
		/* The cluster assignments and distance values for each pixel. */
		vec2di clusters;
		vec2dd distances;

		/* The LAB and xy values of the centers. */
		vec2dd centers;
		/* The number of occurences of each center. */
		std::vector<int> center_counts;

		/* The step size per cluster, and the colour (nc) and distance (ns)
         * parameters. */
		int step, nc, ns;

		/* Compute the distance between a center and an individual pixel. */
		double compute_dist(int ci, cv::Point pixel, cv::Scalar colour);
		cv::Point find_local_minimum(cv::Mat image, cv::Point center);

		/* Remove and initialize the 2d vectors. */
		void clear_data();
		void init_data(cv::Mat image);

	public:
		/* Class constructors and deconstructors. */
		Slic();
		~Slic();

		/* Generate an over-segmentation for an image. */
		void generate_superpixels(cv::Mat image, int step, int nc);
		/* Enforce connectivity for an image. */
		void create_connectivity(cv::Mat image);
		
		/* Draw functions. Resp. displayal of the centers and the contours. */
		void display_center_grid(cv::Mat image, cv::Scalar colour);
		void display_contours(cv::Mat, cv::Scalar colour);
		void colour_with_cluster_means(cv::Mat image);
};

#endif /* ifndef SLIC_H */
