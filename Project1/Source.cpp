#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <bitset>
using namespace std;

#define ONE QInt(10,"1");

typedef bitset<128> binary;

// acctually, QInt is a big binary
class QInt
{
private:
	bitset<128> bit;
public:
	QInt();
	QInt(int mode, string str);
	~QInt();
	string convertToDec();
	string convertToHex();

	QInt & operator=(const QInt & index);
	friend QInt operator+(const QInt & first, const QInt & second);
	//private:
	static string strBigDecToBin(string str);
	static string strBigHexToBin(string str);
	string normalize();

};

void PlusOne(string & result);
void MultByTwo(string & result);

int main()
{
	string str_bits = "";
	QInt index(10, str_bits);

	cout << index.normalize() << endl << index.normalize().length();
	system("pause");
	return 0;
}

QInt::QInt()
{
	int i = 0;
	while (i < 128)
	{
		bit[i] = 0;
	}
}

QInt::QInt(int mode, string str)
{
	if (mode == 2)
		bit = bitset<128>(str);
	if (mode == 10)
	{
		bool negative = (str[0] == '-') ? true : false;

		// nếu âm
		if (negative)
		{
			str = str.substr(1);	// cắt bỏ '-' trong str
		}
		str = strBigDecToBin(str);
		bit = bitset<128>(str);	// chuyển bit

		if (negative)
		{
			bit = ~bit;				// bù 1
			*this = *this + ONE;	// bù 2
		}
	}
	if (mode == 16)
	{
		string hstr = strBigHexToBin(str);
		bit = bitset<128>(hstr);
	}
}

QInt::~QInt()
{
}

string QInt::convertToDec()
{
	string str_bit = bit.to_string();
	string result = "0000000000000000000000000000000000000000\0";	// result hiển thị giá trị thập phân (16 byte ~ 40 kí tự) 

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
		if (add == 1)
			PlusOne(result);	// cộng bit tiếp theo

		i++;
		add = str_bit[i] - '0';
	}

	// loại bỏ các phần tử 0 đầu
	while (result[0] == '0' && result.length() != 1)
	{
		result = result.substr(1);
	}

	return result;
}

string QInt::convertToHex()
{
	string str_bits = bit.to_string();

	// chuẩn hóa dãy bit (nhóm 4 bit)
	int i = 0, pos = 0;
	while (str_bits[i] == '0')
	{
		if ((str_bits.length() - i - 1) % 4 == 0)
			pos = i;
		i++;
	}

	str_bits = str_bits.substr(pos + 1, str_bits.length() - pos);

	string result = "00000000000000000000000000000000\n";
	// xuất chuỗi thập lục phân
	i = 0;
	int temp = 0;
	int add = 0;
	while (i < str_bits.length())
	{
		temp = temp * 2 + add;

		if ((i + 1) % 4 == 0)
		{
			if (temp <= 9)
			{
				result[(i + 1) / 4 - 1] = temp + '0';
			}
			else
			{
				switch (temp)
				{
				case 10: result[(i + 1) / 4 - 1] = 'A'; break;
				case 11: result[(i + 1) / 4 - 1] = 'B'; break;
				case 12: result[(i + 1) / 4 - 1] = 'C'; break;
				case 13: result[(i + 1) / 4 - 1] = 'D'; break;
				case 14: result[(i + 1) / 4 - 1] = 'E'; break;
				default: result[(i + 1) / 4 - 1] = 'F'; break;
				}
			}
			temp = 0;
		}
		i++;
		add = str_bits[i] - '0';
	}

	result = result.substr(0, str_bits.length() / 4);

	return result;
}

QInt & QInt::operator=(const QInt & index)
{
	int i = 0;

	while (i < 128)
	{
		this->bit[i] = index.bit[i];
		i++;
	}

	return *this;
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

string QInt::normalize()
{
	string str_bits = bit.to_string();
	int i = 0;
	int pos = i;

	while (str_bits[i] == str_bits[i + 1])
	{
		if ((str_bits.length() - i - 1) % 4 == 0)
			pos = i;
		i++;
	}
	return str_bits.substr(pos + 1);
}

void MultByTwo(string & result)
{
	string copy = result;
	int i = result.length() - 1;
	int carry = 0;
	while (i >= 0)
	{
		copy[i] = ((result[i] - '0') * 2 + carry) % 10 + '0';
		carry = (((result[i] - '0') * 2) > 9) ? 1 : 0;
		i--;
	}

	result = copy;
}

void PlusOne(string & result)
{
	int i = result.length() - 1;
	int carry = 1;

	while (carry != 0)
	{
		int temp = result[i] - '0' + carry;
		result[i] = (result[i] - '0' + carry) % 10 + '0';
		carry = temp / 10;
	}
}

QInt operator+(const QInt & first, const QInt & second)
{
	string str1 = first.bit.to_string();
	string str2 = second.bit.to_string();
	string result;
	int carry = 0; //Initialize carry

	for (int i = 127; i >= 0; i--)
	{
		int firstBit = str1.at(i) - '0';
		int secondBit = str2.at(i) - '0';
		// boolean expression for sum of 3 bits
		int sum = (firstBit ^ secondBit ^ carry) + '0';

		result = char(sum) + result;

		// boolean expression for 3-bit addition
		carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
	}
	if (carry)
	{
		result = '1' + result;
	}

	return QInt(2, result);
}