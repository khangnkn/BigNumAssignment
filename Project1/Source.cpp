#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
using namespace std;

#define MAXBITS 127
typedef bitset<128> binary;

class QInt
{
private:
	binary bit;
	string tempBit;
	
public:
	QInt();
	QInt(int mode, string str);
	QInt operator=(QInt const &Qi);
	QInt operator+(QInt Qi);
	binary getBits();
	~QInt();
//private:
	static string strBigDecToBin(string str);
	static string strBigHexToBin(string str);
	void printBin();
	static binary addBits(binary first, binary second);
	static binary subtractBits(binary first, binary second);
	static string clearBitZeroes(string bin);
};

int main()
{
	string a = "16";
	string b = "15";
	QInt q1(10, a);
	QInt q2(10, b);
	
	q1.printBin();
	q2.printBin();
	//
	cout << "\nResult: " << QInt::clearBitZeroes(QInt::subtractBits(q1.getBits(), q2.getBits()).to_string());

	cout << "\n";
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
		tempBit = strBigDecToBin(str);
		bit = binary(tempBit);
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

binary QInt::getBits()
{
	return this->bit;
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
	/*while (result[0] == '0' && result.length() != 1)
	{
		result = result.substr(1);
	}*/
	return result;
}

string QInt::strBigDecToBin(string str)
{
	// ASK: nếu str < 0 thì sao?
	string bin = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	if (str[0] != '-')
	{
		for (int i = 0; i < 128 && str != "0"; i++)
		{
			bin[127 - i] = carry(str) + 48;
			str = DivByTwo(str);
		}
	}
	else
	{
		str = str.substr(1);
		str = QInt::strBigDecToBin(str);
		binary tstr(str);
		binary tbin;
		tstr = tstr ^ tbin;

	}
	return bin;
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
	cout << clearBitZeroes(tempBit) << endl;
}

binary QInt::addBits(binary first, binary second)
{
	string str1 = first.to_string();
	string str2 = second.to_string();
	string result;
	int carry = 0; //Initialize carry

	for (int i = MAXBITS; i >= 0; i--)
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

	return binary(result);
}

binary QInt::subtractBits(binary first, binary second)
{
	string str1 = first.to_string();
	string str2 = second.to_string();
	string result;
	int carry = 0; //Initialize carry

	for (int i = MAXBITS; i >= 0; i--)
	{
		int firstBit = str1.at(i) - '0';
		int secondBit = str2.at(i) - '0';
		// boolean expression for sum of 3 bits
		int sub = (firstBit ^ secondBit ^ carry) + '0';

		result = char(sub) + result;

		// boolean expression for 3-bit addition
		if (firstBit == 0 && secondBit == 1)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		
	}


	return binary(result);
}


string QInt::clearBitZeroes(string bin)
{
	string tempBin = bin;

	for (int i = 0; i < MAXBITS; i++)
	{
		if (tempBin[i] == '1')
		{
			tempBin = tempBin.substr(i);
			break;
		}
	}

	return tempBin;
}

