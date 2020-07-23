#include <iostream>
#include <iomanip>
using namespace std;
#define min(a, b) ((a) < (b)? (a) : (b))
void printMatrix(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
		 	// 获得当前的点所在的圈数
			int level = min(min(i - 1, j - 1), min(n - i, n - j));
			int initial = 4 * level * (n - level)+ 1;
			if (i - 1 == level) cout << setw(5) << initial + j - 1 - level;
			else if (n - j == level) cout << setw(5) << initial + n - 2 * level - 1 + i - 1 - level;
			else if (n - i == level) cout << setw(5) << initial + 2 * n - 4 * level - 2 + n - level - j;
			else cout << setw(5) << initial + 3 * n - 6 * level - 3 + n - level - i;
		}
		cout << endl;
	}
}

int main()
{
	for (int n; cin >> n;)
		printMatrix(n);
	return 0;
}