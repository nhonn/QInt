#pragma once
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

class QInt
{
private:
	int A[4];
public:
	QInt();
	~QInt();

	//Chia chuỗi cho 2
	string StrDiv2(string s);			

	//Bật bit
	void TurnOnBit(int &x, int i);		

	//Tắt bit
	void TurnOffBit(int &x, int i);		

	//Gán bit
	void SetBitI(int bit, int i);		

	//Cộng QInt với 1
	void SumWith1();					

	//Lấy bit thứ i
	int GetBitI(int x, int i);

	//Chuẩn hóa độ dài 2 chuỗi
	void Standardize(string &a, string &b);		

	//Cộng chuỗi
	string Sum(string a, string b);				

	//Trừ chuỗi
	string Sub(string a, string b);				

	//Nhân ký tự với chuỗi
	string Multiply(char a, string b);

	//Chuyển sang nhị phân đưa vào QInt
	void StrToQInt(string s);		

	//Kiểm tra số âm
	bool IsNagative();

	//In ra số QInt
	string PrintQInt();		

	//Hàm in ra số dưới dạng nhị phân
	string PrintBinary();

	//Chuyển từ dãy nhị phân sang thập lục phân
	string BinToHex(string);		

	//Chuyển từ dãy nhị phân sang thập phân
	string BinToDec(string);

	//Chuyển từ dãy thập lục phân sang nhị phân
	string HexToBin(string); 

	//Toán tử gán
	QInt& operator = (const QInt&); 
	
	//Toán tử cộng
	QInt operator + (const QInt&); 

	//Toán tử trừ
	QInt operator - (const QInt&);	

	//Toán tử nhân
	QInt operator * (const QInt&);		

	//Toán tử chia
	QInt operator / (const QInt&);	
	
	//Toán tử AND
	QInt operator & (const QInt&);	

	//Toán tử OR
	QInt operator | (const QInt&);	

	//Toán tử XOR
	QInt operator ^ (const QInt&);	

	//Toán tử NOT
	QInt& operator ~ ();		

	//Dịch phải 1 bit
	void ShiftRight1Bit();

	//Dịch trái 1 bit
	void ShiftLeft1Bit();

	//Dịch phải k bit
	QInt& operator >> (int);

	//Dịch trái k bit
	QInt& operator << (int);	

	//Phép xoay trái
	QInt& rol();	

	//Phép xoay phải
	QInt& ror();
};