#include <iostream>
#include <string>
#include <vector>

//2��~9��::�������
void GuGuDan()
{
	std::cout << "Function::GuGuDan()" << std::endl;
}

//::������� startDan��~finish��, startStep~finishStep
void GuGuDan(int startDan, int finishDan, int startStep, int finishStep)
{
	std::cout << "Function::GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;

}
//::������� startDan��~finish��, startStep~finishStep
//no display, no use cout
std::string GuGuDans(int startDan, int finishDan, int startStep, int finishStep)
{
	std::cout << "Function::string GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;
	std::string lines;
	//for (size_t i = 0; i < 10; i++)
	//{
	//	std::string line="";
	//	for (size_t col = 0; col < 10; col++)
	//	{
	//		int gugu = dan * step;
	//		line += std::to_string(dan);
	//		line += " * ";
	//		line += std::to_string(step);
	//		line += " = ";
	//		line += std::to_string(gugu);
	//		line += "\t";
	//	}
	//	lines += line;
	//}
	return lines;
}

int main()
{


	GuGuDan();
	GuGuDan(2, 3, 4, 5);
	std::string gg = GuGuDans(2, 3, 4, 5);
	std::cout << gg << std::endl;
	return 1;
}