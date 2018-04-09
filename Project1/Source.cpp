#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
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
	friend QInt operator+(QInt Qi_1, QInt Qi_2);
	~QInt();
	void convertToDec();
//private:
	static string strBigDecToBin(string str);
	static string strBigHexToBin(string str);
	void printBin();
		
};

void PlusOne(string & result);
void MultByTwo(string & result);

int main()
{
	string a = "1526";
	string b = "0x123";
	QInt m(10, a);
	QInt n(16, b);
	cout << a;
	cout << b;

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



QInt::~QInt()
{
}

void QInt::convertToDec()
{
	string str_bit = bit.to_string();

	bitset<40> ZERO;

	string result = ZERO.to_string();

	// đánh dấu bit 1 đầu tiên
	int i = 0;
	while (i < str_bit.length() && str_bit[i] == 48)
	{
		i++;
	}
	
	// duyệt chuỗi nhị phân từ trái sang phải
	char add = str_bit[i] - '0';

	while (i < 128)
	{
		MultByTwo(result);		// nhân 2
		if(add==1)
			PlusOne(result);	// cộng bit tiếp theo

		i++;
		add = str_bit[i] - '0';
	}

	// loại bỏ các phần tử 0 đầu
	while (result[0] == '0' && result.length() != 1)
	{
		result = result.substr(1);
	}

	cout << result;
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
	// ASK: nếu str < 0 thì sao?
	string bin = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < 128 && str != "0"; i++)
	{
		bin[127 - i] = carry(str) + 48;
		str = DivByTwo(str);
	}
	//loại các phần tử khác 0 đầu
	while (bin[0] == '0' && bin.length() != 1)
	{
		bin = bin.substr(1);
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
	// ASK: theo yêu cầu của thầy là không in những số 0 đầu?
	 cout << bit << endl;
}

void MultByTwo(string & result)
{
	string copy = result;
	int i = result.length() - 1;
	int carry = 0;
	while (i >= 0)
	{
		copy[i] = ((result[i] - '0') * 2  + carry) % 10 + '0';
		carry = (((result[i] - '0') * 2) > 9) ? 1 : 0;
		i--;
	}

	result = copy;
}

QInt operator+(QInt Qi_1, QInt Qi_2)
{
	QInt qResult;
	while (Qi_2.bit.to_ullong() != 0)
	{
		binary carry = Qi_1.bit & Qi_2.bit;
		Qi_1.bit = Qi_1.bit ^ Qi_2.bit;
		Qi_2.bit = carry << 1;
	}

	return QInt(Qi_1);
}
void PlusOne(string & result)
{
	int i = result.length() - 1;
	int carry = 1;

	while (carry!=0)
	{
		int temp = result[i] - '0' + carry;
		result[i] = (result[i] - '0' + carry) % 10 + '0';
		carry = temp / 10;
	}
}