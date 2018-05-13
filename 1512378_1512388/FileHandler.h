#include "QInt.h"
using namespace std;

//Đọc và ghi file
void ProcessedFile(char *input, char* output); 

// Kiểm tra chế độ 1 chỉ thị hay 2
int GetMode(string s);

//Tách các thành phần trong chuỗi
void Split(string arr[],string s);

//Xử lý chế độ 1 chỉ thị
string Mode1Handler(string s); 

//Xử lý chế độ 1 chỉ thị với nhị phân
string Mode1Bin(string arr[]);

//Xử lý chế độ 1 chỉ thị với thập phân
string Mode1Dec(string arr[]); 

//Xử lý chế độ 1 chỉ thị với thập lục phân
string Mode1Hex(string arr[]); 

//Xử lý chế độ 2 chỉ thị
string Mode2Handler(string s); 