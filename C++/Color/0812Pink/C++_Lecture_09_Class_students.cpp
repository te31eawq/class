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
			std::cout << student.name << " 학생의 과목별 합계, 평균은 " 
			<< student.sum << "," << student.avg << " 입니다" << std::endl;
		}
		std::cout << "\n국어 성적 최우수 학생은 " << topKoreanStudent->name << "입니다";
		std::cout << "\n영어 성적 최우수 학생은 " << topEnglishStudent->name << "입니다";
		std::cout << "\n수학 성적 최우수 학생은 " << topMathStudent->name << "입니다\n";
	}
	std::vector<Score>& GetStudents() { return students; }

};

int main()
{
	std::cout << "이 프로그램은 학생 성적을 관리하는 프로그램입니다." << std::endl;
	std::cout << "학생 이름/ 국,영,수 정보를 입력하시면 학생들의 성적을 정리해드립니다." << std::endl;
	std::cout << "============================================" << std::endl;
	StudentInfo students;
	char addMore;
	do
	{
		int kor, eng, math;
		std::string name;

		std::cout << "학생 이름을 입력하세요 : "; std::cin >> name;
		std::cout << "국어 성적을 입력하세요 : "; std::cin >> kor;
		std::cout << "수학 성적을 입력하세요 : "; std::cin >> eng;
		std::cout << "영어 성적을 입력하세요 : "; std::cin >> math;

		students.SetInfo(name, kor, eng, math);

		std::cout << "추가 학생 정보를 입력하시겠습니까? (Y or N): ";
		std::cin >> addMore;

	} while (addMore == 'Y' || addMore == 'y');
	students.CalcBestStudent();
	std::cout << "\n모든 학생 정보: \n";
	students.ShowInfo();

	

	return 1;
}