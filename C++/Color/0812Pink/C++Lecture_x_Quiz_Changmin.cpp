#include <iostream>

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

void DrawLine(Point pt1, Point pt2, Point pt3, Point pt4) {
    int width = pt2.x - pt1.x + 1;
    int height = pt3.y - pt2.y + 1;

    for (int i = 0; i < width; ++i) {
        if (i == 0) std::cout << "忙";
        else if (i == width - 1) std::cout << "忖";
        else std::cout << "式式";
    }
    std::cout << std::endl;

    for (int i = 0; i < height - 2; ++i) {
        std::cout << "弛";
        for (int j = 0; j < width - 2; ++j) {
            std::cout << "  ";
        }
        std::cout << "弛" << std::endl;
    }

    for (int i = 0; i < width; ++i) {
        if (i == 0) std::cout << "戌";
        else if (i == width - 1) std::cout << "戎";
        else std::cout << "式式";
    }
    std::cout << std::endl;
}

int main() {
    Point pt[4] = { Point(1,1), Point(10,1), Point(10,10), Point(1,10) };
    DrawLine(pt[0], pt[1], pt[2], pt[3]);

    return 1;
}