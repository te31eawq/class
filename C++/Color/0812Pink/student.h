#pragma once

#include <string>
//header :: �����
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
	// ���� + �ʱ�ȭ
	int age = 0;
	std::string name = "";
	stScore score;

};

