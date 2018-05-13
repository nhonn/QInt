#include "FileHandler.h"

//Xử lý file
void ProcessedFile(char *input, char *output)
{
	ifstream f1(input);
	if (f1.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}
	ofstream f2(output);
	while (!f1.eof()) 
	{
		string line = "";
		string res = "";
		getline(f1, line);
		if (GetMode(line))
			res = Mode1Handler(line);
		else
			res = Mode2Handler(line);
		f2 << res << endl;
	}
	cout << "------->> SUCCCES <<------" << endl;
	f1.close();
	f2.close();
}

// Kiểm tra chuỗi 1 hay 2 chỉ thị
// return 1: 1 chỉ thị (Mode1)
// return 0: 2 chỉ thị (Mode2)
int GetMode(string s)
{
	string temp;
	int i = s.find(' ') + 1;
	for (; i < s.length(); i++)
	{
		if (s[i] != ' ')
			temp += s[i];
		else
			break;
	}
	if (temp != "2" && temp != "10" && temp != "16") 
		return 1;
	return 0;
}

void Split(string arr[], string s)
{
	int j = 0;
	for (int i = 0; i < s.length(); i++)
	{
		arr[j] += s[i];
		if (s[i + 1] == ' ')
		{
			i++;
			j++;
		}
	}
}

//Xử lý chế độ 1 chỉ thị
string Mode1Handler(string s)
{
	int count = 0;								//Số lượng khoảng trắng

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ') count++;
	}

	if (count == 3)
	{
		string arr[] = { "", "", "", "" };
		Split(arr, s);

		//Xử lý
		if (arr[0] == "2")
			return Mode1Bin(arr);
		else if (arr[0] == "10")
			return Mode1Dec(arr);
		else if (arr[0] == "16")
			return Mode1Hex(arr);
		else
			return "Undefined error.";
	}
	else if (count == 2)
	{
		string arr[] = { "", "", "" };
		Split(arr, s);

		//Xử lý
		if (arr[0] == "2")
		{
			QInt a;
			a.StrToQInt(a.BinToDec(arr[2]));  
			if (arr[1] == "ror")
			{
				a.ror();
			}
			else if (arr[1] == "rol")
			{
				a.rol();
			}
			else if (arr[1] == "~")
			{
				~a;
			}
			return a.PrintBinary();
		}
		else if (arr[0] == "10")
		{
			QInt a;
			a.StrToQInt(arr[2]);
			if (arr[1] == "ror")
			{
				a.ror();
			}
			else if (arr[1] == "rol")
			{
				a.rol();
			}
			else if (arr[1] == "~")
			{
				~a;
			}
			return a.PrintQInt();

		}
		else if (arr[0] == "16")
		{
			QInt a;
			a.StrToQInt(a.BinToDec(a.HexToBin(arr[2])));
			if (arr[1] == "ror")
				a.ror();
			else if (arr[1] == "rol")
				a.rol();
			else if (arr[1] == "~")
				~a;
			return a.BinToHex(a.PrintBinary());
		}
	}
}

//Xử lý chế độ 1 chỉ thị với nhị phân
string Mode1Bin(string arr[])
{
	QInt a, b;
	a.StrToQInt(a.BinToDec(arr[1]));

	if (arr[2] == "+")
	{
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a + b;
	}
	else if (arr[2] == "-")
	{
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a - b;
	}
	else if (arr[2] == "*")
	{
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a * b;
	}
	else if (arr[2] == "/")
	{
		while (arr[3][0] == '0'&&arr[3].length() != 1) arr[3].erase(0, 1);
		if (arr[3] == "0") return "Cant divide to 0";
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a / b;
	}
	else if (arr[2] == "&")
	{
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a & b;
	}
	else if (arr[2] == "^")
	{
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a ^ b;
	}
	else if (arr[2] == "|")
	{
		b.StrToQInt(b.BinToDec(arr[3]));
		a = a | b;
	}
	else if (arr[2] == ">>")
	{
		int x = atoi(arr[3].c_str());
		a >> x;
	}
	else if (arr[2] == "<<")
	{
		int x = atoi(arr[3].c_str());
		a << x;
	}
	return a.PrintBinary();
}

//Xử lý chế độ 1 chỉ thị với thập phân
string Mode1Dec(string arr[])
{
	QInt a, b;
	a.StrToQInt(arr[1]);
	b.StrToQInt(arr[3]);
	if (arr[2] == "+")
		a = a + b;
	else if (arr[2] == "-") 
		a = a - b;
	else if (arr[2] == "*")	
		a = a * b;
	else if (arr[2] == "/")
	{
		if (b.PrintQInt() == "0") return "ERROR";
		a = a / b;
	}
	else if (arr[2] == "&")
		a = a & b;
	else if (arr[2] == "^") 
		a = a ^ b;
	else if (arr[2] == "|") 
		a = a | b;
	else if (arr[2] == ">>")
	{
		int x = atoi(arr[3].c_str());
		a >> x;
	}
	else if (arr[2] == "<<")
	{
		int x = atoi(arr[3].c_str());
		a << x;
	}
	return a.PrintQInt();
}

//Xử lý chế độ 1 chỉ thị với thập lục phân
string Mode1Hex(string arr[])
{
	QInt a, b;
	a.StrToQInt(a.BinToDec(a.HexToBin(arr[1])));

	if (arr[2] == "+")
	{
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));
		a = a + b;
	}
	else if (arr[2] == "-")
	{
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));
		a = a - b;
	}
	else if (arr[2] == "*")
	{
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));
		a = a * b;
	}
	else if (arr[2] == "/")
	{
		while (arr[3][0] == '0'&&arr[3].length() != 1) arr[3].erase(0, 1);
		if (arr[3] == "0") return "Cant divide to 0.";
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));	
		a = a / b;
	}
	else if (arr[2] == "&")
	{
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));
		a = a & b;
	}
	else if (arr[2] == "^")
	{
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));
		a = a ^ b;
	}
	else if (arr[2] == "|")
	{
		b.StrToQInt(b.BinToDec(b.HexToBin(arr[3])));
		a = a | b;
	}
	else if (arr[2] == ">>")
	{
		int x = atoi(arr[3].c_str());
		a >> x;
	}
	else if (arr[2] == "<<")
	{
		int x = atoi(arr[3].c_str());
		a << x;
	}
	return a.BinToHex(a.PrintBinary());
}

//Xử lý chế độ 2 chỉ thị
string Mode2Handler(string s)
{
	string arr[3] = { "","","" };
	Split(arr, s);
	if (arr[0] == "2")
	{
		if (arr[1] == "10")
		{
			QInt a;
			return a.BinToDec(arr[2]);
		}
		else if (arr[1] == "16")
		{
			QInt a;
			return a.BinToHex(arr[2]);
		}
	}
	else if (arr[0] == "10")
	{
		if (arr[1] == "2")
		{
			QInt a;
			a.StrToQInt(arr[2]);
			return a.PrintBinary();
		}
		else  if (arr[1] == "16")
		{
			QInt a;
			a.StrToQInt(arr[2]);
			return a.BinToHex(a.PrintBinary());
		}
	}
	else if (arr[0] == "16")
	{
		if (arr[1] == "2")
		{
			QInt a;
			return a.HexToBin(arr[2]);
		}
		else  if (arr[1] == "10")
		{
			QInt a;
			return a.BinToDec(a.HexToBin(arr[2]));
		}
	}
}