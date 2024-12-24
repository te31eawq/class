// pink.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "ColorDefineh.h"
#include <algorithm>
#define PIXEL_WHITE 255
#define PIXEL_BLACK 0
using namespace cv;


/*
	cv::Mat
		//! pointer to the data
		uchar* data;
*/


/////////////////////
//  typedef Point2i Point;		// in cv::mat.hpp


void DrawLine(Point pt1, Point pt2, cv::Mat& img) {
	cv::Size size = img.size();
	int width = size.width;
	int height = size.height;
	uchar* pData = img.data;

	// draw horizontal.
	if (pt1.x != pt2.x && pt1.y == pt2.y) {
		const int y_offset_value = pt1.y * width;
		if (pt1.x < pt2.x) { // draw horizontal - left to right
			for (int x = pt1.x; x <= pt2.x; x++) {
				pData[y_offset_value + x] = PIXEL_WHITE;
			}
		}
		else { // draw horizontal - right to left
			for (int x = pt1.x; x >= pt2.x; x--) {
				pData[y_offset_value + x] = PIXEL_WHITE;
			}
		}
	}
	// draw vertical.
	else if (pt1.x == pt2.x && pt1.y != pt2.y) {
		const int x_offset_value = pt1.x;
		if (pt1.y < pt2.y) { // draw vertical - top to bottom
			for (int y = pt1.y; y <= pt2.y; y++) {
				pData[y * width + x_offset_value] = PIXEL_WHITE;
			}
		}
		else { // draw vertical - bottom to top
			for (int y = pt1.y; y >= pt2.y; y--) {
				pData[y * width + x_offset_value] = PIXEL_WHITE;
			}
		}
	}
	else
	{
		std::cout << "Invalid to draw";
	}

	std::cout << "pt1=" << pt1.x << "," << pt1.y << " ----> " << "pt2=" << pt2.x << "," << pt2.y << std::endl;
}

int main()
{
	{

		const int width = 10;
		const int height = 10;
		cv::Mat img = cv::Mat::zeros(width, height, CV_8UC1);
		Point pt[4] = { Point(0,0),Point(width - 1,0),Point(width - 1,height - 1),Point(0,height - 1) };
		//cv::Mat img = cv::Mat::zeros(100, 100, CV_8UC1);
		//Point pt[4] = { Point(1,1),Point(100,1),Point(100,100),Point(1,100) };

		size_t pt_size = _countof(pt);
		//pt_size = sizeof(pt_size) / (sizeof(Point));

		for (size_t i = 0; i < pt_size; i++) {
			DrawLine(pt[i], pt[(i + 1) % pt_size], img);
		}

	}
	const int width = 100;
	const int height = 100;
	cv::Mat img = cv::Mat::zeros(width, height, CV_8UC1);
	cv::Mat img_rect = cv::Mat::zeros(width, height, CV_8UC1);

	int gap = 10;
	cv::Point pt[4] = { Point(0 + gap,0 + gap),
		Point(width - 1 - gap,0 + gap),
		Point(width - 1- gap,height - 1- gap),
		Point(0+ gap,height - 1- gap) };
	size_t pt_size = _countof(pt);
	for (size_t i = 0; i < pt_size; i++) {
		cv::line(img, pt[i], pt[(i + 1) % pt_size], cv::Scalar(255));
	}

	cv::rectangle(img_rect,
		cv::Rect(Point(0 + gap, 0 + gap), Point(width - 1 - gap, height - 1 - gap)),
		cv::Scalar(255));


	return 0;


}
