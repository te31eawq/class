#include "student.h"


//cpp :: 구현부
student::student()
	:age(0) // 멤버 이니셜라이저
	, name("")
{
	memset(&score, 0x00, sizeof(score));
}

student::~student()
{
}