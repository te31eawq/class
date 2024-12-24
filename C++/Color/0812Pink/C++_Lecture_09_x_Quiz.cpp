#include <iostream>
#include <string>
#include <vector>
#include "ColorDefineh.h"

struct Point
{
	int x, y;
	Point(int _x, int _y) : x(_x), y(_y) {}
};


void DrawLine(Point pt1, Point pt2)
{
	std::cout << "pt1= " << pt1.x << "," << pt1.y << "---->" << "pt2= " << pt2.x << "," << pt2.y << std::endl;
}

int main()
{

	const 

	Point pt[4] = { Point(1,1),Point(10,1),Point(10,10),Point(1,10)};

	for (size_t i = 0; i < 4; i++)
	{
		DrawLine(pt[i%4], pt[(i+1)%4]);
	}

	

	return 1;
}

//#include <iostream>
//#include <string>
//#include <vector>
//
//struct point
//{
//    int x, y;
//    point(int _x, int _y) : x(_x), y(_y) {}
//};
//
//void drawline(std::vector<std::string>& grid, point pt1, point pt2)
//{
//    if (pt1.y == pt2.y)
//    {
//        int x_end = std::max(pt1.x, pt2.x);
//        int x_start = std::min(pt1.x, pt2.x);
//        for (size_t x = x_start; x <= x_end; x++)
//        {
//            grid[pt1.y][x] = '*';
//        }
//    }
//    else if (pt1.x == pt2.x)
//    {
//        int y_end = std::max(pt1.y, pt2.y);
//        int y_start = std::min(pt1.y, pt2.y);
//        for (size_t y = y_start; y < y_end; y++)
//        {
//            grid[y][pt1.x] = '*';
//        }
//    }
//    /*std::cout << "pt1=" << pt1.x << "," << pt1.y << "---->" << pt2.x << "," << pt2.y << std::endl;*/
//}
//
//void DrawGrid(const std::vector<std::string>& grid)
//{
//    for (const auto& line : grid)
//    {
//        std::cout << line << std::endl;
//    }
//}
//
//int main()
//{
//    int width = 12;
//    int height = 12;
//
//    std::vector<std::string> grid(height, std::string(width, ' '));
//
//    std::vector<point> pt;
//    pt.push_back(point(1, 1));
//    pt.push_back(point(10, 1));
//    pt.push_back(point(10, 10));
//    pt.push_back(point(1, 10));
//
//    //이것을 for문을 사용하여 사각형을 그리ㅣ오
//    drawline(grid, pt[0], pt[1]);
//    drawline(grid, pt[1], pt[2]);
//    drawline(grid, pt[2], pt[3]);
//    drawline(grid, pt[3], pt[0]);
//
//
//    DrawGrid(grid);
//    return 1;
//
//}