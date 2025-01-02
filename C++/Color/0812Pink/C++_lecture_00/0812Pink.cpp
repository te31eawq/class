#include <iostream>
#include <string>
#include "ColorDefineh.h"

int main()
{
	std::cout << "Hello World!\n";
	int a = 10;
	int b = 20;
	int c = a + b;

	cv::Mat img = cv::Mat::zeros(100, 100, CV_8UC1);
	cv::Mat colorImage = cv::imread("Images\\Audrey.jpg", cv::ImreadModes::IMREAD_UNCHANGED);

	std::string nameWindow = "Show";
	cv::namedWindow(nameWindow, cv::WindowFlags::WINDOW_NORMAL);
	cv::resizeWindow(nameWindow, 600, 800);
	cv::imshow(nameWindow, colorImage);
	cv::waitKey();
	cv::destroyAllWindows();
	return 1;
}

