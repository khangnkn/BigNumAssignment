#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
using namespace std;

typedef bitset<128> binary;

class QInt
{
private:
	bitset<128> bit;
public:
	QInt();
	QInt(int mode, string str);
	~QInt();
};

int main()
{
	return 0;
}