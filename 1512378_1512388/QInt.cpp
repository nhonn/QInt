#include "QInt.h"


QInt::QInt()
{
	A[0] = 0, A[1] = 0, A[2] = 0, A[3] = 0;  //Khởi tạo giá trị mặc định
}

QInt::~QInt()
{
}

string QInt::StrDiv2(string s)
{	
	string a = "";
	int len = s.length();				//Lấy giá trị độ dài của chuỗi

	int tmp = s[0] - 48;				

	string x;

	for (int i = 0; i < len; i++)		//Thực hiện chia
	{
		x = (tmp / 2) + 48;			
		a = a + x;
		tmp = (tmp % 2) * 10 + (s[i + 1] - 48);
	}
	if (a.length()>1 && a[0] == '0')
		a.erase(0, 1);					//Xóa ký tự 0 đầu chuỗi
	return a;
}

void QInt::TurnOnBit(int &x, int i)		//Bật bit
{
	int temp = 1;
	temp = temp << i;
	x = temp | x;
}
void QInt::TurnOffBit(int &x, int i)	//Tắt bit 
{
	int temp = 1;
	temp = temp << i;
	x = ~(temp)&x;
}
void QInt::SetBitI(int bit, int i)		//Gán bit
{
	i = 127 - i;
	int x, j;
	if (i >= 0 && i <= 31)			//Xác định vị trí của i trên phần tử nào của biến QInt
	{
		j = i;
		if (bit == 1)
		{
			TurnOnBit(this->A[3], j);
		}
	}
	else if (i >= 32 && i <= 63)
	{
		j = i - 32;
		if (bit == 1)
		{
			TurnOnBit(this->A[2], j);
		}
	}
	else if (i >= 64 && i <= 95)
	{
		j = i - 64;
		if (bit == 1)
		{
			TurnOnBit(this->A[1], j);
		}
	}
	else
	{
		j = i - 96;
		if (bit == 1)
		{
			TurnOnBit(this->A[0], j);
		}
	}
}

//Trả về giá trị của bit thứ i
int QInt::GetBitI(int x, int i) 
{
	x = (x >> i) & 1;
	return x;
}
void QInt::SumWith1()
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 32; j++)
		{
			if (GetBitI(this->A[i], j) == 1)
				TurnOffBit(this->A[i], j);
			else
			{
				TurnOnBit(this->A[i], j);
				return;
			}
		}
	}
}

void QInt::StrToQInt(string s)			//Chuyển xâu nhập vào thành nhị phân
{
	int temp = 0;
	if (s[0] == '-')				
	{
		temp = 1;
		s.erase(0, 1);					//Cắt dấu '-' ra khỏi chuỗi
	}
	int i = 127;
	while (s != "0")
	{
		int bit = (s[s.length() - 1] - 48) % 2;
		this->SetBitI(bit, i);
		s = StrDiv2(s);
		i--;
	}
	if (temp==1)						//Nếu là số âm thì chuyển sang bù 2
	{
		~*this;
		SumWith1();
	}
}

bool QInt::IsNagative()
{
	if (GetBitI(this->A[0], 31) == 1)
		return true;
	return false;
}

void QInt::Standardize(string &a, string &b)	
{
	int len1 = a.length();
	int len2 = b.length();
	if (len1 >= len2)
	{
		b.insert(0, len1 - len2, '0');			//Chèn chuỗi '0' vào đầu chuỗi
	}
	else
	{
		a.insert(0, len2 - len1, '0');			//Chèn chuỗi '0' vào cuối chuỗi
	}
}

string QInt::Sum(string a, string b)			//Cộng 2 số
{
	string s = "";
	Standardize(a, b);							//Chuẩn hóa chuỗi
	int l = a.length();

	int temp = 0;
	for (int i = l - 1; i >= 0; i--)   
	{
		temp = (a[i] - 48) + (b[i] - 48) + temp;
		s.insert(0, 1, (temp % 10) + 48);
		temp = temp / 10;
	}
	if (temp>0)
	{
		s.insert(0, 1, temp + 48);
	}
	return s;
}

string QInt::Sub(string a, string b)
{
	string s = "";
	Standardize(a, b);							 // Chuẩn hóa
	int l = a.length();

	int temp = 0;
	for (int i = l - 1; i >= 0; i--)
	{
		if ((a[i] - 48) >= ((b[i] - 48) + temp))
		{
			temp = (a[i] - 48) - (b[i] - 48) - temp;
			s.insert(0, 1, temp + 48);
			temp = 0;
		}
		else
		{
			temp = (a[i] - 48) + 10 - (b[i] - 48) - temp;
			s.insert(0, 1, temp + 48);
			temp = 1;
		}
	}
	while (s[0] == '0')
	{
		s.erase(0, 1);
	}
	return s;
}


//Nhân chuỗi với ký tự 1 số
string QInt::Multiply(char a, string b)
{
	string s = "";
	int temp = 0;
	for (int i = b.length() - 1; i >= 0; i--)
	{
		temp = (a - 48) * (b[i] - 48) + temp;
		s.insert(0, 1, (temp % 10) + 48);
		temp = temp / 10;
	}

	if (temp>0)
	{
		s.insert(0, 1, temp + 48);
	}
	return s;
}

//In số QInt ở dạng thập phân
string QInt::PrintQInt()				
{
	int tmp = 127;
	string s = "";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 31; j >= 0; j--)
		{
			if (GetBitI(this->A[i], j) == 1)
			{
				string temp = "1";
				for (int k = 1; k <= tmp; k++)
				{
					temp = Multiply('2', temp);
				}
				s = Sum(s, temp);
			}
			tmp--;
		}
	}
	if (IsNagative())
	{
		string temp = "1";
		for (int k = 1; k <= 127; k++)
		{
			temp = Multiply('2', temp);
		}
		s = Sub(s, temp);
		s = Sub(temp, s);
		s.insert(0, 1, '-');
	}
	if (s == "") s.insert(0, 1, '0');
	return s;
}

//In số QInt ở dạng nhị phân
string QInt::PrintBinary()
{
	string result = "";
	for (int i = 0; i < 4; i++)
		for (int j = 31; j >= 0; j--)
			result+=GetBitI(A[i], j)+48;

	while (result[0] == '0'&&result.length()!=1) result.erase(0, 1);
	return result;
}

//Chuyển số QInt từ nhị phân sang thập lục phân
string QInt::BinToHex(string b)
{
	string t;
	for (int i = 0; i < 128; i++)
	{
		t += "0";
	}
	Standardize(b, t);
	char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	string result = "";
	string temp = "";
	for (int j = b.length()-1;j>=0;)
	{
		// Tạo xâu chứa dãy nhị phân 4 bit
		while (temp.length() != 4)
		{
			temp.insert(0, 1, b[j]);
			j--;
		}
		// Chuyển dãy nhị phân 4 bit sang dạng thập phân
		if (temp.length() == 4)
		{
			int tmp = 0;
			for (int k = 0; k < 4; k++)
				if (temp[temp.length() - k - 1] == '1')
					tmp += pow(2, k);
			result.insert(0, 1, hex[tmp]);
			temp = "";
		}
	}
	while (result[0] == '0'&&result.length() != 1) result.erase(0, 1);
	
	return result;
}

//Chuyển từ thập lục phân sang nhị phân
string QInt::HexToBin(string h)
{
	string result = "";
	string bin[] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010"
		, "1011", "1100", "1101", "1110", "1111" };
	for (int i = 0; i < h.length(); i++)
	{
		switch (h[i])
		{
		case '0': case '1': case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			result += bin[h[i]-48]; break;
		case 'A': result += bin[10]; break;
		case 'B': result += bin[11]; break;
		case 'C': result += bin[12]; break;
		case 'D': result += bin[13]; break;
		case 'E': result += bin[14]; break;
		case 'F': result += bin[15]; break;
		}
	}

	return result;
}

//Chuyển từ hệ nhị phân sang thập phân
string QInt::BinToDec(string b)
{
	int tmp = b.length()-1;
	string result = "";
	for (int i = 0; i < b.length(); i++)
	{
		if (b[i] == '1')
		{
			string temp = "1";
			for (int k = 1; k <= tmp; k++)
			{
				temp = Multiply('2', temp);
			}
			result = Sum(result, temp);
		}
		tmp--;
	}
	if (b.length()==128&&b[0]=='1')
	{
		string temp = "1";
		for (int k = 1; k <= 127; k++)
		{
			temp = Multiply('2', temp);
		}
		result = Sub(result, temp);
		result = Sub(temp, result);
		result.insert(0, 1, '-');
	}
	return result;
}

//Toán tử cộng
QInt QInt::operator+(const QInt& x)
{
	QInt temp = x;
	QInt result;
	int memory = 0; int tmp = 127;
	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j <32; j++) {
			int kq = this->GetBitI(this->A[i], j) + temp.GetBitI(temp.A[i], j);
			switch (kq) {
			case 0:
				if (memory == 0) {
					result.SetBitI(0, tmp);
					tmp--;
					break;
				}
				else if (memory == 1) {
					result.SetBitI(1, tmp);
					tmp--;
					memory = 0;
					break;
				}
			case 1:
				if (memory == 0) {
					result.SetBitI(1, tmp);
					tmp--;
					break;
				}
				else if (memory == 1) {
					result.SetBitI(0, tmp);
					tmp--;
					break;
				}
			case 2:
				if (memory == 0) {
					result.SetBitI(0, tmp);
					memory = 1;
					tmp--;
					break;
				}
				else if (memory == 1) {
					result.SetBitI(1, tmp);
					tmp--;
					break;
				}
			}
		}
	}
	return result;
}

// Toán tử trừ
QInt QInt::operator-(const QInt &x)
{
	QInt temp = x;
	QInt result;
	~temp;
	temp.SumWith1();
	result = *this + temp;
	return result;
}

//Toán tử nhân
QInt QInt::operator*(const QInt &x)
{
	QInt result = x;
	int tmp = 0;
	QInt A;
	int k = 128;
	while (k > 0)
	{
		int lowestBit = GetBitI(result.A[3], 0);				//Lấy bit nhỏ nhất của Q
		if (lowestBit == 1 && tmp == 0)
		{
			A = A - *this;
		}
		else if (lowestBit == 0 && tmp == 1)
		{
			A = A + *this;
		}
		tmp = lowestBit;
		result >> 1;
		int bit0A = GetBitI(A.A[3], 0);					//Lấy bit nhỏ nhất của A			
		if (bit0A == 1)									//Nếu bit cuối của A là 1
			TurnOnBit(result.A[0], 31);						//Bật bit đầu của Q thành 1
		else TurnOffBit(result.A[0], 31);
		A >> 1;
		k--;
	}
	return result;
}

//Toán tử chia
QInt QInt::operator/(const QInt &x)
{
	QInt A;
	QInt tmp = x;
	QInt result = *this;
	if (tmp.PrintQInt() == "0")
	{
		return tmp;
	}
	int k = 128;
	int sign1 = GetBitI(result.A[0], 31);		//Lấy bit dấu của result
	int sign2 = GetBitI(tmp.A[0], 31);			//Lấy bit dấu của số bị chia
	if (sign1 == 1)								//Nếu result là số âm thì chuyển sang bù 2
	{
		~result;
		result.SumWith1();
	}	
	if (sign2 == 1)								//Nếu là số âm thì chuyển sang bù 2
	{
		~tmp;
		tmp.SumWith1();
	}
	while (k > 0)
	{
		int temp = GetBitI(result.A[0], 31);
		result << 1;
		A << 1;
		if (temp == 1) TurnOnBit(A.A[3], 0);
		else TurnOffBit(A.A[3], 0);
		A = A - tmp;
		if (GetBitI(A.A[0], 31) == 1)
		{
			TurnOffBit(result.A[3], 0);
			A = A + tmp;
		}	
		else TurnOnBit(result.A[3], 0);
		k--;
	}
	if (sign1 != sign2)
	{
		~result;
		result.SumWith1();
	}
	return result;
}

//Toán tử gán bằng
QInt& QInt::operator=(const QInt& Q)
{
	if (this != &Q)
	{
		for (int i = 0; i < 4; i++)
		{
			A[i] = Q.A[i];
		}
	}
	return *this;
}

//Toán tử AND
QInt QInt::operator&(const QInt& Q)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.A[i] = A[i] & Q.A[i];
	}
	return temp;
}

//Toán tử OR
QInt QInt::operator|(const QInt& Q)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.A[i] = A[i] | Q.A[i];
	}
	return temp;
}

//Toán tử XOR
QInt QInt::operator^(const QInt& Q)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.A[i] = A[i] ^ Q.A[i];
	}
	return temp;
}

//Toán tử NOT
QInt& QInt::operator~()
{
	int temp = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			temp = temp << j;
			A[i] = A[i] ^ temp;
			temp = 1;
		}
	}
	return *this;
}

void QInt::ShiftRight1Bit()
{
	A[3] = A[3] >> 1;							//Dịch sang phải 1 bit của 32 bit nhỏ nhất

	for (int i = 2; i >= 0; i--)
	{
		int temp = GetBitI(A[i], 0);			//Lấy giá trị bit thứ 0 của phần A[i]

		if (temp == 1)
		{
			TurnOnBit(A[i + 1], 31);			//Bật bit thứ ...... của A[i+1]
		}
		else TurnOffBit(A[i + 1], 31);			//Tăt bit thứ ...... của A[i+1]

		A[i] = A[i] >> 1;						// Dịch sang phải 1 bit của 32 bit phần hiện tại
	}
}

void QInt::ShiftLeft1Bit()
{
	A[0] = A[0] << 1;							//Dịch sang trái 1 bit của 32 bit nhỏ nhất

	for (int i = 1; i <= 3; i++)
	{
		int temp = GetBitI(A[i], 31);			//Lấy giá trị bit thứ 31 của phần A[i]
		if (temp == 1)
			TurnOnBit(A[i - 1], 0);				
		else TurnOffBit(A[i - 1], 0);			
		A[i] = A[i] << 1;						
	}
}

//Dịch phải k bit
QInt& QInt::operator>>(int k)
{
	for (int i = 0; i < k; i++)
	{
		this->ShiftRight1Bit();
	}

	return *this;
}

//Dịch trái k bit
QInt& QInt::operator<<(int k)
{
	for (int i = 0; i < k; i++)
	{
		this->ShiftLeft1Bit();
	}

	return *this;
}

//Phép xoay trái
QInt& QInt::rol()
{
	int temp = GetBitI(A[0],31);
	*this << 1;
	if (temp == 1) TurnOnBit(A[3], 0);
	else TurnOffBit(A[3], 0);
	return *this;
}

//Phép xoay phải
QInt& QInt::ror()
{
	int temp = GetBitI(A[3], 0);
	*this >> 1;
	if (temp == 1) TurnOnBit(A[0], 31);
	else TurnOffBit(A[0], 31);
	return *this;
}