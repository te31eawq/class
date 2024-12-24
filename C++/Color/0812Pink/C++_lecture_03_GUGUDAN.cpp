#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int main()
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			std::cout << std::setw(2) << j << " x "
				 << i <<  " = " << std::setw(2) << i * j;
		}
		std::cout << std::endl;
	}

	return 1;
}