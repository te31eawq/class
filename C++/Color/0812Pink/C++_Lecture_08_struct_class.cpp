#include <iostream>
#include <string>
#include <vector>

struct Student // data
{
	int kor, eng, math;
	std::string name;
	double sum, avg, tot;
	Student()
	{
		kor = eng = math = 0;
		name = 'hong';
		sum = avg = tot = 0.;
	}
};


class CStudent // data + action
{
private:
	//member variables
	int kor, eng, math;
	std::string name;
	double sum, avg, tot;
public:
	//member functions
	CStudent() // creator... ctor;
		: kor(0)//member initialized
		, eng(0)
		, math(0)
		, name("hong")
		,sum(0.0)
		,avg(0.0)
		,tot(0.0)
	{
		/*kor = eng = math = 0;
		name = "hong";
		sum = avg = tot = 0;*/
	}
	~CStudent() {} // destroy... dtor
protected:
};

int main()
{
	char confirm;
	int i = 0, full = 0, j = 0, next = 0;
	std::vector<Student> students;
	Student student[100];

	while(1)
	{
		std::cout << "학생 입력을 받으세요" << std::endl;
		std::cin >> student[i].name;

		std::cout << "국어 성적을 입력하세요" << std::endl;
		std::cin >> student[i].kor;
		std::cout << "영어 성적을 입력하세요" << std::endl;
		std::cin >> student[i].eng;
		std::cout << "수학 성적을 입력하세요" << std::endl;
		std::cin >> student[i].math;
		student[i].sum = student[i].kor + student[i].eng + student[i].math;
		student[i].avg = (student[i].kor + student[i].eng + student[i].math) / 3;

		std::cout << student[i].name << "의 과목별 합계, 평균은 " << student[i].sum << ", " << student[i].avg << "입니다" << std::endl << std::endl;
		std::cout << "추가 학생 정보를 입력하시겠습니까? (Y or N)" << std::endl;
		std::cin >> confirm; // Y 와 N 확인용

		if (confirm == 'Y')
		{
			std::cout << std::endl;
			i++;
		}
		else if (confirm == 'N')
		{
			full = i; // 입력한 수 만큼만 
			for (i = 0; i <= full; i++)
			{
				std::cout << student[i].name << "의 과목별 합계, 평균은 " << student[i].sum << ", " << student[i].avg << "입니다" << std::endl;
			}
			std::cout << std::endl;
			for (int turn = 0; turn <= full+1; turn++) // 국어 성적 비교
			{
				if (student[j].kor < student[j + next + 1].kor)
				{
					j = j + next + 1;
					next = 0;
				}
				else
				{
					next++;
				}
			}

			std::cout << "국어 성적 최우수 학생은 " << student[j].name << " 학생입니다" << std::endl;

			j = 0;
			next = 0;
			for (int turn = 0; turn <= full+1; turn++) // 영어 성적 비교
			{
				if (student[j].eng < student[j + next + 1].eng)
				{
					j = j +next + 1;
					next = 0;
				}
				else
				{
					j = j;
					next++;
				}
			}
			std::cout << "영어 성적 최우수 학생은 " << student[j].name << " 학생입니다" << std::endl;
			j = 0;
			next = 0;
			for (int turn = 0; turn <= full+1; turn++) // 수학 성적 비교
			{
				if (student[j].math < student[j + next + 1].math)
				{
					j = j + next + 1;
					next = 0;
				}
				else
				{
					j = j;
					next++;
				}
			}
			std::cout << "수학 성적 최우수 학생은 " << student[j].name << " 학생입니다" << std::endl;
			break;
		}
	}

	//학생 입력을 받으세요.
	//국어 성적을 입력하시오
	//영어 성적을 입력하시오
	//수학 성적을 입력하시오
	//학생의 과목별 합계, 평균은 ??, ?? 입니다

	//추가 학생 정보를 입력하시겠습니까? (Y or N)
	//학생 입력을 받으세요.
	//국어 성적을 입력하시오
	//영어 성적을 입력하시오
	//수학 성적을 입력하시오
	//학생의 과목별 합계, 평균은 ??, ?? 입니다
	 

	//추가 학생 정보를 입력하시겠습니까? (Y or N)
	// 종료 시 모든 학생의 정보를 위와같이 출력하시오
	// 서창민 학생의 과목별 합계, 평균은 ??, ??입니다
	// 최재원 학생의 과목별 합계, 평균은 ?? ,??입니다
	// 영어 성적 최우수 학생은 서창민 학생입니다.
	// 수학 성적 최우수 학생은 서창민 학생입니다.
	// 국어 성적 최우수 학생은 최재원 학생입니다.
	 
	
	//CStudent c_student;

	return 1;
}

