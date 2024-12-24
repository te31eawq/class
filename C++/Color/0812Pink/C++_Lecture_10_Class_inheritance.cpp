#include <iostream>
#include <string>
#include <vector>


class GuGuDan
{
	//public, protected, private: 접근지정자
public:
	GuGuDan()
		: p_public(0)
		, p_private(0)
		, p_protected(0)
		, _startDan(0)
		, _finishDan(0)
		, _startStep(0)
		, _finishStep(0)
	{
		//class creator
		std::cout << "GuGuDan::Ctor" << std::endl;
	}
	GuGuDan(const int& startDan,
		const int& finishDan,
		const int& startStep,
		const int& finishStep)
		: _startDan(startDan)
		, _finishDan(finishDan)
		, _startStep(startStep)
		, _finishStep(finishStep)
	{
		//class creator
		std::cout << "GuGuDan::Ctor" << std::endl;
	}
	GuGuDan(const int& startDan,
		const int& finishDan)
		:GuGuDan(startDan, finishDan, 1, 9)
	{
		std::cout << "GuGuDan::Ctor" << std::endl;
	}

	virtual ~GuGuDan() {
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
	//virtual std::string DoV();//virtual function
	virtual std::string Do()//pure virtual function
	{
		std::cout << "Call GuGuDan::Do" << std::endl;
		std::string lines;
		for (size_t step = _startStep; step <= _finishStep; step++)
		{
			std::string line = "";
			for (size_t dan = _startDan; dan <= _finishDan; dan++)
			{
				int result = dan * step;
				line += std::to_string(dan);
				line += " x ";
				line += std::to_string(step);
				line += " = ";
				line += std::to_string(result);
				line += "\t";
			}
			lines += line + "\n";
		}
		return lines;
	}


public:
	int p_public = 0;
private:
	int p_private = 0;

protected:
	int _startDan = 0;
	int _finishDan = 0;
	int _startStep = 0;
	int _finishStep = 0;

protected://파생클래스에서 필요한 내용들
	int p_protected = 0;
};
class GuGuDan_A : public GuGuDan
{
private:
	int a = 0;
public:
	GuGuDan_A() { std::cout << "GuGuDan_A::Ctor" << std::endl; }
	~GuGuDan_A() { std::cout << "GuGuDan_A::Dtor" << std::endl; }
	void checkMemory()
	{
		a = 100;

		p_public = 100;
		p_protected = 100;
		//a_private = 100; //error
	}
	std::string Do()//overriding
	{
		std::cout << "Call GuGuDan_A::Do" << std::endl;
		std::string lines;
		for (size_t dan = _startDan; dan <= _finishDan; dan++)
		{
			std::string line = "";
			for (size_t step = _startStep; step <= _finishStep; step++)
			{
				int result = dan * step;
				line += std::to_string(dan);
				line += " x ";
				line += std::to_string(step);
				line += " = ";
				line += std::to_string(result);
				line += "\n";
			}
			lines += line + "\n";
		}
		return lines;
	}
};

int main_backup()
{
	GuGuDan ggd;
	ggd.setParams(3, 5, 1, 5);
	std::string gugudan_result = ggd.Do();
	//output
	std::cout << "display gugudan result" << std::endl;
	std::cout << gugudan_result << std::endl;


	GuGuDan_A ggd_a;
	ggd_a.checkMemory();

	//input
	ggd_a.setParams(3, 5, 1, 5);

	//doing algorithm
	gugudan_result = ggd_a.Do();

	//output
	std::cout << "display gugudan result" << std::endl;
	std::cout << gugudan_result << std::endl;


	return 1;

}

int main()
 
{
	GuGuDan* pGGD = nullptr;
	GuGuDan_A* pGGD_A = nullptr;
	GuGuDan_A ggd_a;

	pGGD = dynamic_cast<GuGuDan*>(&ggd_a);//up-casting // 결국에는 GuGuDan 캐스팅

	pGGD_A = dynamic_cast<GuGuDan_A*>(pGGD);//down-casting // 결국에는 ... 뭐지?
	//pGGD->checkMemory();

	//input
	pGGD->setParams(3, 5, 1, 5);


	//doing algorithm
	std::string gugudan_result = pGGD->Do();

	//output
	std::cout << "display gugudan result" << std::endl;
	std::cout << gugudan_result << std::endl;


	return 1;
}