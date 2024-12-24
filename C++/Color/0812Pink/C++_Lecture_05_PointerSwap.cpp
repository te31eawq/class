#include <iostream>
#include <string>
#include <vector>

void swap(int* a, int* b)
{
	if (a != nullptr && b != nullptr)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}
}

void swap2(int &a, int &b) // 레퍼런스
{
		int temp = a;
		a = b;
		b = temp;
}

int main()
{

	int a= 10, b= 20;

	
	std::cout << "a = " << a << " b = " << b << std::endl;
	swap(&a, &b);
	std::cout << "a = " << a << " b = " << b << std::endl;
	swap2(a, b);
	std::cout << "a = " << a << " b = " << b << std::endl;



	return 1;
}