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
		std::cout << "�л� �Է��� ��������" << std::endl;
		std::cin >> student[i].name;

		std::cout << "���� ������ �Է��ϼ���" << std::endl;
		std::cin >> student[i].kor;
		std::cout << "���� ������ �Է��ϼ���" << std::endl;
		std::cin >> student[i].eng;
		std::cout << "���� ������ �Է��ϼ���" << std::endl;
		std::cin >> student[i].math;
		student[i].sum = student[i].kor + student[i].eng + student[i].math;
		student[i].avg = (student[i].kor + student[i].eng + student[i].math) / 3;

		std::cout << student[i].name << "�� ���� �հ�, ����� " << student[i].sum << ", " << student[i].avg << "�Դϴ�" << std::endl << std::endl;
		std::cout << "�߰� �л� ������ �Է��Ͻðڽ��ϱ�? (Y or N)" << std::endl;
		std::cin >> confirm; // Y �� N Ȯ�ο�

		if (confirm == 'Y')
		{
			std::cout << std::endl;
			i++;
		}
		else if (confirm == 'N')
		{
			full = i; // �Է��� �� ��ŭ�� 
			for (i = 0; i <= full; i++)
			{
				std::cout << student[i].name << "�� ���� �հ�, ����� " << student[i].sum << ", " << student[i].avg << "�Դϴ�" << std::endl;
			}
			std::cout << std::endl;
			for (int turn = 0; turn <= full+1; turn++) // ���� ���� ��
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

			std::cout << "���� ���� �ֿ�� �л��� " << student[j].name << " �л��Դϴ�" << std::endl;

			j = 0;
			next = 0;
			for (int turn = 0; turn <= full+1; turn++) // ���� ���� ��
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
			std::cout << "���� ���� �ֿ�� �л��� " << student[j].name << " �л��Դϴ�" << std::endl;
			j = 0;
			next = 0;
			for (int turn = 0; turn <= full+1; turn++) // ���� ���� ��
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
			std::cout << "���� ���� �ֿ�� �л��� " << student[j].name << " �л��Դϴ�" << std::endl;
			break;
		}
	}

	//�л� �Է��� ��������.
	//���� ������ �Է��Ͻÿ�
	//���� ������ �Է��Ͻÿ�
	//���� ������ �Է��Ͻÿ�
	//�л��� ���� �հ�, ����� ??, ?? �Դϴ�

	//�߰� �л� ������ �Է��Ͻðڽ��ϱ�? (Y or N)
	//�л� �Է��� ��������.
	//���� ������ �Է��Ͻÿ�
	//���� ������ �Է��Ͻÿ�
	//���� ������ �Է��Ͻÿ�
	//�л��� ���� �հ�, ����� ??, ?? �Դϴ�
	 

	//�߰� �л� ������ �Է��Ͻðڽ��ϱ�? (Y or N)
	// ���� �� ��� �л��� ������ ���Ͱ��� ����Ͻÿ�
	// ��â�� �л��� ���� �հ�, ����� ??, ??�Դϴ�
	// ����� �л��� ���� �հ�, ����� ?? ,??�Դϴ�
	// ���� ���� �ֿ�� �л��� ��â�� �л��Դϴ�.
	// ���� ���� �ֿ�� �л��� ��â�� �л��Դϴ�.
	// ���� ���� �ֿ�� �л��� ����� �л��Դϴ�.
	 
	
	//CStudent c_student;

	return 1;
}

