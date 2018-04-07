#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
using namespace std;

typedef bitset<128> binary;

class QInt
{
private:
	binary bit;
public:
	QInt();
	QInt(int mode, string str);
	QInt operator=(QInt const &Qi);
	QInt operator+(QInt Qi);
	~QInt();
//private:
	static string strBigDecToBin(string str);
	static string strBigHexToBin(string str);
	void printBin();
};

int main()
{
	bool a = 1, b = 1;
	cout << (bool)(a + b);
	system("pause");
	return 0;
}

QInt::QInt()
{
}

QInt::QInt(int mode, string str)
{
	if (mode == 2)
		bit = binary(str);
	if (mode == 10)
	{
		string bstr = strBigDecToBin(str);
		bit = binary(bstr);
	}	
	if (mode == 16)
	{
		string hstr = strBigHexToBin(str);
		bit = binary(hstr);
	}
}

QInt QInt::operator=(QInt const & Qi)
{
	this->bit = Qi.bit;
	return Qi;
}

QInt QInt::operator+(QInt Qi)
{
	binary result;
	for (int i = 0; i < 127; i++)
	{
		//result.set(127 - i, )
	}
	return Qi;
}

QInt::~QInt()
{
}

//Private functions.
//These functions support calculating process.
bool carry(string str)
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

string QInt::strBigDecToBin(string str)
{
	string bin = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < 128 && str != "0"; i++)
	{
		bin[127 - i] = carry(str) + 48;
		str = DivByTwo(str);
	}
	return string(bin);
}
string conHexBin(char c)
{
	int swh = c - 48;
	switch (swh)
	{
	case 0:
		return "0000";
	case 1:
		return "0001";
	case 2:
		return "0010";
	case 3:
		return "0011";
	case 4:
		return "0100";
	case 5:
		return "0101";
	case 6:
		return "0110";
	case 7:
		return "0111";
	case 8:
		return "1000";
	case 9:
		return "1001";
	case 17:
		return "1010";
	case 18:
		return "1011";
	case 19:
		return "1100";
	case 20:
		return "1101";
	case 21:
		return "1110";
	case 22:
		return "1111";
	default:
		break;
	}
}
string QInt::strBigHexToBin(string str)
{
	string result = "";
	for (int i = 2; i < str.length(); i++)
	{
		result = result + conHexBin(str[i]);
	}
	return string(result);
}

void QInt::printBin()
{
	cout << bit << endl;
}
