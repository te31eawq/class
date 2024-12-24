#include <iostream>
#include <string> // 문자와 문자가 열거되어 있는 상태 = 배열
#include <vector> // vector 컨테이너에 Arr를 저장
//::casting::
//static_cast
//const_cast
//reinterpret_case
//dynamic_cast

int main()
{
	std::cout << "C++_lecture_01.cpp" << std::endl;

	//c/c++...memory data
	//single value
	int a = 0;
	unsigned char aa = 0;
	char cA = 'A';
	double _aa = 0.1f;
	float _a = 0.01f;
	//pointer
	void*		pAddr = nullptr; //address 32bit, 64bit WORD()
	char*		pCharAddr = nullptr;
	double*		pDdAddr = nullptr;
	//*pDdAddr = 0x10;
	//group value 
	struct MyStruct
	{
		int a = 0;
		unsigned char aa = 0;
		char cA = 'A';
		double _aa = 0.1f;
		float _a = 0.01f;
	};
	//array... image processing ...database
	int Arr[10] = { 0x00, };// ....1
	std::vector<int> vArr(10);//....2
	std::vector<char> vArr2(10);
	std::vector<MyStruct> vArr3(10);

	//= operator
	//index [0]...[N-1] 까지 총 N개
	Arr[5] = 10;  // 얘는 Array
	vArr[5] = 10; // 얘는 vector


	//address addr++....addr++
	int* pArr = &Arr[0];
	pArr++;
	//l-value(남아있음) = r-value(사라짐)
	(*pArr) = 10;

	int* pvArr = &vArr[0];
	pvArr++;
	*pvArr = 10;

	//struct
	vArr3[0].a = 20;
	vArr3[1].aa = 'B';
	//class = {var, fuct > struct}

	std::cout << ("%d", vArr3[0].a) << std::endl;;
	std::cout << ("%s", vArr3[1].aa) << std::endl;;
	std::cout << ("%s", vArr3[2].cA) << std::endl;;
	std::cout << ("%lf", vArr3[3]._aa) << std::endl;

	return 1;
}