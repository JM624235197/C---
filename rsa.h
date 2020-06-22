#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>//����������Ĺ���
#include<boost/multiprecision/miller_rabin.hpp>//���Լ���ͷ�ļ�
#define NUMBER 256

//typedef long DataType;

//�������ͱ�ɴ���
typedef boost::multiprecision::int1024_t DataType;//���ɴ����̶�λ

namespace brdm = boost::random;//brdm�ͱ�ʾboost::random�������ռ�

struct Key
{
	DataType _ekey;//������Կ(e,n)
	DataType _dkey;//������Կ(d,n)
	DataType _nkey;//��������n
};
/*
1����������
2����n
3����գ�n��
4����e��1<e<��(n)�ͦ�(n)���ɻ��ʣ����ѡ��
5����d��e * d% ��(n) =1;
6����Կ(e��n)��˽Կ(d��n)
*/
class Rsa
{
private:
	Key _key;
public:

	Rsa();//�޲ι��캯��
	//д���������Ľӿں���

	void Ecrept(const char*filename, const char *fileout);//�����ļ�������Ϊ�����ļ���������ļ���
	void Dcrept(const char*filename, const char *fileout);//�����ļ�

	DataType GetPrime();//����һ������
	Key GetallKey();
	DataType Ecrept(DataType data,DataType ekey,DataType nkey);//���ܺ���
	DataType Dcrept(DataType data, DataType dkey, DataType nkey);//���ܺ���
	bool IsPrime(DataType data);//�ж�һ�����Ƿ�Ϊ����
	bool IsPrimeBignum(DataType data);//�ж�һ�������Ƿ�Ϊ����
	DataType GetNkey(DataType p1,DataType p2);//��ȡ�����Ĳ���,����Ϊ��������
	DataType GetOrla(DataType p1, DataType p2);//ŷ������
	DataType GetEkey(DataType orla);//������Կ������Ϊŷ����������(n);
	DataType GetDkey(DataType ekey,DataType orla);//������Կ������Ϊ���ܵ���Կ�͹�������
	DataType GetGcd(DataType data1, DataType data2);//�ж������������Լ���Ƿ�Ϊ1
	void  Getkeys();
	DataType Exgcd(DataType a, DataType b, DataType &x, DataType &y);//��ģ��Ԫ�أ���������Կ
};