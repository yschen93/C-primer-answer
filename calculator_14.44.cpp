#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

int add(int a, int b)
{
	return a + b;
}

auto mod = [](int a, int b){return a % b; };

struct divide
{
	int operator()(int a, int b)
	{
		return a / b;
	}
};

map<string, function<int(int, int)> > calculator =
{
	{ "+", add },
	{ "-", minus<int>() },
	{ "*", [](int a, int b){return a * b; } },
	{ "/", divide() },
	{ "%", mod }
};

int main()
{
	string s;
	while (cin >> s)
	{
		int a, b;
		cin >> a >> b;
		cout << calculator[s](a, b) << endl;
	}

	system("pause");
	return 0;
}
