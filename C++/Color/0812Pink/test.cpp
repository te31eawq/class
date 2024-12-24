#include <iostream>
#include <vector> // strlen, strcpy, strcat, strstr
#include <string>

using namespace std;

int main()
{
    int N;
	cin >> N;
	if (N > 100)
	{
		return 0;
	}
	vector<int> x(N, 0);
	vector<int> y(N, 0);
	int k = 0;
	int answer = N*100;
	int tempx = 0;
	int tempy = 0;

	while(k < N)
	{
		cin >> x[k] >> y[k];
		
		if (x[k] >= 0 && y[k] >= 0)
		{
			k++;
			
		}
	}

	for (size_t i = 0; i < N-1; i++)
	{
		for (size_t j = i; j < N; j++)
		{
			if (i != j)
			{
				if ((x[i] - x[j]) < 10 && (x[i] - x[j]) > -10 && (y[i] - y[j]) < 10 && (y[i] - y[j]) > -10)
				{
					tempx = 10 - (x[i] - x[j]);
					if (x[i] - x[j] < 0)
					{
						tempx = 10 + (x[i] - x[j]);
					}
					tempy = 10 - (y[i] - y[j]);
					if (y[i] - y[j] < 0)
					{
						tempy = 10 + (y[i] - y[j]);
					}
					cout << "temp x: " << tempx << endl;
					cout << "temp y: " << tempy << endl;
					answer = answer - (tempx * tempy);
				}
			}
		}
	}
	cout << answer;
	return 0;
}