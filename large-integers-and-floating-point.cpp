#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>

using namespace std;

#define MAX 4
#define BIN_MAX 128

//S? bin c?ng 1
string binCong1(string& Q)
{
	string temp = Q;
	//Ý tu?ng ta duy?t t? cu?i m?ng v? n?u g?p 1 thì d?i thành 0, n?u g?p 0 thì d?i thành 1 và break
	for (int i = temp.length() - 1; i >= 0; i--)
	{
		if ((temp[i] - 48) == 1)
		{
			temp[i] = 48;
		}
		else
		{
			temp[i] = 49;
			break;
		}
	}
	return temp;
}

//S? bin tr? 1
string binTru1(string& Q)
{
	string temp = Q;
	//Ý tu?ng duy?t t? cu?i m?ng v? n?u g?p 0 thì d?i thành 1, n?u g?p 1 thì d?i thành 0 và break
	for (int i = temp.length() - 1; i >= 0; i--)
	{
		if ((temp[i] - 48) == 0)
		{
			temp[i] = 49;
		}
		else
		{
			temp[i] = 48;
			break;
		}
	}
	return temp;
}

//L?y bù 1 c?a chu?i bin, 0->1 và 1->0
string Bu1(string& Q)
{
	string tmp = Q;
	for (int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] - 48 == 0)
		{
			tmp[i] = 49;
		}
		else
		{
			tmp[i] = 48;
		}
	}
	return tmp;
}

//Chuy?n t? nh? phân sang th?p l?c phân
string binToHex(string& Q)
{
	string temp = Q;
	string res = "";	//Chu?i k?t qu?
	string s = "0123456789ABCDEF"; //Tuong ?ng 0='0', ..., 10='A' , ..., 15='F'
	int n = temp.length();
	//Ý tu?ng là ta s? chia ra t?ng c?m 4 bit d? chuy?n v? Hex
	//N?u s? lu?ng bit không chia h?t cho 4 thì ta thêm bit 0 vào d?u chu?i
	if (n % 4 != 0)
	{
		temp.insert(0, 4 - n % 4, '0');
	}
	n = temp.length();
	int k = n - 1;
	for (int i = 0; i < n / 4; i++) //S? l?n duy?t là n/4
	{
		int t = 0;
		for (int j = 0; j < 4; j++)	//M?i l?n l?y 4 bit chuy?n sang Hex
		{
			t = t | (temp[k] - 48)*(1 << j);
			k--;
		}
		res = s[t] + res;
	}
	while (res[0] == '0') //VD: Khi chu?i Hex là 0000AF9 thì chuy?n thành AF9
	{
		res.erase(0, 1);
	}
	return res;
}

//C?ng 2 s? th?p phân
string decPlusDec(string& A, string& B)
{
	int na = A.length(); //Ð? dài chu?i A
	int nb = B.length(); //Ð? dài chu?i B
						 //Làm cho d? dài A và B b?ng nhau
	if (na > nb)
	{
		B.insert(0, na - nb, '0');
	}
	else if (nb > na)
	{
		A.insert(0, nb - na, '0');
	}
	string res; //Chu?i k?t qu?
	int n = A.length(); //n là d? dài 2 chu?i sau khi làm thành b?ng nhau
	int du = 0;
	string s = "0123456789"; //Tuong ?ng 0='0', ..., 9='9'
							 //Ý tu?ng th?c hi?n phép c?ng nhu s?p phép tính c?ng trên gi?y c?ng tay
	for (int i = n - 1; i >= 0; i--)
	{
		int t = A[i] + B[i] - 2 * 48 + du;
		res = s[t % 10] + res;
		du = t / 10;
	}
	if (du != 0) //L?y ph?n du cu?i cùng dua vào res
	{
		res = s[du % 10] + res;
	}
	int j = res.length();
	if (j == 0)
	{
		res += "0";
	}
	return res;
}

//l?y 1 s? th?p nhân 2
string decMulTwo(string& Q)
{
	//A x 2 = A + A
	string res = decPlusDec(Q, Q);
	return res;
}

//2^n
string twoPowDec(int x)
{
	string res = "1"; //Giá tr? kh?i t?o là 1
					  //Ý tu?ng 2^2 = ?
					  //a = 1
					  //a = a + a = 2
					  //a = a + a = 2 + 2 = 4 = 2^2
	for (int i = 0; i < x; i++)
	{
		res = decMulTwo(res);
	}
	return res;
}

//Chuy?n t? nh? phân sang th?p phân
string binToDec(string& Q)
{
	string res = ""; //Chu?i k?t qu?
	int n = Q.length();
	string temp = Q;
	if (Q[0] - 48 != 0)	//Ki?m tra s? nh?p vào có ph?i s? âm không, n?u âm chuy?n sang d?ng bù 2
	{
		temp = binTru1(temp);
		temp = Bu1(temp);
	}
	for (int i = 0; i < temp.length(); i++)
	{
		if (temp[temp.length() - i - 1] - 48 == 0)
		{
			continue;
		}
		else
		{
			res = decPlusDec(res, twoPowDec(i));
		}
	}
	if (Q[0] - 48 != 0) //Ki?m tra âm duong d? thêm d?u '-'
	{
		res.insert(0, 1, '-');
	}
	int j = res.length();
	if (j == 0)
	{
		res += "0";
	}
	return res;
}

//Chia nguyên s? th?p phân cho 2
string decDivTwo(string& A)
{
	string res; //Chu?i k?t qu?
	string s = "0123456789"; //Tuong ?ng 0='0', ..., 9='9'
	int du = 0;	//Ph?n du
	int temp;
	if (A == "0" || A == "1") //Ki?m tra n?u A = 0 ho?c A = 1 thì k?t qu? phép chia s? b?ng 0
	{
		res = "0";
	}
	//Th?c hi?n phép chia nhu chia trên gi?y
	for (int i = 0; i < A.length(); i++)
	{
		temp = (A[i] - 48) + 10 * du;
		du = temp % 2;
		if (temp / 2 > 0 || i > 0)
		{
			res = res + s[temp / 2];
		}
	}
	return res;
}

//Chuy?n t? h? th?p phân sang nh? phân
string decToBin(string& Q)
{
	int dau = 0;	//Luu d?u c?a s?
	string tmp = Q;
	if (Q[0] == '-')	//Ki?m tra s? dó là âm hay duong
	{
		dau = 1;	//Luu d?u l?i
		tmp.erase(0, 1);	//Xóa d?u di d? nó tr? thành s? duong
	}
	string res;	//Chu?i k?t qu?
	string s = "01";
	while (tmp != "0")
	{
		//Chúng ta xét s? cu?i cùng c?a chu?i s? n?u l? thì du là 1 và ngu?c l?i là 0
		res = s[(tmp[tmp.length() - 1] - 48) % 2] + res;
		tmp = decDivTwo(tmp);	//Tìm thuong c?a phép chia
	}
	int n = res.length();
	res.insert(0, BIN_MAX - n, '0');	//N?u chu?i k?t qu? chua d? 128 bit thì ta thêm bit 0 vào cho d?
	if (dau == 1) //n?u s? ban d?u là âm thì ta chuy?n v? dang bù 2 c?a nó
	{
		res = Bu1(res);
		res = binCong1(res);
	}
	return res;
}

//Chuy?n t? th?p phân sang nh? phân ? d?ng 32 bit
string decToBin_KhongDau32Bit(unsigned int Q)
{

	unsigned int tmp = Q;
	string res;
	string s = "01";
	while (tmp != 0)
	{
		res = s[tmp % 2] + res;
		tmp = tmp / 2;
	}
	int n = res.length();
	res.insert(0, 32 - n, '0');
	return res;
}

//chuy?n t? th?p phân sang th?p l?c phân
string decToHex(string& Q)
{
	//Ý tu?ng chuy?n t? th?p phân sang nh? phân sau dó t? nh? phân sang th?p l?c phân
	string tmp = decToBin(Q);
	string res = binToHex(tmp);
	return res;
}

//Chuy?n t? th?p l?c phân sang nh? phân
string hexToBin(string& Q)
{
	//Ý tu?ng chuy?n t? s? th?p l?c phân sang nh? phân 4 bit sau dó ghép l?i
	string res;
	for (int i = 0; i < Q.length(); i++)
	{
		switch (Q[i])
		{
		case '0': res += "0000"; break;
		case '1': res += "0001"; break;
		case '2': res += "0010"; break;
		case '3': res += "0011"; break;
		case '4': res += "0100"; break;
		case '5': res += "0101"; break;
		case '6': res += "0110"; break;
		case '7': res += "0111"; break;
		case '8': res += "1000"; break;
		case '9': res += "1001"; break;
		case 'A': res += "1010"; break;
		case 'B': res += "1011"; break;
		case 'C': res += "1100"; break;
		case 'D': res += "1101"; break;
		case 'E': res += "1110"; break;
		case 'F': res += "1111"; break;
		}
	}
	int n = res.length();
	res.insert(0, BIN_MAX - n, '0');	//Thêm vào cho d? 128 bit
	return res;
}

//Khai báo class QInt, các thu?c tính và phuong th?c
class QInt
{
private:
	unsigned int arrayBits[MAX] = { 0 };	//S? d?ng m?ng int không d?u
public:
	QInt();
	QInt(int, string);
	~QInt();
	void ScanQInt(int);	//nh?p QInt theo h? base t? bàn phím
	void PrintQInt(int);	//Xu?t QInt theo h? yêu c?u ra màn hình
	string Print(int);	//Tr? ra chu?i s? theo h? yêu c?u

	QInt& operator+(const QInt&);	//C?ng hai s? QInt
	QInt& operator-(const QInt&);	//Tr? hai s? QInt
	QInt& operator-();	//Tìm s? d?i c?a QInt
	QInt& operator*(const QInt&);	//Tích hai s? QInt
	QInt& operator/(const QInt&);	//Thuong hai s? QInt

	bool operator==(const QInt&);	//So sánh b?ng
	bool operator<=(const QInt&);	//So sánh <=
	bool operator>=(const QInt&);	//So sánh >=
	bool operator<(const QInt&);	//So sánh <
	bool operator>(const QInt&);	//So sánh >
	QInt& operator=(const QInt&);	//Phép gán b?ng

	QInt& operator&(const QInt&);	//Phép AND
	QInt& operator|(const QInt&);	//Phép OR
	QInt& operator^(const QInt&);	//Phép XOR
	QInt& operator~();	//Phép NOT

	QInt& operator<<(const int);	//Phép d?ch trái k bit
	QInt& operator >> (const int);	//Phép d?ch ph?i k bit
	QInt& ROL(const int);	//Phép xoay trái k bit
	QInt& ROR(const int);	//Phép xoay ph?i k bit
};

//Kh?i t?o QInt
QInt::QInt()
{

}

//Kh?i t?o có tham s?
QInt::QInt(int base, string s) //Truy?n vào h? base và chu?i s? tuong ?ng
{
	int n = s.length();
	switch (base)
	{
	case 2:	//N?u là h? 2 thì ch? c?n thêm d? bit 0 cho d? 128 bit
		s.insert(0, BIN_MAX - n, '0');
		break;
	case 10: s = decToBin(s); break; //N?u là h? 10 thì chuy?n sang h? 2
	case 16: s = hexToBin(s); break;	//N?u là h? 16 thì chuy?n sang h? 2
	}
	//Tách m?i 32 bit luu vào arrayBits[i]
	for (int i = s.length() - 1; i >= 0; i--)
	{
		arrayBits[i / 32] = arrayBits[i / 32] | ((s[i] - 48)*(1 << ((BIN_MAX - i - 1) % 32)));
	}
}

//Hàm h?y
QInt::~QInt()
{

}

//Nh?p QInt t? bàn phím theo h? yêu c?u du?c truy?n vào
void QInt::ScanQInt(int x) //Truy?n vào h? x
{
	//Ph?n bên du?i tuong t? nhu hàm kh?i t?o có tham s?
	string tmp;
	cin >> tmp;
	int n = tmp.length();
	switch (x)
	{
	case 2:
		tmp.insert(0, BIN_MAX - n, '0');
		break;
	case 10: tmp = decToBin(tmp); break;
	case 16: tmp = hexToBin(tmp); break;
	}
	for (int i = tmp.length() - 1; i >= 0; i--)
	{
		arrayBits[i / 32] = arrayBits[i / 32] | ((tmp[i] - 48)*(1 << ((BIN_MAX - i - 1) % 32)));
	}
}

//Xu?t s? QInt ra màn hình theo h? yêu c?u du?c nh?p t? bàn phím
void QInt::PrintQInt(int x)
{
	string res;
	for (int i = 0; i < MAX; i++)
	{
		res = res + decToBin_KhongDau32Bit(arrayBits[i]);
	}
	switch (x)
	{
	case 2:
		while (res[0] == '0')
		{
			int n = res.length();
			if (n == 1)
			{
				break;
			}
			res.erase(0, 1);
		}
		break;
	case 10: res = binToDec(res); break;
	case 16: res = binToHex(res); break;
	}
	cout << res << endl;
}

string QInt::Print(int x)
{
	string res;
	for (int i = 0; i < MAX; i++)
	{
		res = res + decToBin_KhongDau32Bit(arrayBits[i]);
	}
	switch (x)
	{
	case 2:
		while (res[0] == '0')
		{
			int n = res.length();
			if (n == 1)
			{
				break;
			}
			res.erase(0, 1);
		}
		break;
	case 10: res = binToDec(res); break;
	case 16: res = binToHex(res); break;
	}
	return res;
}

//C?ng hai s? QInt
QInt & QInt::operator+(const QInt &B)
{
	//Ý tu?ng l?i d?ng v?n d? tràn bit d? th?c hi?n phép c?ng
	QInt *tmp = new QInt;
	int du = 0;	//Ban d?u kh?i t?o du = 0
	for (int i = MAX - 1; i >= 0; i--)
	{
		unsigned int a = this->arrayBits[i];
		unsigned int b = B.arrayBits[i];
		unsigned int c = a + b;
		tmp->arrayBits[i] = c + du;
		unsigned int min;
		if (a < b)
		{
			min = a;
		}
		else
		{
			min = b;
		}
		//Phát hi?n tràn bit, n?u tràn bit thì du = 1
		if (c < min)
		{
			du = 1;
		}
		else
		{
			du = 0;
		}
	}
	return *tmp;
}

//Tr? hai s? QInt
QInt & QInt::operator-(const QInt &B)
{
	//Ý tu?ng l?i d?ng v?n d? tràn bit d? th?c hi?n phép tr?
	QInt *tmp = new QInt;
	int du = 0; //Kh?i t?o du = 0
	for (int i = MAX - 1; i >= 0; i--)
	{
		unsigned int a = this->arrayBits[i];
		unsigned int b = B.arrayBits[i];
		unsigned int c = a - b - du;
		//Phát hi?n tràn bit, n?u tràn bit thù du = 1
		if (a < b)
		{
			du = 1;
		}
		else
		{
			du = 0;
		}
		tmp->arrayBits[i] = c;
	}
	return *tmp;
}

//Tìm s? d?i c?a QInt
QInt & QInt::operator-()
{
	QInt* res = new QInt;
	QInt numberOne;
	numberOne.arrayBits[3] = 1;
	*res = ~(*this) + numberOne;
	return *res;
}

//Tích 2 s? QInt
QInt & QInt::operator*(const QInt &Q)
{
	QInt* res = new QInt;
	QInt* tmp = new QInt;
	*tmp = *this;
	for (int i = 0; i < BIN_MAX; i++)
	{
		if ((Q.arrayBits[(BIN_MAX - i - 1) / 32] >> (i % 32)) & 1)
		{
			*res = *res + *tmp;
		}
		*tmp = (*tmp) << 1;
	}
	return *res;
}

//Thuong 2 s? QInt
QInt & QInt::operator/(const QInt &B)
{
	QInt* C = new QInt;
	QInt* tmp = new QInt;
	QInt* tmp1 = new QInt;
	QInt* tmp2 = new QInt;
	*tmp = B;
	int i = BIN_MAX;
	int dau = 0;
	if (this->arrayBits[0] >> 31)
	{
		dau++;
		*this = -(*this);
	}
	if (B.arrayBits[0] >> 31)
	{
		dau++;
		*tmp = -(*tmp);
	}
	while (i)
	{
		*tmp2 = (*this >> (i - 1)) - *tmp1;
		*C = *C << 1;
		if (*tmp2 >= *tmp)
		{
			C->arrayBits[3] = C->arrayBits[3] | 1;
			*tmp1 = *tmp1 + *tmp;
		}
		*tmp1 = *tmp1 << 1;
		i--;
	}
	if (dau % 2 == 0)
	{
		return *C;
	}
	return -(*C);
}

//Phép AND
QInt & QInt::operator&(const QInt &B)
{
	//Ý tu?ng ta AND l?n lu?t các ph?n t? arrayBits v?i nhau
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = arrayBits[0] & B.arrayBits[0];
	tmp->arrayBits[1] = arrayBits[1] & B.arrayBits[1];
	tmp->arrayBits[2] = arrayBits[2] & B.arrayBits[2];
	tmp->arrayBits[3] = arrayBits[3] & B.arrayBits[3];
	return *tmp;
}

//Phép OR
QInt & QInt::operator|(const QInt &B)
{
	//Ý tu?ng ta OR l?n lu?t các ph?n t? arrayBits v?i nhau
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = arrayBits[0] | B.arrayBits[0];
	tmp->arrayBits[1] = arrayBits[1] | B.arrayBits[1];
	tmp->arrayBits[2] = arrayBits[2] | B.arrayBits[2];
	tmp->arrayBits[3] = arrayBits[3] | B.arrayBits[3];
	return *tmp;
}

//Phép XOR
QInt & QInt::operator^(const QInt &B)
{
	//Ý tu?ng ta XOR l?n lu?t các ph?n t? arrayBits v?i nhau
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = arrayBits[0] ^ B.arrayBits[0];
	tmp->arrayBits[1] = arrayBits[1] ^ B.arrayBits[1];
	tmp->arrayBits[2] = arrayBits[2] ^ B.arrayBits[2];
	tmp->arrayBits[3] = arrayBits[3] ^ B.arrayBits[3];
	return *tmp;
}

//Phép NOT
QInt & QInt::operator~()
{
	//Ý tu?ng ta NOT l?n lu?t các ph?n t? arrayBits
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = ~arrayBits[0];
	tmp->arrayBits[1] = ~arrayBits[1];
	tmp->arrayBits[2] = ~arrayBits[2];
	tmp->arrayBits[3] = ~arrayBits[3];
	return *tmp;
}

//Phép d?ch trái k bit
QInt & QInt::operator<<(const int k)
{
	QInt* tmp = new QInt;
	*tmp = *this;
	for (int i = 0; i < k; i++)
	{
		tmp->arrayBits[0] = tmp->arrayBits[0] << 1;
		tmp->arrayBits[0] = tmp->arrayBits[0] | ((tmp->arrayBits[1] >> 31) & 1);
		tmp->arrayBits[1] = tmp->arrayBits[1] << 1;
		tmp->arrayBits[1] = tmp->arrayBits[1] | ((tmp->arrayBits[2] >> 31) & 1);
		tmp->arrayBits[2] = tmp->arrayBits[2] << 1;
		tmp->arrayBits[2] = tmp->arrayBits[2] | ((tmp->arrayBits[3] >> 31) & 1);
		tmp->arrayBits[3] = tmp->arrayBits[3] << 1;
	}
	return *tmp;
}

//Phép d?ch ph?i k bit
QInt & QInt::operator >> (const int k)
{
	QInt* tmp = new QInt;
	*tmp = *this;
	for (int i = 0; i < k; i++)
	{
		tmp->arrayBits[3] = (tmp->arrayBits[3]) >> 1;
		tmp->arrayBits[3] = tmp->arrayBits[3] | ((1 & tmp->arrayBits[2]) << 31);
		tmp->arrayBits[2] = tmp->arrayBits[2] >> 1;
		tmp->arrayBits[2] = tmp->arrayBits[2] | ((1 & tmp->arrayBits[1]) << 31);
		tmp->arrayBits[1] = tmp->arrayBits[1] >> 1;
		tmp->arrayBits[1] = tmp->arrayBits[1] | ((1 & tmp->arrayBits[0]) << 31);
		unsigned int c = tmp->arrayBits[0];
		c = c >> 31;
		c = c << 31;
		tmp->arrayBits[0] = tmp->arrayBits[0] >> 1;
		tmp->arrayBits[0] = tmp->arrayBits[0] | c;
	}
	return *tmp;
}

//Phép xoay trái k bit
QInt & QInt::ROL(const int k)
{
	QInt *res = new QInt;
	*res = *this;
	for (int i = 0; i < k; i++)
	{
		unsigned int tmp = (res->arrayBits[0] >> 31) & 1;;
		*res = *res << 1;
		res->arrayBits[3] = res->arrayBits[3] | tmp;
	}
	return *res;
}

//Phép xoay ph?i k bit
QInt & QInt::ROR(const int k)
{
	QInt *res = new QInt;
	*res = *this;
	for (int i = 0; i < k; i++)
	{
		unsigned int tmp = (res->arrayBits[3]) & 1;
		*res = *res >> 1;
		res->arrayBits[3] = res->arrayBits[3] | (tmp << 31);
	}
	return *res;
}

//So sánh b?ng
bool QInt::operator==(const QInt &B)
{
	for (int i = 0; i < MAX; i++)
	{
		if (arrayBits[i] != B.arrayBits[i])
			return false;
	}
	return true;
}

//So sánh <=
bool QInt::operator<=(const QInt &B)
{
	if ((*this < B) || (*this == B))
	{
		return true;
	}
	return false;
}

//So sánh >=
bool QInt::operator>=(const QInt &B)
{
	if ((*this > B) || (*this == B))
	{
		return true;
	}
	return false;
}

//So sánh <
bool QInt::operator<(const QInt &B)
{
	int a = arrayBits[0];
	int b = B.arrayBits[0];
	a = (a >> 31) & 1;
	b = (b >> 31) & 1;
	if (a > b)
	{
		return true;
	}
	else if (a < b)
	{
		return false;
	}
	for (int i = 0; i < MAX; i++)
	{
		if (arrayBits[i] < B.arrayBits[i])
		{
			return true;
		}
		else if (arrayBits[i] == B.arrayBits[i])
		{
			continue;
		}
		return false;
	}
}

//So sánh >
bool QInt::operator>(const QInt &B)
{
	int a = arrayBits[0];
	int b = B.arrayBits[0];
	a = (a >> 31) & 1;
	b = (b >> 31) & 1;
	if (a > b)
	{
		return false;
	}
	else if (a < b)
	{
		return true;
	}
	for (int i = 0; i < MAX; i++)
	{
		if (arrayBits[i] > B.arrayBits[i])
		{
			return true;
		}
		else if (arrayBits[i] == B.arrayBits[i])
		{
			continue;
		}
		return false;
	}
}

//Phép gán b?ng
QInt & QInt::operator=(const QInt &B)
{
	for (int i = 0; i < MAX; i++)
	{
		this->arrayBits[i] = B.arrayBits[i];
	}
	return *this;
}

//Hàm d?m s? kho?ng tr?ng c?a 1 chu?i
int demKhoangTrang(string s)
{
	int d = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == 32)
		{
			d = d + 1;
		}
	}
	return d;
}

class ChamDong
{
private:
public:
	virtual void Scan(string q);
	virtual void Print();
	ChamDong();
	~ChamDong();
};




class Qfloat :public ChamDong
{
private:
	char x[100000];
public:
	void Scan(string q);
	void Print();
	void PrintQfloat();
	void DecToBin();
	char getx(int n);
	void setarr(char u, char v[], char z[]);
	Qfloat();
	~Qfloat();
};
void ChamDong::Scan(string q)
{
}

void ChamDong::Print()
{
}

ChamDong::ChamDong()
{
}


ChamDong::~ChamDong()
{
}

class Bit : public ChamDong
{
private:
	bool bit[128] = { 0 };
public:
	void Scan(string q);
	void Print();
	void PrintBit();
	void BinToDec();
	bool getbit(int n);
	void set(int n, int x);
	Bit();
	~Bit();
};
// d?c vô m?ng bit
void Bit::Scan(string q)
{
	ChamDong::Scan(q);
	for (int i = 0; i < q.length(); i++)
	{
		bit[i] = q[i] - 48;
	}
	for (int i = q.length(); i < 128; i++)
	{
		bit[i] = 0;
	}
}
//int bit
void Bit::Print()
{
	ChamDong::Print();
	BinToDec();
}
// Ki?m tra m?ng
bool KT(bool bit[], int start, int end, int gt)
{
	for (int i = start; i <= end; i++)
	{
		if (bit[i] != gt)
		{
			return false;
		}
	}
	return true;
}
//in bit
void Bit::PrintBit()
{
	cout << bit[0];
	for (int i = 1; i <= 15; i++)
	{
		cout << bit[i];
	}
	for (int i = 16; i < 128; i++)
	{
		cout << bit[i];
	}
	cout << endl;
}
//l?y giá tr? bit
bool Bit::getbit(int n)
{
	return bit[n];
}
//thay d?i giá tr? m?ng bin
void Bit::set(int n, int x)
{
	bit[n] = x;
}
//tính 2^n
int Pow(int n)
{
	int luythua = 1;
	for (int i = 0; i < n; i++)
	{
		luythua *= 2;
	}
	return luythua;
}
// s?a m?ng thêm 1 vào d?u m?ng
void Sua(char v[])
{
	int n;
	for (int i = 0;; i++)
	{
		if (v[i] == '\0')
		{
			n = i;
			break;
		}
	}
	for (int i = n; i > 0; i--)
	{
		v[i] = v[i - 1];
	}
	v[n + 1] = '\0';
	v[0] = '1';
}
//nhân 2 m?ng
void mul2(char v[], int c)
{
	v[0] += (v[0] - 48);
	if (v[0] > 57)
	{
		v[0] -= 10;
		Sua(v);
		for (int i = 2; i < 20000; i++)
		{
			if (v[i] != '\0')
			{
				v[i] += (v[i] - 48);
				if (v[i] > 57)
				{
					v[i] -= 10;
					v[i - 1] += 1;
				}
			}
			else
			{
				v[i - 1] += c;
				break;
			}
		}
	}
	else {
		for (int i = 1; i < 20000; i++)
		{
			if (v[i] != '\0')
			{
				v[i] += (v[i] - 48);
				if (v[i] > 57)
				{
					v[i] -= 10;
					v[i - 1] += 1;
				}
			}
			else
			{
				v[i - 1] += c;
				break;
			}
		}
	}
}
//chia 2 m?ng
void div2(char v[], int c)
{
	for (int i = 0; i < 200000; i++)
	{
		if (v[i] != '\0')
		{
			int a = (v[i] - 48) % 2;
			v[i] -= (v[i] - 48) / 2 + a;
			if (a == 1)
			{
				if (v[i + 1] != '\0')
					v[i + 1] += 10;
				else
				{
					v[i + 1] = '5';
					v[i + 2] = '\0';
					break;
				}
			}
		}
	}
	v[0] += c * 5;
}


void Bit::BinToDec()
{
	if (KT(bit, 1, 15, 0) || KT(bit, 1, 15, 1))
	{
		if (KT(bit, 1, 15, 0) && KT(bit, 16, 127, 0) && bit[0] == 1)
			cout << "-0" << endl;
		if (KT(bit, 1, 15, 0) && KT(bit, 16, 127, 0) && bit[0] == 0)
			cout << "+0" << endl;
		if (KT(bit, 1, 15, 0) && !KT(bit, 16, 127, 0))
			cout << "denormalized" << endl;
		if (KT(bit, 1, 15, 1) && KT(bit, 16, 127, 0))
			cout << "infinity" << endl;
		if (KT(bit, 1, 15, 1) && !KT(bit, 16, 127, 0))
			cout << "NAN" << endl;
	}
	else {
		Qfloat x;
		char u, v[20000], z[20000];

		if (bit[0] == 0) {
			u = '+';
		}
		if (bit[0] == 1) {
			u = '-';
		}
		int t = 0;
		for (int i = 1; i <= 15; i++)
		{
			t += bit[i] * Pow(15 - i);
		}
		t -= 16383;
		v[0] = '0';
		v[1] = '\0';
		z[0] = '0';
		z[1] = '\0';
		int k;
		for (int i = 127;; i--)
		{
			if (bit[i] == 1)
			{
				k = i;
				break;
			}
			if (i == 16)
			{
				k = 15;
				break;
			}
		}
		if (t >= 0) {
			v[0] = '1';
			v[1] = '\0';
			for (int i = 16; i < t + 16; i++)
			{
				int c = 0;
				if (i<127)
				{
					c = bit[i];
				}
				mul2(v, c);
			}
			if (k >= t + 16)
			{
				z[0] = '5';
				z[1] = '\0';
				for (int i = k - 1; i >= t + 16; i--)
				{
					int c = 0;
					if (bit[i] == 1)
					{
						c = 1;
					}
					div2(z, c);
				}
			}
		}
		else {
			z[0] = '5';
			z[1] = '\0';
			for (int i = k - 1; i >= 16; i--)
			{
				int c = 0;
				if (bit[i] == 1)
				{
					c = 1;
				}
				div2(z, c);
			}
			div2(z, 1);
			for (int i = 0; i < abs(t) - 1; i++)
			{
				div2(z, 0);
			}
		}
		x.setarr(u, v, z);
		x.PrintQfloat();
	}
}

Bit::Bit()
{
}
Bit::~Bit()
{
}
//d?c dec
void Qfloat::Scan(string q)
{
	ChamDong::Scan(q);
	for (int i = 0; i < q.length(); i++)
	{
		x[i] = q[i];
	}
	x[q.length()] = '\0';
}
//chuy?n s? ch?m d?ng sang bin và in
void Qfloat::Print()
{
	ChamDong::Print();
	DecToBin();
}
//in m?ng
void Qfloat::PrintQfloat()
{
	if (x[0] != '+')
		cout << x[0];
	for (int i = 1; i < 100000; i++)
	{
		if (x[i] == '\0')
			break;
		cout << x[i];
	}
	cout << endl;
}
// l?y giá tr? m?ng
char Qfloat::getx(int n)
{
	return x[n];
}
// n?i m?ng
void Qfloat::setarr(char u, char v[], char z[])
{
	x[0] = u;
	int n;
	for (int i = 1; i < 100000; i++)
	{
		x[i] = v[i - 1];
		if (v[i] == '\0') {
			n = i + 1;
			break;
		}

	}
	x[n] = '.';
	for (int i = n + 1; i < 100000; i++)
	{
		x[i] = z[i - n - 1];
		if (z[i - n - 1] == '\0')
			break;
	}
}
// Tách s? ch?m d?ng theo t?ng ph?n d?u ph?n nguyên và ph?n s? ph?y
void Tach(char x[], int& u, char v[], char z[])
{
	if (x[0] == '-' || x[0] == '+')
	{
		if (x[0] == '-')
			u = 1;
		else
			u = 0;
		int n = 100000;
		for (int i = 1; i<100000; i++)
		{
			if (x[i] != '.' && x[i] != '\0')
			{
				v[i - 1] = x[i];
			}
			else
			{
				v[i - 1] = '\0';
				if (x[i] == '\0')
				{
					z[0] = '0';
					z[1] = '\0';
					return;
				}
				else
				{
					n = i + 1;
					break;
				}
			}
		}
		for (int i = n; i<100000; i++)
		{
			if (x[i] != '\0')
			{
				z[i - n] = x[i];
			}
			else {
				z[i - n] = '\0';
				break;
			}
		}
	}
	else
	{
		u = 0;
		int n;
		for (int i = 0;; i++)
		{
			if (x[i] != '.' && x[i] != '\0')
			{
				v[i] = x[i];
			}
			else
			{
				v[i] = '\0';
				if (x[i] == '\0')
				{
					z[0] = '0';
					z[1] = '\0';
					return;
				}
				else
				{
					n = i + 1;
					break;
				}
			}
		}
		for (int i = n; i<100000; i++)
		{
			if (x[i] != '\0')
			{
				z[i - n] = x[i];
			}
			else {
				z[i - n] = '\0';
				break;
			}
		}
	}
}
// xóa d?u m?ng
void delFirst(char v[])
{
	for (int i = 0;; i++)
	{
		v[i] = v[i + 1];
		if (v[i + 1] == '\0')
			break;
	}
}
// xóa cu?i m?ng
void delLast(char v[])
{
	if (v[0] != '\0') {
		for (int i = 1;; i++)
		{
			if (v[i] == '\0')
			{
				v[i - 1] = '\0';
				break;
			}
		}
	}
}
//chia 2 m?ng tr? v? s? du
int div(char v[])
{
	int a;
	for (int i = 0; i < 100000; i++)
	{
		if (v[i] != '\0')
		{
			a = (v[i] - 48) % 2;
			v[i] -= (v[i] - 48) / 2 + a;
			if (a == 1)
			{
				if (v[i + 1] != '\0')
					v[i + 1] += 10;
				else
				{
					break;
				}
			}
		}
		else {
			break;
		}
	}
	while (v[0] == '0')
		delFirst(v);
	return a;
}
// nhân 2 m?ng
int mul(char v[])
{
	int a = 0;
	v[0] += (v[0] - 48);
	if (v[0] > 57)
	{
		a = 1;
		v[0] -= 10;
	}
	for (int i = 1; i < 100000; i++)
	{
		if (v[i] != '\0')
		{
			v[i] += (v[i] - 48);
			if (v[i] > 57)
			{
				v[i] -= 10;
				v[i - 1] += 1;
			}
		}
		else
		{
			if (v[i - 1] == '0')
				delLast(v);
			break;
		}
	}
	return a;
}
//thêm vào cu?i m?ng
void addFirst(char v[], int a)
{
	int n;
	for (int i = 0;; i++)
	{
		if (v[i] == '\0')
		{
			n = i;
			break;
		}
	}
	for (int i = n; i >= 1; i--)
	{
		v[i] = v[i - 1];
	}
	v[n + 1] = '\0';
	v[0] = a + 48;
}
// chuy?n ph?n nguyên v? bin
void ToBin1(char v[])
{
	char u[100000];
	u[0] = '\0';
	int a;
	int t = 0;
	while (v[0] != '\0')
	{
		a = div(v);
		t++;
		addFirst(u, a);
	}
	for (int i = 0; i < 100000; i++)
	{
		v[i] = u[i];
		if (u[i] == '\0')
			break;
	}
}
// thêm vào cu?i m?ng
void addLast(char v[], int a)
{
	for (int i = 0;; i++)
	{
		if (v[i] == '\0')
		{
			v[i] = 48 + a;
			v[i + 1] = '\0';
			break;
		}
	}
}
// chuy?n t? s? ph?y sang s? bin
void ToBin2(char v[])
{
	char u[100000];
	u[0] = '\0';
	int a;
	int t = 0;
	while (v[0] != '\0' && t != 10000)
	{
		a = mul(v);
		t++;
		addLast(u, a);
	}
	for (int i = 0; i < 100000; i++)
	{
		v[i] = u[i];
		if (u[i] == '\0')
			break;
	}
}

void Qfloat::DecToBin()
{
	Bit a;
	int u = 1;
	char v[100000];
	char z[100000];
	Tach(x, u, v, z);
	if (v[0] == '0' && ((z[0] == '0' && z[1] == '\0') || z[0] == '\0'))
	{
		a.set(0, u);
		for (int i = 1; i < 128; i++)
		{
			a.set(i, 0);
		}
	}
	else
	{
		ToBin1(v);
		ToBin2(z);
		int n = 16383;
		int p[15] = { 0 };
		if (v[0] != '0')
		{
			for (int i = 0; ; i++)
			{
				if (v[i] == '\0')
				{
					n = n + i - 1;
					break;
				}
			}
			int i = 14;
			while (n > 0)
			{
				p[i] = n % 2;
				n /= 2;
				i--;
			}
			int b = 0;
			int c = 0;
			a.set(0, u);
			for (int i = 1; i < 16; i++)
			{
				a.set(i, p[i - 1]);
			}
			for (int i = 16; i < 128; i++)
			{
				if (v[i - 15] != '\0')
				{
					a.set(i, v[i - 15] - 48);
				}
				else
				{
					b = i;
					break;
				}
			}
			for (int i = b; i < 128; i++)
			{
				if (z[i - b] == '\0')
				{
					c = i;
					break;
				}
				else
				{
					a.set(i, z[i - b] - 48);
				}
			}
			if (b == 127)
			{
				if (v[112] == '1')
				{
					while (a.getbit(b) != 0)
					{
						a.set(b, 0);
						b--;
					}
					a.set(b, 1);
				}
			}
			if (c == 127)
			{
				if (z[c - b] == '1')
				{
					while (a.getbit(c) != 0)
					{
						a.set(c, 0);
						c--;
					}
					a.set(c, 1);
				}
			}

		}
		else
		{
			for (int i = 0;; i++)
			{
				if (z[i] == '1')
				{
					n = n - i - 1;
					break;
				}
				if (z[i] == '\0')
				{
					break;
				}
			}
			int d = 16383 - n;
			int i = 14;
			while (n > 0)
			{
				p[i] = n % 2;
				n /= 2;
				i--;
			}
			int b = 127;
			a.set(0, u);
			for (int i = 1; i < 16; i++)
			{
				a.set(i, p[i - 1]);
			}
			for (int i = 16; i < 128; i++)
			{
				if (z[i + d - 16] == '\0')
				{
					a.set(i, 0);
					break;
				}
				else
				{
					a.set(i, z[i + d - 16] - 48);
				}
			}
			if (z[128 + d - 16] == '1')
			{
				while (a.getbit(b) != 0)
				{
					a.set(b, 0);
					b--;
				}
				a.set(b, 1);
			}
		}
	}
	a.PrintBit();
}

Qfloat::Qfloat()
{
}


Qfloat::~Qfloat()
{
}

int main(int mun, char**arg)
{
	if (strcmp(arg[3], "QInt") == 0)
	{
		int dem = 0;
		vector<string>kq; //Ch?a chu?i k?t qu? s? xu?t ra file output
		string tmp;
		while (!cin.eof())	//Ð?c d?n cu?i file
		{
			freopen(arg[1], "rt", stdin);	//M? file d? d?c
			cin.seekg(dem, ios::cur);
			getline(cin, tmp);	//Ð?c vào chu?i tmp t?ng dòng d? xét xem dòng dó dang th?c hi?n phép tính gì
			dem += tmp.length() + 2;
			int n = tmp.length();
			cin.seekg(-(n + 2), ios::cur);
			int t = demKhoangTrang(tmp);	//Ð?m s? kho?ng tr?ng c?a tmp d? xét tru?ng h?p
			if (t == 2)	//t = 2 chuy?n t? h? A sang h? B và phép NOT (~)
			{
				int base1, base2;
				string s1, s2;
				cin >> base1 >> s1;
				if (s1 == "~")
				{
					cin >> s2;
					QInt A(base1, s2);
					A = ~A;
					kq.push_back(A.Print(base1));
				}
				else {
					int j = s1.length();
					cin.seekg(-j, ios::cur);
					cin >> base2 >> s2;
					QInt A(base1, s2);
					kq.push_back(A.Print(base2));
				}
			}
			//Ngu?c l?i  t= 3 s? các phép toán: +, -, *, / , &, |, , ^, >, >=, <, <=, ==
			//Ð?c bi?t v?i các ki?u so sánh thì d? li?u tr? v? là YES n?u so sánh dúng
			// là No n?u só sánh sai
			else
			{
				int base, k;
				string st1, st2, st3;
				cin >> base >> st1 >> st2;
				QInt A(base, st1);
				QInt res;
				if (st2 == "+")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A + B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "-")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A - B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "*")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A * B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "/")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A / B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "&")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A & B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "|")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A | B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "^")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A ^ B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "<<")
				{
					cin >> k;
					res = A << k;
					kq.push_back(res.Print(base));
				}
				else if (st2 == ">>")
				{
					cin >> k;
					res = A >> k;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "ROL")
				{
					cin >> k;
					res = A.ROL(k);
					kq.push_back(res.Print(base));
				}
				else if (st2 == "ROR")
				{
					cin >> k;
					res = A.ROR(k);
					kq.push_back(res.Print(base));
				}
				else if (st2 == ">")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A > B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == "<")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A < B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == ">=")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A >= B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == "<=")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A <= B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == "==")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A == B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
			}
		}
		freopen(arg[2], "wt", stdout);
		for (int i = 0; i < kq.size(); i++)
		{
			cout << kq[i] << endl;
		}
	}
	else
	{
		vector <ChamDong*> a;
		FILE* ps;
		ps = freopen(arg[1], "rt", stdin);
		ChamDong* temp;
		while (!cin.eof())
		{
			int b, c;
			cin >> b;
			cin >> c;
			string q;
			cin >> q;
			if (b == 2 && c == 10)
			{
				temp = new Bit;
				temp->Scan(q);
				a.push_back(temp);
			}
			else
			{
				temp = new Qfloat;
				temp->Scan(q);
				a.push_back(temp);
			}
		}
		ps = freopen(arg[2], "wt", stdout);
		for (int i = 0; i < a.size(); i++)
		{
			a[i]->Print();
		}
		for (ChamDong* &temp : a)
		{
			delete temp;
		}
	}
	return 0;
}

