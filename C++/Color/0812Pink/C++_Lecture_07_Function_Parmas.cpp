#include <iostream>
#include <string>
#include <vector>

void Swap_ref(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void FnSwap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void swap_assign(int a, int b) 
{
	int t = a;
	a = b;
	b = t;
}

// case 1: memory a, b assignment
// (func a) = (ext a)
// case 2: memory 10, 20 create temp object(variables)
// (func int a) = (int temp)_a <= (10)


void main()
{
	int a = 10;
	int b = 20;
	std::cout << "기본값들" << std::endl;
	std::cout << "a = " << a <<" " << "b = " << b << " " << std::endl;
	Swap_ref(a, b);
	std::cout << "swap_ref(a,b)" << std::endl;
	std::cout << "a = " << a << " " << "b = " << b << " " << std::endl;
	FnSwap(&a, &b);
	std::cout << "Swap_pointer(a,b)" << std::endl;
	std::cout << "a = " << a <<" "<< "b = " << b << " " <<std::endl;
	swap_assign(10 , 20);
	swap_assign(a, b);

	int a_assign = 0;
	a_assign = a;
	a_assign = 10;
	std::cout << "Swap_assign(a,b)" << std::endl;
	//Swap_ref(10, 20); // 변수를 넣어야지 상수는 안됨
	std::cout << "a = " << a << " " << "b = " << b << " " << std::endl;
	return;
}