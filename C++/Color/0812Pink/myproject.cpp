#include <iostream>
#include <string>
#include <vector>
#include "ColorDefineh.h"

class draw
{
protected:
	cv::Mat img;
	uchar* pData;

public:
	draw() {};
	draw(int rows, int cols, cv::Scalar color = 255)
	{
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
		pData = img.data;
	}
	virtual ~draw() {}
	virtual const cv::Mat& GetCanvas() { return img; }

	virtual void drawing(int rows, int cols, cv::Scalar color = 255)
	{
		std::cout << "�θ�Ŭ���� �Լ� ���" << std::endl;
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
	}
};

class drawson : public draw
{
public:
	drawson() {}
	drawson(int rows, int cols, cv::Scalar color = 255)
	{
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
		pData = img.data;
	}
	~drawson() {}

	const cv::Mat& GetCanvas() { return img; }

	void drawing(int rows, int cols, cv::Scalar color = 255)
	{
		std::cout << "�ڽ�Ŭ���� �Լ� ���" << std::endl;
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
	}

	void drawing2(int rows, int cols, cv::Scalar color = 255)
	{
		std::cout << "�ڽ�Ŭ����2�Լ� ���" << std::endl;
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
	}

	void line(cv::Point pt1, cv::Point pt2)
	{
		int width = img.cols;
		std::cout << "�ڽ�Ŭ���� line ���" << std::endl;
		pData[pt1.y * width + pt1.x] = 255;
	}
};

int main()
{
	int rows = 400;
	int cols = 600;

	cv::Point pt[2] = { cv::Point(100,100), cv::Point(200,200) };
	draw* pscatch = new drawson(rows, cols, 255);
	drawson* son = dynamic_cast<drawson*>(pscatch); // �ٿ�ĳ����
	const cv::Mat real = son->GetCanvas();
	son->line(pt[0], pt[1]);
	
	



	/*drawson second;   // ��ĳ����
	draw* pscatch = nullptr;

	pscatch = &second; // �θ�κ��� �Լ��� �̾������ ������ �� �� ����
	pscatch->drawing(400, 600, 255);
	const cv::Mat real = pscatch->GetCanvas();
	pscatch->line(pt[0], pt[1]);*/






	return 1;

}