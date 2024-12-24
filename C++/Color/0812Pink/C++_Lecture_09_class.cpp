#include <iostream>
#include <string>
#include <vector>

class GuGuDan
{
public:
	GuGuDan()
		: a_public(0)
		, a_private(0)
		, a_protected(0)
		, _startDan(0)
		, _finishDan(0)
		, _startStep(0)
		, _finishStep(0)
	{
		std::cout << "GuGuDan::Ctor" << std::endl;
	}
	//public, protected, private: 접근지정자
	GuGuDan(const int& startDan,
		const int& finishDan,
		const int& startStep,
		const int& finishStep)
		: _startDan(startDan)
		, _finishDan(finishDan)
		, _startStep(startStep)
		, _finishStep(finishStep)
	{
		std::cout << "GuGuDan::Ctor" << std::endl;
	}
	GuGuDan(const int& startDan,
		const int& finishDan)
		:GuGuDan(startDan, finishDan, 1, 9)
	{
	}

	~GuGuDan()
	{
		//class destroy
		std::cout << "GuGuDan::Dtor" << std::endl;
	}

	void setParams(const int& startDan,
		const int& finishDan,
		const int& startStep,
		const int& finishStep)
	{
		_startDan = startDan;
		_finishDan = finishDan;
		_startStep = startStep;
		_finishStep = finishStep;
	}

	std::string Do()
	{
		std::cout << "Function::string GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;
		std::string lines = "";
		std::cout << "_startDan의 값은 " << _startDan << std::endl;
		std::cout << "_finishDan의 값은 " << _finishDan << std::endl;
		for (size_t dan = _startDan; dan <= _finishDan; dan++)
		{
			std::string line = "";
			for (size_t step = _startStep; step <= _finishStep; step++)
			{
				int gugu = dan * step;
				line += std::to_string(dan);
				line += "*";
				line += std::to_string(step);
				line += "=";
				line += std::to_string(gugu);
				line += "\t";
			}
			line += '\n';
			lines += line;
		}
		return lines;
	}
public:
	int a_public = 0;
private:
	int a_private = 0;

	int _startDan = 0;
	int _finishDan = 0;
	int _startStep = 0;
	int _finishStep = 0;
protected://파생클래스에서 필요한 내용들
	int a_protected = 0;
};


int main()
{
	{
		GuGuDan ggd;
		ggd.setParams(3, 5, 1, 5);
		std::string gugudan_result = ggd.Do();
		std::cout << "display gugudan result" << std::endl;
		std::cout << gugudan_result << std::endl;
	}
	return 1;
}