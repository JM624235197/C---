#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>//产生随机数的工具
#include<boost/multiprecision/miller_rabin.hpp>//素性检测的头文件
#define NUMBER 256

//typedef long DataType;

//数据类型变成大数
typedef boost::multiprecision::int1024_t DataType;//给成大数固定位

namespace brdm = boost::random;//brdm就表示boost::random的命名空间

struct Key
{
	DataType _ekey;//加密秘钥(e,n)
	DataType _dkey;//解密秘钥(d,n)
	DataType _nkey;//公共部分n
};
/*
1、产生素数
2、求n
3、求φ（n）
4、求e：1<e<φ(n)和φ(n)构成互质，随机选择
5、求d：e * d% φ(n) =1;
6、公钥(e，n)、私钥(d，n)
*/
class Rsa
{
private:
	Key _key;
public:

	Rsa();//无参构造函数
	//写两个公共的接口函数

	void Ecrept(const char*filename, const char *fileout);//加密文件，参数为输入文件流和输出文件流
	void Dcrept(const char*filename, const char *fileout);//解密文件

	DataType GetPrime();//产生一个素数
	Key GetallKey();
	DataType Ecrept(DataType data,DataType ekey,DataType nkey);//加密函数
	DataType Dcrept(DataType data, DataType dkey, DataType nkey);//解密函数
	bool IsPrime(DataType data);//判断一个数是否为素数
	bool IsPrimeBignum(DataType data);//判断一个大数是否为素数
	DataType GetNkey(DataType p1,DataType p2);//获取公共的部分,参数为两个素数
	DataType GetOrla(DataType p1, DataType p2);//欧拉函数
	DataType GetEkey(DataType orla);//加密秘钥，参数为欧拉函数即φ(n);
	DataType GetDkey(DataType ekey,DataType orla);//解密秘钥，参数为加密的秘钥和公共部分
	DataType GetGcd(DataType data1, DataType data2);//判断两个数的最大公约数是否为1
	void  Getkeys();
	DataType Exgcd(DataType a, DataType b, DataType &x, DataType &y);//求模反元素，即加密秘钥
};