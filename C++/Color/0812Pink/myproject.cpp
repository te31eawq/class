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
		std::cout << "부모클래스 함수 사용" << std::endl;
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
		std::cout << "자식클래스 함수 사용" << std::endl;
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
	}

	void drawing2(int rows, int cols, cv::Scalar color = 255)
	{
		std::cout << "자식클래스2함수 사용" << std::endl;
		img = cv::Mat::zeros(rows, cols, CV_8UC1);
	}

	void line(cv::Point pt1, cv::Point pt2)
	{
		int width = img.cols;
		std::cout << "자식클래스 line 사용" << std::endl;
		pData[pt1.y * width + pt1.x] = 255;
	}
};

int main()
{
	int rows = 400;
	int cols = 600;

	cv::Point pt[2] = { cv::Point(100,100), cv::Point(200,200) };
	draw* pscatch = new drawson(rows, cols, 255);
	drawson* son = dynamic_cast<drawson*>(pscatch); // 다운캐스팅
	const cv::Mat real = son->GetCanvas();
	son->line(pt[0], pt[1]);
	
	



	/*drawson second;   // 업캐스팅
	draw* pscatch = nullptr;

	pscatch = &second; // 부모로부터 함수는 이어받지만 재정의 할 수 있음
	pscatch->drawing(400, 600, 255);
	const cv::Mat real = pscatch->GetCanvas();
	pscatch->line(pt[0], pt[1]);*/






	return 1;

}