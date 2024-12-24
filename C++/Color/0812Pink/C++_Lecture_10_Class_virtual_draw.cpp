#include <iostream>
#include <string>
#include <vector>
#include "ColorDefineh.h"

using namespace std;
using namespace cv;

class IDrawer
{
public:
	virtual void draw_line(cv::Point pt1, cv::Point pt2) { std::cout << "IDrawer::draw" << std::endl; }
	virtual void line(Point pt1, Point pt2)
	{
		cout << "Drawer::line" << endl;
	};
	virtual void circle(Point pt1, int radius)
	{
		cout << "Drawer::circle" << endl;
	};
	virtual void rectangle(Point pt1, Point pt2)
	{
		cout << "Drawer::rectangle" << endl;
	};
	virtual void polygon(std::vector<Point> pts)
	{
		cout << "Drawer::polygon" << endl;
	};
	virtual void txt(Point pt1, Point pt2)
	{
		cout << "Drawer::txt" << endl;
	};
	virtual void set_image(const cv::Mat& img)
	{
		cv::Mat _img = img;
	};
};

class DrawTxt : public IDrawer
{

public:
	DrawTxt() {}
	~DrawTxt() {}
	void draw_line(cv::Point pt1, cv::Point pt2) override
	{
		std::cout << "DrawTxt::draw_line" << std::endl;
		std::cout << "pt1" << pt1.x << "," << pt1.y << "---->" << "pt2 =" << pt2.x << "," << pt2.y << std::endl;
	}
	void line(Point pt1, Point pt2)
	{
		cout << "DrawTxt::line" << endl;
	};
	void circle(Point pt1, int radius)
	{
		cout << "DrawTxt::circle" << endl;
	};
	void rectangle(Point pt1, Point pt2)
	{
		cout << "DrawTxt::rectangle" << endl;
	};
	void polygon(std::vector<Point> pts)
	{
		cout << "DrawTxt::polygon" << endl;
	};
	void txt(Point pt1, Point pt2)
	{
		cout << "DrawTxt::txt" << endl;
	};

};

class DrawMat :public IDrawer
{
private:
	Mat _img;
	Mat draw_img;
public:
	DrawMat() {}
	DrawMat(const Mat& color_img)
		: draw_img(color_img) {}
	~DrawMat(){}
	void set_image(const cv::Mat& img)
	{
		_img = img.clone();
	}
	void draw_line(cv::Point pt1, cv::Point pt2)
	{
		cv::Size size = _img.size();
		uchar* pData = _img.data;
		int width = size.width;
		int height = size.height;
		int x0 = pt1.x; int y0 = pt1.y; int x1 = pt2.x;  int y1 = pt2.y;
		int dx = abs(x0 - x1);
		int dy = abs(y0 - y1);

		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		int err = dx - dy;
		int e2;

		while (true)
		{
			pData[y0 * width + x0] = 255;
			if (x0 == x1 && y0 == y1)
				break;
			e2 = 2 * err;

			if (e2 > -dy)
			{
				err -= dy;
				x0 += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				y0 += sy;
			}
		}
	}
	void line(Point pt1, Point pt2)
	{
	};
	void circle(Point pt1, int radius)
	{
		uchar* pData = _img.data;
		int width = _img.cols;
		const double PI = 3.14159265358979323846;
		int points = 360;
		double angle = 2 * PI / points;

		for (size_t i = 0; i < points; i++)
		{
			double angleStep = i * angle;
			int DrawX = static_cast<int>(pt1.x + radius * cos(angleStep));
			int DrawY = static_cast<int>(pt1.y + radius * sin(angleStep));
			pData[DrawY * width + DrawX] = 255;
		}
	};
	void rectangle(Point pt1, Point pt2)
	{
	};
	void polygon(std::vector<Point> pts)
	{
	};
	void txt(Point pt1, Point pt2)
	{
	};
	cv::Mat get_image() const {
		return _img;
	};
};

int main()
{
	cv::Point pt[2] = { cv::Point(300,300), cv::Point(400,100) };
	cv::Mat img = cv::Mat::zeros(400, 600, CV_8UC1);
	IDrawer first;
	DrawTxt second;
	DrawMat third;
	IDrawer* pspace = nullptr;

	pspace = &first;
	pspace->draw_line(pt[0], pt[1]);

	pspace = &second;
	pspace->draw_line(pt[0], pt[1]);

	pspace = &third;
	pspace->set_image(img);
	pspace->draw_line(pt[0], pt[1]);
	pspace->circle(pt[0], 10);
	
	img = third.get_image();





	int a = 1;

	return 1;

}