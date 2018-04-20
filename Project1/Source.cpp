#include <iostream>
#include <cmath>
#include <string>
#include <vector>
//#include <sstream>
#include <fstream>
#include <bitset>
#include <fstream>
using namespace std;

#define ONE QInt(10,"1")
#define MAXBITS 127
typedef bitset<128> binary;

class QInt
{
private:
	binary bit;
public:
	//Constructor and Destructor
	QInt();
	QInt(const QInt & index); //all done. works with negative
	QInt(int mode, string str);
	~QInt();
	//Calculating
	QInt operator=(QInt const & index);
	friend QInt operator+(const QInt & first, const QInt & second);
	friend QInt operator-(const QInt & first, const QInt & second);
	friend QInt operator*(const QInt & first, const QInt & second);
	friend QInt operator/(const QInt & first, const QInt & second);
	friend QInt operator&(const QInt & index_1, const QInt & index_2);
	friend QInt operator|(const QInt & index_1, const QInt & index_2);
	friend QInt operator^(const QInt & index_1, const QInt & index_2);
	friend QInt operator~(const QInt & index);
	friend QInt operator>>(const QInt & index, int step);
	friend QInt operator<<(const QInt & index, int step);
	QInt rol();
	QInt ror();
	//Converter
	string convertToDec();
	string convertToHex();
	static string strBigDecToBin(string str);
	static string strBigHexToBin(string str);
	//Input - Output system
	static void runCal(char* input, char* output);
	static void Cal(istream & is, ostream & os);
	void print(int mode, ostream & os);
	//Suporting
	string normalize();
	//Comparison operators
	friend bool operator==(const QInt & first, const QInt & second);
};

void PlusOne(string & result);
void MultByTwo(string & result);
string conHexBin(char c);
string conBinHex(string bstr);

int main(int argc, char** argv)
{
	QInt::runCal(argv[1], argv[2]);
	system("pause");
	return 0;
}

QInt::QInt()
{
}

QInt::QInt(const QInt & index)
{
	this->bit = index.bit;
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

QInt QInt::operator=(QInt const & index)
{
	this->bit = index.bit;
	return QInt(*this);
}

QInt::~QInt()
{
}

string QInt::convertToDec()
{
	string str_bit = bit.to_string();
	string result = "0000000000000000000000000000000000000000\0";	// result hiển thị giá trị thập phân (16 byte ~ 40 kí tự)

																	// đánh dấu bit 1 đầu tiên
	bool negative = (str_bit[0] == '1') ? true : false;
	str_bit = this->normalize();


	// nếu âm
	if (negative)
	{
		QInt abs_bit = *this;
		abs_bit = abs_bit - QInt(10, "1");	// abs_bit là bù 1
		abs_bit.bit = ~(abs_bit.bit);		// abs_bit là thể hiện nhị phân của trị tuyệt đối decimal
		str_bit = abs_bit.normalize();
	}

	int i = 0;
	char add = str_bit[i] - '0';

	while (i < str_bit.length())
	{
		MultByTwo(result);		// nhân 2
		if (add == 1)
			PlusOne(result);	// cộng bit tiếp theo

		i++;
		if (i < str_bit.length())
			add = str_bit[i] - '0';
	}

	// cắt bỏ các số 0 đầu
	i = 0;
	while (result[i] == '0') {
		i++;
	}
	if (negative)
		result = result.substr(i - 1), result[0] = '-';
	else result = result.substr(i);

	return result;
}

string QInt::convertToHex()
{
	string hex_str = bit.to_string();
	string result;
	string tmp_str;
	for (int i = 0; i < MAXBITS; i = i + 4)
	{
		tmp_str = hex_str.substr(i, 4);
		result = result + conBinHex(tmp_str);
	}
	if (result[0] != 'F')
	{
		int i = 1;
		while (result[i] == result[i - 1])
		{
			i++;
		}
		return result.substr(i - 1);
	}
	return result;
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
		for (int i = 0; i <= MAXBITS && str != "0"; i++)
		{
			bin[MAXBITS - i] = carry(str) + 48;
			str = DivByTwo(str);
		}
	}
	else
	{
		str = str.substr(1);
		str = QInt::strBigDecToBin(str);
		QInt tstr(2, str);
		QInt tbin;
		tstr = tstr ^ tbin;
		tbin.bit.set(MAXBITS, 1);
		tstr = tstr + tbin;
		bin = tstr.bit.to_string();
	}
	return bin;
}

string QInt::strBigHexToBin(string str)
{
	string result = "";
	for (int i = 0; i < str.length(); i++)
	{
		result = result + conHexBin(str[i]);
	}
	return string(result);
}


void QInt::runCal(char* input, char* output)
{
	fstream is, os;
	is.open(input, ios::in);
	os.open(output, ios::out);
	while (is.peek() != EOF)
	{
		QInt::Cal(is, os);
		is.peek();
		os << "\n";
	}
	is.close();
	os.close();
}

void QInt::Cal(istream & is, ostream & os)
{
	vector<string> arr_elements;
	QInt val1, val2;
	QInt result;
	int mode, mode_s;
	string op;
	while (is.peek() != '\n' && is.peek() != EOF)
	{
		string tmp;
		is >> tmp;
		arr_elements.push_back(tmp);
	}
	is.seekg(2, ios_base::cur);
	op = arr_elements[arr_elements.capacity() - 2];
	if (op == "+" || op == "-" || op == "*" || op == "/" || op == "&" || op == "|" || op == "^")
	{
		mode = stoi(arr_elements[0]);
		val1 = QInt(mode, arr_elements[1]);
		val2 = QInt(mode, arr_elements[3]);
		switch (op[0])
		{
		case '+':
			result = val1 + val2; break;
		case '-':
			result = val1 - val2; break;
		case '*':
			result = val1 * val2; break;
		case '/':
			result = val1 / val2; break;
		case '&':
			result = val1 & val2; break;
		case '|':
			result = val1 | val2; break;
		case '^':
			result = val1 ^ val2; break;
		default:
			os << "Err\n"; break;
		}
		result.print(mode, os);
		return;
	}
	else if (op == ">>" || op == "<<")
	{
		mode = stoi(arr_elements[0]);
		val1 = QInt(mode, arr_elements[1]);
		int step = stoi(arr_elements[3]);
		if (op == ">>")
			result = val1 >> step;
		else if (op == "<<")
			result = val1 << step;
		else
			cout << "Err\n";
		result.print(mode, os);
		return;
	}
	else if (op == "~" || op == "rol" || op == "ror")
	{
		mode = stoi(arr_elements[0]);
		val1 = QInt(mode, arr_elements[2]);
		if (op == "~")
			result = ~val1;
		else if (op == "rol")
			result = val1.rol();
		else if (op == "ror")
			result = val1.ror();
		else
			cout << "Err\n";
		result.print(mode, os);
		return;
	}
	else
	{
		mode = stoi(arr_elements[0]);
		mode_s = stoi(arr_elements[1]);
		val1 = QInt(mode, arr_elements[2]);
		val1.print(mode_s, os);
		return;
	}
}

void QInt::print(int mode, ostream & os)
{
	if (*this == QInt(2, "0"))
	{
		os << '0';
		return;
	}

	string result;
	if (mode == 2)
	{
		result = this->bit.to_string();
		while (result[0] == '0')
		{
			result = result.substr(1);
		}
	}
	if (mode == 10)
	{
		result = this->convertToDec();
	}
	if (mode == 16)
	{
		result = this->convertToHex();
	}
	os << result;
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

string conBinHex(string bstr)
{
	bitset<4> bs(bstr);
	string result;
	int swt = bs.to_ullong();
	switch (swt)
	{
	case 0:
		result = result + "0"; break;
	case 1:
		result = result + "1"; break;
	case 2:
		result = result + "2"; break;
	case 3:
		result = result + "3"; break;
	case 4:
		result = result + "4"; break;
	case 5:
		result = result + "5"; break;
	case 6:
		result = result + "6"; break;
	case 7:
		result = result + "7"; break;
	case 8:
		result = result + "8"; break;
	case 9:
		result = result + "9"; break;
	case 10:
		result = result + "A"; break;
	case 11:
		result = result + "B"; break;
	case 12:
		result = result + "C"; break;
	case 13:
		result = result + "D"; break;
	case 14:
		result = result + "E"; break;
	case 15:
		result = result + "F"; break;
	default:
		break;
	}
	return result;
}

string QInt::normalize()
{
	string str_bits = bit.to_string();

	int i = 1;
	while (str_bits[i] == str_bits[i - 1]) i++;

	return str_bits.substr(i);
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

bool operator==(const QInt & first, const QInt & second)
{
	int i = 0;
	while (i <= MAXBITS)
	{
		if (first.bit.to_string()[i] != second.bit.to_string()[i])
			return false;
		i++;
	}
	return true;
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

	return QInt(2, result);
}

QInt operator-(const QInt & first, const QInt & second)
{
	return first + (~second + QInt(10, "1"));
}

QInt operator*(const QInt & first, const QInt & second)
{
	string str1 = first.bit.to_string();
	string str2 = second.bit.to_string();
	string result = QInt(10, "0").bit.to_string();

	// xây dựng chuỗi kết quả
	int carry = 0;
	for (int i = str1.length() - 1; i >= 0; i--, carry = 0)
	{
		for (int j = str2.length() - 1; j >= 0; j--)
		{
			int pos = j - (str1.length() - 1 - i);
			if (pos >= 0)
			{
				int temp = carry + (result[pos] - '0');
				temp += (str1[i] == '0') ? 0 : str2[j] - '0';

				result[pos] = temp % 2 + '0';

				if (temp > 1)
				{
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				temp = 0;
			}
		}
	}


	return QInt(2, result);
}

QInt operator/(const QInt & first, const QInt & second)
{
	if (second == QInt(10, "0"))
	{
		cout << "Error: divided by 0\n";
		return second;
	}

	string str1 = first.bit.to_string();
	string str2 = second.bit.to_string();
	string result;

	// xét first, second cùng hay khác dấu
	bool neg = ((str1[0] != '0'&&str2[0] == '0') || (str1[0] == '0'&&str2[0] != '0')) ? true : false;

	// chuẩn hóa, đưa về trị tuyệt đối
	if (str1[0] == '1')
	{
		QInt abs_bit = first - QInt(10, "1");	// abs_bit là bù 1
		abs_bit.bit = ~(abs_bit.bit);			// abs_bit là thể hiện nhị phân của trị tuyệt đối decimal
		str1 = abs_bit.bit.to_string();
	}
	int i = 1;
	while (str1[i] == str1[i - 1]) i++;
	str1 = str1.substr(i);


	if (str2[0] == '1')
	{
		QInt abs_bit = second - QInt(10, "1");	// abs_bit là bù 1
		abs_bit.bit = ~(abs_bit.bit);			// abs_bit là thể hiện nhị phân của trị tuyệt đối decimal
		str2 = abs_bit.bit.to_string();
	}
	i = 1;
	while (str2[i] == str2[i - 1]) i++;
	str2 = str2.substr(i);

	// xây dựng chuỗi kết quả
	i = str2.length();
	string temp = str1.substr(0, i);
	while (i <= str1.length())
	{
		char add = ((temp.length() > str2.length()) || (temp.length() == str2.length() && temp >= str2)) ? '1' : '0';
		result += add;
		if (add == '1')
		{
			QInt qtemp(2, temp);
			QInt qstr2(2, str2);
			temp = (qtemp - qstr2).normalize();
		}

		temp += str1[i];
		i++;
	}

	// nếu số bị chia nhỏ hơn số chia
	if (str1.length() < str2.length())
		return QInt(10, "0");

	if (!neg)
		return QInt(2, result);
	else
		return ~QInt(2, result) + QInt(10, "1");	// bù 2
}

QInt operator&(const QInt & index_1, const QInt & index_2)
{
	QInt result;
	result.bit = index_1.bit & index_2.bit;
	return QInt(result);
}

QInt operator|(const QInt & index_1, const QInt & index_2)
{
	QInt result;
	result.bit = index_1.bit | index_2.bit;
	return QInt(result);
}

QInt operator^(const QInt & index_1, const QInt & index_2)
{
	QInt result;
	result.bit = index_1.bit ^ index_2.bit;
	return QInt(result);
}

QInt operator~(const QInt & index)
{
	QInt result;
	result.bit = ~index.bit;
	return QInt(result);
}

QInt operator>>(const QInt & index, int step)
{
	QInt result;
	result.bit = index.bit >> step;
	return QInt(result);
}

QInt operator<<(const QInt & index, int step)
{
	QInt result;
	result.bit = index.bit << step;
	return QInt(result);
}

QInt QInt::rol()
{
	QInt result;
	result = *this << 1;
	result.bit.set(0, 1);
	int i = MAXBITS;
	while (result.bit[i] == 0) i--;
	result.bit.set(i, 0);
	return QInt(result);
}

QInt QInt::ror()
{
	QInt result;
	bool index;
	index = this->bit[0];
	result = *this >> 1;
	if (index == 1)
	{
		int i = MAXBITS;
		while (result.bit[i] == 0)
			i--;
		result.bit.set(i + 1, index);
	}
	return QInt(result);
}
