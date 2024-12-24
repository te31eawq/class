#pragma once

#include <string>
//header :: 선언부
struct stScore
{
	int kor;
	int eng;
	int mat;
};

class student
{
public:
	student();
	~student();

private:
	// 선언 + 초기화
	int age = 0;
	std::string name = "";
	stScore score;

};

