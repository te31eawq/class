#include <iostream>
#include <string>
#include "ColorDefineh.h"

int main()
{

	//cv::Mat colorImage = cv::imread("Images\\Audrey.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
	int rows = 100;
	int cols = 100;

	cv::Mat img = cv::Mat::zeros(rows, cols, CV_8UC1);



	uchar* pData = img.data; // array start address
	int width = cols; // array width size
	int height = rows; // array height size
	size_t start_row = (rows / 4) - 1;
	size_t start_col = (cols / 4) - 1;
	size_t finish_row = (rows - (rows / 4))-1;
	size_t finish_col = (cols - (cols / 4))-1;

	for (size_t row = start_row; row <= finish_row; row++)
	{
		for (size_t col = start_col; col <= finish_col; col++)
		{
			size_t index = col + row * width;
			if (row == start_row || row == finish_row || col == start_col || col == finish_col)
			{
				pData[index] = 255;
			}
		}
	}

	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			size_t index = col + row * width;
			if (row == 50 || col == 50)
			{
				pData[index] = 255;
			}
		}
	}



	return 1;
}