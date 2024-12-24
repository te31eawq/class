#include <iostream>
#include <string>
#include "ColorDefineh.h"

class DrawCanvas
{
private:
	cv::Mat canvas;
	uchar* pCanvas = nullptr;
public:
	DrawCanvas() {};
	DrawCanvas(int rows, int cols, int channels = 1)
	{
		if (channels == 1)
			canvas = cv::Mat::zeros(rows, cols, CV_8UC1);
		else if (channels == 3)
			canvas = cv::Mat::zeros(rows, cols, CV_8UC3);
		pCanvas = canvas.data;
	}
	~DrawCanvas() {};

	const cv::Mat& GetCanvas() { return canvas; }
	void Draw_line(cv::Point pt1, cv::Point pt2, cv::Scalar color = 255)
	{
		if (pt1.x > pt2.x)
			std::swap(pt1.x, pt2.x);
		if (pt1.y > pt2.y)
			std::swap(pt1.y, pt2.y);

		int x0 = pt1.x;
		int y0 = pt1.y;
		int x1 = pt2.x;
		int y1 = pt2.y;

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		double m = 0.0;
		if (dy != 0 && dx != 0)
			m = dy * 1.0 / dx;
		double offset = y0 - m * x0;
		//offset *= 1;

		while (true)
		{
			pCanvas[y0 * canvas.cols + x0] = color[0];

			if (abs(x0 - x1) <= 1 && abs(y0 - y1) <= 1)
				break;

			if (dx != 0)
			{
				x0++;
				y0 = m * x0 + offset;
			}
			else
				y0++;
		}
		/*int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		int err = dx - dy; // 1-0, 0-1
		int e2;
		while (true)
		{
			pCanvas[y0 *canvas.cols + x0] = color[0];
			if (x0 == x1 && y0 == y1)
				break;

			e2 = 2 * err;

			if (e2 < dx)
			{
				err += dx;
				y0 += sy;
			}

			if (e2 > -dy)
			{
				err -= dy;
				x0 += sx;
			}
		}*/
	}
	void Draw_circle(cv::Point pt, int radius, cv::Scalar color = 255)
	{
		const double PI = 3.14159265358979323846;
		int points = 360*3;
		double angleStep = 2 * PI / points; // 라디안으로 바꿈(계산상으로 1도)

		for (size_t i = 0; i < points; i++)
		{
			double angle = i * angleStep; // 각도 1도씩 변경
			int DrawX = (pt.x + cos(angle) * radius);
			int DrawY = (pt.y + sin(angle) * radius);

			pCanvas[DrawY * canvas.cols + DrawX] = color[0];


		}
	}
	void Draw_rectangle(cv::Point pt_topLeft, cv::Point pt_btmRight, cv::Scalar color = 255)
	{
		int x0 = pt_topLeft.x; // ex (20,20) 와 (60,60)
		int y0 = pt_topLeft.y;
		int x2 = pt_btmRight.x;
		int y2 = pt_btmRight.y;

		int x1 = x2; // righttop
		int y1 = y0;

		int x3 = x0; // leftbtm
		int y3 = y2;

		Draw_line({ x0,y0 }, { x2,y2 }, color[0]);
		Draw_line({ x2,y2 }, { x1,y1 }, color[0]);
		Draw_line({ x1,y1 }, { x3,y3 }, color[0]);
		Draw_line({ x3,y3 }, { x0,y0 }, color[0]);
	}
};


int main()
{
	int rows = 400;
	int cols = 600;
	int channels = 1;//gray-1,color-3 
	DrawCanvas dCan(rows, cols, channels);

	const cv::Mat& canvasImage = dCan.GetCanvas();

	cv::Point pt(cols / 2 - 1, rows / 2 - 1);
	int radius = std::min(rows, cols) / 3;
	dCan.Draw_circle(pt, radius);


	int gap = 10;
	cv::Point ptArry[4] = { cv::Point(0 + gap,0 + gap),
	cv::Point(cols-1-gap,0 + gap),
	cv::Point(cols - 1 - gap,rows - 1 - gap),
	cv::Point(0 + gap,rows - 1 - gap) };

	dCan.Draw_line(ptArry[0], ptArry[1], cv::Scalar(255));
	dCan.Draw_line({ 300,200 }, { 400,300 }, cv::Scalar(255));
	//dCan.Draw_rectangle(ptArry[0], ptArry[2], cv::Scalar(255));



	//debug point, check image watch
	int a = 0;

	return 1;
}