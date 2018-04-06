#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
using namespace std;

class QInt
{
private:
	bitset<128> bit;
public:
	QInt();
	QInt(int mode, string str);
	~QInt();
};

int tru(int a, int b)
{
	return a - b;
}

int main()
{
	return 0;
}