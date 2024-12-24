#include <iostream>
#include <string>
#include <vector>
class CStudent //data+action
{
private:
	//member variables
	int kor, eng, math;
	std::string name;
	double sum, avg;
	//member functions
public:
	CStudent()//creator...ctor
		: kor(0)//member initialized
		, eng(0)
		, math(0)
		, name("")
		, sum(0.0)
		, avg(0.0)
	{
		//kor = eng = math = 0;
		//name = "hong";
		//sum = avg = 0.;
	}
	~CStudent() {}//destroy...dtor

	void setting(std::string &nameset, int korres, int engres, int mathres)
	{
		name = nameset;
		kor = korres;
		eng = engres;
		math = mathres;
	}

	void calculate()
	{
		sum = kor + eng + math;
		avg = sum / 3.0;
	}

	std::string getname() const {return name;}
	int getkor() const { return kor; }
	int geteng() const { return eng; }
	int getmath() const { return math; }
	double getsum() const { return sum; }
	double getavg() const { return avg; }


protected:


};

int main()
{
	std::vector<CStudent> students;
	char addMore;
	do
	{
		int kor, eng, math;
		std::string name;
		CStudent student;

		std::cout << "�л� �̸��� �Է��ϼ���: ";
		std::cin >> name;

		std::cout << "���� ������ �Է��ϼ���: ";
		std::cin >> kor;

		std::cout << "���� ������ �Է��ϼ���: ";
		std::cin >> eng;

		std::cout << "���� ������ �Է��ϼ���: ";
		std::cin >> math;

		student.setting(name, kor, eng, math);
		student.calculate();

		students.push_back(student);

		std::cout << student.getname() << " �л��� ���� �հ�, ����� " << student.getsum() << ", " << student.getavg() << " �Դϴ�." << std::endl;

		std::cout << "�߰� �л� ������ �Է��Ͻðڽ��ϱ�? (Y or N): ";
		std::cin >> addMore;

	} while (addMore == 'Y' || addMore == 'y');

	// Display all student information
	std::cout << "\n��� �л� ����:\n";


	// std::vector<Student>::iterator iter = students.begin(); iter != students.end(); iter++)
	for (const auto& student : students)
	{
		std::cout << student.getname() << " �л��� ���� �հ�, ����� " << student.getsum() << ", " << student.getavg() << " �Դϴ�." << std::endl;
	}

	// Determine top students
	CStudent topKoreanStudent = students[0];
	CStudent topEnglishStudent = students[0];
	CStudent topMathStudent = students[0];

	for (const auto& student : students)
	{
		if (student.getkor() > topKoreanStudent.getkor())
			topKoreanStudent = student;

		if (student.geteng() > topEnglishStudent.geteng())
			topEnglishStudent = student;

		if (student.getmath() > topMathStudent.getmath())
			topMathStudent = student;
	}

	std::cout << "\n���� ���� �ֿ�� �л��� " << topKoreanStudent.getname() << " �л��Դϴ�." << std::endl;
	std::cout << "���� ���� �ֿ�� �л��� " << topEnglishStudent.getname() << " �л��Դϴ�." << std::endl;
	std::cout << "���� ���� �ֿ�� �л��� " << topMathStudent.getname() << " �л��Դϴ�." << std::endl;

	return 0;
}