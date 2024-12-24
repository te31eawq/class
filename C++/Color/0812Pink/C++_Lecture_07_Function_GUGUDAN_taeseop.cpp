#include <iostream>
#include <string>
#include <vector>

void GuGuDan() // 2단~9단::가로출력
{
	std::cout << "Function::GuGuDan()" << std::endl;
	for (size_t i = 2; i < 10; i++)
	{
		for (size_t j = 1; j < 10; j++)
		{
			std::cout << i << "*"  << j  << "=" <<i*j <<"\t";
		}
	}
	std::cout << std::endl;
}

//::가로출력 startDan ~ finish 단, startstep~finishstep
void GuGuDan(int startDan, int finishDan, int startStep, int finishStep)
{
	std::cout << "Function::GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;

	for (size_t i = startDan; i < finishDan; i++)
	{
		for (size_t j = startStep; j <= finishStep; j++)
		{
			std::cout << i << "*" << j << "=" << i * j << "\t";
			if (j == finishStep) std::cout << std::endl;
		}
	}
}

//::가로출력 startDan ~ finish 단, startstep~finishstep
//no display 
std::string GuGuDans(int startDan, int finishDan, int startStep, int finishStep)
{
	std::cout << "Function::string GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;
	std::string lines = "";
	for (size_t dan = 3; dan <= 5; dan++)
	{
		std::string line="";
		for (size_t step = 2; step <= 6; step++)
		{
			int gugu = dan * step;
			line += std::to_string(dan);
			line += "*";
			line += std::to_string(step);
			line += "=";
			line += std::to_string(gugu);
			line += "\n";
		}
		lines += line;
	}
	return lines;
}
int main()
{
	GuGuDan();
	GuGuDan(2, 8, 1, 7);
	std::string gg = GuGuDans(3, 5, 2, 6);
	std::cout << gg << std::endl;
	return 1;
}