#include "student.h"


//cpp :: ������
student::student()
	:age(0) // ��� �̴ϼȶ�����
	, name("")
{
	memset(&score, 0x00, sizeof(score));
}

student::~student()
{
}