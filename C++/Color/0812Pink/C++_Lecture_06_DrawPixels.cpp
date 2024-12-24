
#include <iostream>
#include <string>
#include "ColorDefineh.h"

int main()
{
	//cv::Mat colorImage = cv::imread("Images\\Audrey.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
	int rows = 400;
	int cols = 600;
	cv::Mat img = cv::Mat::zeros(rows, cols, CV_8UC1);


	uchar* pImg = img.data;
	int width_step = cols;
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			size_t idx = row * width_step + col;
			if (row == col)
				pImg[idx] = row;
			if (width_step - col == row)
				pImg[idx] = row;
		}
	}

	return 1;
}