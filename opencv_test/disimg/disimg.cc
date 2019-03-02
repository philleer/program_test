#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

std::string filename;
cv::Mat image;
std::string winName = "show";
std::string savename;

enum {
	NOT_SET = 0,
	IN_PROCESS = 1,
	SET = 2
};

uchar rectState;
cv::Rect rect;
cv::Mat mask;
const cv::Scalar GRE(0, 255, 0);
cv::Mat bgdModel, fgdModel;

void setRectInMask() {
	rect.x = std::max(0, rect.x);
	rect.y = std::max(0, rect.y);
	rect.width = std::min(rect.width, image.cols - rect.x);
	rect.height = std::min(rect.height, image.rows - rect.y);
}

static void getBinMask( const cv::Mat& comMask, cv::Mat& binMask ) {
	binMask.create(comMask.size(), CV_8UC1);
	binMask = comMask & 1;
}

void on_mouse (int event, int x, int y, int flags, void*) {
	cv::Mat res;
	cv::Mat binMask;

	switch (event) 
	{
			case CV_EVENT_LBUTTONDOWN:
					if(rectState == NOT_SET) {
							rectState = IN_PROCESS;
							rect = cv::Rect(x, y, 1, 1);
					}
					break;
			case CV_EVENT_LBUTTONUP:
					if(rectState == IN_PROCESS) {
							rect = cv::Rect(cv::Point(rect.x, rect.y), cv::Point(x, y));
							rectState = SET;
							(mask(rect)).setTo(cv::Scalar(cv::GC_PR_FGD));
							cv::Mat img = cv::imread(filename, 1);
							float ratio = 600.0 / std::max(img.cols, img.rows);
							cv::resize(img, image, cv::Size((int)(img.cols * ratio), (int)(img.rows * ratio)), cv::INTER_LINEAR);cv::grabCut(image, mask, rect, bgdModel, fgdModel, 1, cv::GC_INIT_WITH_RECT);
							getBinMask(mask, binMask);
							image.copyTo(res, binMask);
							cv::imshow("11", res);
							// cv::imwrite("result_fg.png", res);
							cv::imwrite(savename, res);

					}
					break;
			case CV_EVENT_MOUSEMOVE:
					if(rectState == IN_PROCESS) {
							rect = cv::Rect(cv::Point(rect.x, rect.y), cv::Point(x, y));
							cv::Mat img = cv::imread(filename, 1);
							float ratio = 600.0 / std::max(img.cols, img.rows);
							cv::resize(img, image, cv::Size((int)(img.cols * ratio), (int)(img.rows * ratio)), cv::INTER_LINEAR);
							cv::rectangle(image, cv::Point(rect.x, rect.y), cv::Point(rect.x+rect.width, rect.y+rect.height), GRE, 2);
							cv::imshow(winName, image);
					}
					break;
			default:break;	
	}
}

int main(int argc, const char** argv)
{
	if (argc < 3) {
		std::cout << "usage: ./disimg <Image_Path>" << std::endl;
		return -1;
	}

	filename = argv[1];
	savename = argv[2];
	std::cout << savename << std::endl;
	cv::Mat img = cv::imread(filename, 1);
	float ratio = 600.0 / std::max(img.cols, img.rows);
	cv::resize(img, image, cv::Size((int)(img.cols * ratio), (int)(img.rows * ratio)), cv::INTER_LINEAR);
	cv::imshow(winName, image);
	mask.create(image.size(), CV_8UC1);
	rectState = NOT_SET;
	mask.setTo(cv::GC_BGD);

	cv::setMouseCallback(winName, on_mouse, 0);
	// cv::imwrite(argv[2], image);
	// cv::imshow("display image", img);
	cv::waitKey(0);
	return 0;
}

