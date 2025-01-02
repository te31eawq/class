#include <iostream>
#include <string>
#include <vector>

int main()
{
	//제어문 : 조건문 , 반복문
	

	//int nArray[10] = { 1,2,3,4,5,6,7,8,9,10 }; // int x array[10] = 4x10 = 40
	//int* arrayPtr = nArray;

	//for (int i = 0; i < sizeof(nArray) / sizeof(int); i++)
	//{
	//	std::cout << arrayPtr[i] << "  "<<std::endl;
	//}

	//std::cout << "sizeof(nArray) 크기 : " << sizeof(nArray) << std::endl;
	//std::cout << "sizeof(int) 크기 : " << sizeof(int) << std::endl;
	//std::cout << "sizeof(nArray)/sizeof(int) 크기 : " << sizeof(nArray)/sizeof(int) << std::endl;

	//size = (-)...array 
	

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			std::cout << "i = " << i << std::endl;
		else if (i % 2 != 0)
			std::cout << "i_o = " << i << std::endl;
		else
			std::cout << "default" << std::endl;
	}

	std::vector<int> v(10);
	size_t sz = v.size();
	for (size_t i = 0; i < v.size(); i++)
		std::cout << "v =  " << v[i] << std::endl;

	for (size_t i = 0; i < v.size(); i++)
	{
		if (i % 2 == 0)
		{
			std::cout << "i = " << i << std::endl;
		}
	}

	for (size_t row = 0; row < 10; row++)
	{
		for (size_t col = 0; col < 10; col++)
		{
			std::cout << "[row,col] = " << row << " , " << col << std::endl;
		}
	}
}