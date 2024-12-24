#include <iostream>
#include <string>
#include <vector>

struct Score
{
	int kor, eng, math;
	std::string name;
	double sum, avg;
};

class StudentInfo
{
private:
	std::vector<Score> students;
	const Score* topKoreanStudent = nullptr;
	const Score* topEnglishStudent = nullptr;
	const Score* topMathStudent = nullptr;
public:
	StudentInfo() { std::cout << "Students::Ctor" << std::endl; }
	~StudentInfo() { std::cout << "Students::Dtor" << std::endl; }

	void SetInfo(const std::string& name, const int& kor, const int& eng, const int& math)
	{
		Score score;
		score.name = name; score.kor = kor; score.eng = eng; score.math = math;
		score.sum = kor + eng + math;
		score.avg = score.sum / 3;
		students.push_back(score);
	}

	void CalcBestStudent()
	{
		topKoreanStudent = &students[0];
		topEnglishStudent = &students[0];
		topMathStudent = &students[0];

		for (const auto& student : students)
		{
			for (const auto& student : students)
			{
				if (student.kor > topKoreanStudent->kor)
					topKoreanStudent = &student;

				if (student.eng > topEnglishStudent->eng)
					topEnglishStudent = &student;

				if (student.math > topMathStudent->math)
					topMathStudent = &student;
			}
		}
	}

	void ShowInfo()
	{
		for (const auto& student : students)
		{
			std::cout << student.name << " �л��� ���� �հ�, ����� " 
			<< student.sum << "," << student.avg << " �Դϴ�" << std::endl;
		}
		std::cout << "\n���� ���� �ֿ�� �л��� " << topKoreanStudent->name << "�Դϴ�";
		std::cout << "\n���� ���� �ֿ�� �л��� " << topEnglishStudent->name << "�Դϴ�";
		std::cout << "\n���� ���� �ֿ�� �л��� " << topMathStudent->name << "�Դϴ�\n";
	}
	std::vector<Score>& GetStudents() { return students; }

};

int main()
{
	std::cout << "�� ���α׷��� �л� ������ �����ϴ� ���α׷��Դϴ�." << std::endl;
	std::cout << "�л� �̸�/ ��,��,�� ������ �Է��Ͻø� �л����� ������ �����ص帳�ϴ�." << std::endl;
	std::cout << "============================================" << std::endl;
	StudentInfo students;
	char addMore;
	do
	{
		int kor, eng, math;
		std::string name;

		std::cout << "�л� �̸��� �Է��ϼ��� : "; std::cin >> name;
		std::cout << "���� ������ �Է��ϼ��� : "; std::cin >> kor;
		std::cout << "���� ������ �Է��ϼ��� : "; std::cin >> eng;
		std::cout << "���� ������ �Է��ϼ��� : "; std::cin >> math;

		students.SetInfo(name, kor, eng, math);

		std::cout << "�߰� �л� ������ �Է��Ͻðڽ��ϱ�? (Y or N): ";
		std::cin >> addMore;

	} while (addMore == 'Y' || addMore == 'y');
	students.CalcBestStudent();
	std::cout << "\n��� �л� ����: \n";
	students.ShowInfo();

	

	return 1;
}