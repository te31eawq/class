#include <iostream>
#include <string>
#include <vector>

int main()
{
	int nArray[] = {1,2,3,4,5,6,7,8,9,10};
	int* pArr = nArray;
	int length = sizeof(nArray) / sizeof(int);

	size_t sum = 0;

	sum = 0;
	for (size_t i = 0; i < length; i++)
		sum += *(pArr + i);
	std::cout << "sum = " << sum << std::endl;

	sum = 0;
	for (size_t i = 0; i < length; i++)
		sum += pArr[i];
	std::cout << "sum = " << sum << std::endl;

	sum = 0;
	for (size_t i = 0; i < length; i++)
		sum += *(pArr++);
	std::cout << "sum = " << sum << std::endl;
		sum += *(pArr++);
	std::cout << "sum = " << sum << std::endl;




	/*for (size_t i = 0; i < length; i++)
		std::cout << *(pArr + i) << " ";
	std::cout << std::endl;
	for (size_t i = 0; i < length; i++)
		std::cout << pArr[i] << " ";
	std::cout << std::endl;
	for (size_t i = 0; i < length; i++)
		std::cout << *(pArr++) << " ";
	std::cout << std::endl;
*/
	return 1;
}