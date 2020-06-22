#include"rsa.h"
#include"bignum.h"
#include<fstream>
#include<iostream>
#include<boost/multiprecision/cpp_int.hpp>//����������
#include<boost/multiprecision/random.hpp>
//using namespace std;
using std::cout;
using std::cin;
using std::endl;

void test()
{
	Rsa rsa;
	rsa.Getkeys();
	Key key = rsa.GetallKey();

	DataType original = 2;//ԭʼ����
	DataType decout = rsa.Ecrept(original, key._ekey, key._nkey);
	cout << "original��" << original << endl;
	cout << "ecrept��" << decout << endl;
	cout << "decrpet��" << rsa.Dcrept(decout, key._dkey, key._nkey) << endl;//����

}

void testFile()//���������ӿں����Ĵ���
{
	std::ifstream fin("test.txt");
	//�ı���ʽ�򿪣����տո���߻��ж�ȡ����
	char c;
	int a;
	double d;
	fin >> c;
	fin >> a;
	fin >> d;
	cout << "a��" << a << "c��" << c << "d��" << d;
}
void testRSA()
{
	Rsa rsa;
	Key key = rsa.GetallKey();
	cout << "(e,n)��" << key._ekey <<','<< key._nkey << endl;
	cout << "(d,n)��" << key._dkey << ',' << key._nkey<<endl;

	rsa.Ecrept("test.txt", "test.Ecrpet.txt");
	rsa.Dcrept("test.ecrpet.txt", "test.decrept.txt");
}

void testBignumadd()
{
	cout << "---------add--------" << endl;
	Bignum bi;
	int a = 198765342;
	int b = 93476581;

	cout << a + b << endl;
	//cout << bi.add("198765342", "93476581") << endl;

	Bignum aa = "198765342";
	Bignum bb = "93476581";

	cout << "aa:" << aa << endl;
	cout << "bb:" << bb << endl;

	cout << aa + bb << endl;

}
void testBignumsub()
{
	cout << "---------sub--------" << endl;
	Bignum bi;
	int a = 198765342;
	int b = 93476581;

	cout << a - b << endl;
	//cout << bi.sub("198765342", "93476581") << endl;

	Bignum aa = "198765342";
	Bignum bb = "93476581";

	cout << "aa:" << aa << endl;
	cout << "bb:" << bb << endl;

	cout << aa - bb << endl;

	/*int  c = 1001;
	int d = 999;

	cout << c - d << endl;
	cout << bi.sub("1001", "999") << endl;*/
}

void testBignummul()
{
	cout << "---------mul--------" << endl;
	Bignum bi;
	int a = 9834;
	int b = 99235;

	cout << a * b << endl;
	//cout << bi.mul("9834", "99235") << endl;

	Bignum aa = "9834";
	Bignum bb = "99235";

	cout << "aa:" << aa << endl;
	cout << "bb:" << bb << endl;

	cout << aa*bb << endl;
}

void testBignumdev()
{
	cout << "---------dev--------" << endl;
	Bignum bi;
	int a = 99235;
	int b = 9834;

	cout << a / b << endl;
	cout << a % b << endl;

	/*cout << bi.dev("99235", "9834").first<< endl;
	cout << bi.dev("99235", "9834").second << endl;*/

	Bignum aa = "99235";
	Bignum bb = "9834";

	cout << "aa:" << aa << endl;
	cout << "bb:" << bb << endl;

	cout << aa / bb << endl;

	cout << "aa:" << aa << endl;
	cout << "bb:" << bb << endl;

	cout << aa % bb << endl;
}

void testRootBignum()
{
	boost::multiprecision::cpp_int ci;
	ci = 1024;
	//���42��,ci����̫�� 
	//ci = "1579656432344879562545665887956225156263";
	cout <<ci << endl;

	std::string num = "1579656432344879562545665887956225156263";
	boost::multiprecision::cpp_int di(num);
	cout << di << endl;
	cout << di + 10 << endl;
}
void testBoostRandom()
{
	//���������������
	boost::random::mt19937 a(time(NULL));//����
	boost::random::uniform_int_distribution<DataType>dist(0, DataType(1) << 1023);//��������������1023
	for (int i = 0; i < 100; i++)
	{
		DataType num = dist(a);
		cout << num << endl;
	}
}

int main()
{
	//test();
	testRSA();
	//testBignumadd();
	//testBignumsub();
	//testBignummul();
	//testBignumdev();
	//testRootBignum();
	//testBoostRandom();
	system("pause");

	return 0;
}