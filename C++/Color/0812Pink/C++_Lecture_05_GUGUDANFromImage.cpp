#include <iostream>
#include <string>
#include "ColorDefineh.h"

int main()
{

	//cv::Mat colorImage = cv::imread("Images\\Audrey.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
	int rows = 100;
	int cols = 100;

	cv::Mat img = cv::Mat::zeros(rows, cols, CV_8UC3);



	uchar* pData = img.data; // array start address
	int width = cols; // array width size
	int height = rows; // array height size
	int startrow = 45;
	int finishrow = 55;
	int startcol = 45;
	int finishcol = 55;
	int offset = 15;

	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			size_t index = col + row * width;
			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					if (row >= startrow + offset * a && row <= finishrow + offset * a
						&& col >= startcol + offset * b && col <= finishcol + offset * b)
					{
						if (a == 0 || b == 0)
							pData[index] = 255;
						if (a == 2 && b == 2)
							pData[index] = 255;
					}
					if (row >= startrow - offset * a && row <= finishrow - offset * a
						&& col >= startcol - offset * b && col <= finishcol - offset * b)
					{
						if (a == 0 || b == 0)
							pData[index] = 255;
						if (a == 2 && b == 2)
							pData[index] = 255;
					}
					if (row >= startrow + offset * a && row <= finishrow + offset * a
						&& col >= startcol - offset * b && col <= finishcol - offset * b)
						if (a == 2 && b == 2)
							pData[index] = 255;
					if (row >= startrow - offset * a && row <= finishrow - offset * a
						&& col >= startcol + offset * b && col <= finishcol + offset * b)
						if (a == 2 && b == 2)
							pData[index] = 255;

				}
			}

		}
	}



	return 1;
}