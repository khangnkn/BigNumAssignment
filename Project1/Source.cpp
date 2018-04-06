#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class QInt
{
private:
	unsigned __int64 first;
	unsigned __int64 last;
public:
	QInt();
	QInt(string a, int n = 128); // Init QInt from string
	static unsigned __int64 binToUInt64(string a, int n = 64);
	static string UInt64ToBin(unsigned __int64 n);
	static string strBigNumToBin(string str);
	string binary(); //convert QInt to string of binary
	void printDecimal();
	~QInt();
};


bool push2Stack(string str)
{
	int n = str.length();
	return (str[n - 1] - 48) % 2;
}
string DivByTwo(string str)
{
	string result = str;

	int next_add = 0;
	int i = 0;
	for (; i < str.length(); i++)
	{
		int add = next_add;
		if ((str[i] - 48) % 2 != 0)
			next_add = 5;
		else next_add = 0;

		result[i] = ((str[i] - '0') / 2 + add + '0');

	}
	
	//loại các phần tử khác 0 đầu
	while (result[0] == '0' && result.length() != 1)
	{
		result = result.substr(1);
	}
	return result;
}
//Init functions
QInt::QInt()
{
	first = 0;
	last = 0;
}

QInt::QInt(string a, int n)
{
	string b = a.substr(0, 64);
	string c = a.substr(64);
	first = QInt::binToUInt64(b);
	last = QInt::binToUInt64(c);
}

//Convert functions
unsigned __int64 QInt::binToUInt64(string a, int n)
{
	unsigned __int64 last = 0;
	for (int i = 0; i < 64; i++)
	{
		unsigned __int64 temp = (unsigned __int64)(a[63 - i] - 48) << i;
		last = last + temp;
	}
	return last;
}

string QInt::UInt64ToBin(unsigned __int64 n)
{
	string result = "0000000000000000000000000000000000000000000000000000000000000000";
	unsigned __int64 mask = 0x8000000000000000;
	for (int i = 0; i < 64; i++)
	{
		if ((n & mask) != 0) result[i] = '1';
		mask = mask >> 1;
	}
	return result;
}

string QInt::strBigNumToBin(string str)
{
	string bin = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < 128 && str != "0"; i++)
	{
		bin[127 - i] = push2Stack(str) + 48;
		str = DivByTwo(str);
	}
	return string(bin);
}

string QInt::binary()
{
	string part_1 = QInt::UInt64ToBin(first);
	string part_2 = QInt::UInt64ToBin(last);
	string bin = part_1 + part_2;
	return bin;
}

//Output functions;
void QInt::printDecimal()
{
	string part_1 = QInt::UInt64ToBin(first);
	string part_2 = QInt::UInt64ToBin(last);
	string bin = part_1 + part_2;
	cout << bin;
}

QInt::~QInt()
{
}


int main()
{
	string a = "00000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	string num = "1234";
	string str = QInt::strBigNumToBin(num);
	cout << str << endl;
	system("pause");
	return 0;
}
//https://www.codingconnect.net/convert-binary-to-decimal-using-left-shift-operator/