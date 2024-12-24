#include <iostream>
#include <string>
#include <vector>

//
//function, 함수
//y = f(x) ... input : x, output : y... f : ??? ->a*x+b
//y2 = f(x1)
//y3 = f(x3) ... 재사용성을 가지는 기능
//y = f(x) = a*x+b
//
//function 특징 : 함수 오버로딩

//function
//return type    function_name    (parameters)
void Calc()
{
	std::cout << "Function::Calc()" << std::endl;
}
void Sum()
{
	std::cout << "Function::Sum()" << std::endl;
}
//input : 1 ea, output : 1 ea
int Calc(int x)
{
	std::cout << "Function::Calc(int x)" << std::endl;
	int a = 10;
	int b = 23;
	int y = a * x + b;
	return y;
}
//input : N ea, output : N ea
int Calc(int& a, int b, int& x, int* y=nullptr)
{
	std::cout << "Function::Calc(int& a, int b, int& x, int* y=nullptr)" << std::endl;
	*y = a * x + b;
	return 1;
}
int main()
{
	Calc();

	//void Calc()
	void (*pfnCalc)(void);//function pointer
	pfnCalc = Calc;
	pfnCalc();
	pfnCalc = Sum;
	pfnCalc();
	
	int* pCalc = nullptr;
	//y = f(x)
	int y = 0;
	int x = 10;
	y = Calc(x);
	std::cout << "y = f(x) " << y << " = f(" << x << ")" << std::endl;

	int a = 10;
	int b = 23;
	int ret = Calc(a,b,x,&y);
	std::cout << "y = f(x) " << y << " = f(" << x << ")" << std::endl;
	pfnCalc = Sum;
	pfnCalc();

	//ret = Calc(a, b, x, &y);
	//int Calc(int& a, int b, int& x, int* y = nullptr)
	int (*pfnCalcParams)(int&, int, int&, int*);//function pointer
	pfnCalcParams = Calc;
	ret = pfnCalcParams(a, b, x, &y);
	std::cout << "y = f(x) " << y << " = f(" << x << ")" << std::endl;
	
	return 1;
}