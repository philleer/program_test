#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(int argc, const char** argv)
{
	if (argc != 2) {
		std::cout << "usage: ./disimg <Image_Path>" << std::endl;
		return -1;
	}

//	auto str = "Hello world!";
//	std::cout << "The type of str: " << decltype(str)() << std::endl;

	cv::Mat img = cv::imread( argv[1], 1 );

	if (!img.data) {
		std::cout << "No image data." << std::endl;
		return -1;
	}

	cv::namedWindow("disimg", cv::WINDOW_AUTOSIZE);
	cv::imshow("display image", img);
	cv::waitKey(0);

	return 0;
}

