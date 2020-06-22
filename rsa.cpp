#include<time.h>
#include<iostream>
#include<fstream>
//#include<ostream>
#include<math.h>
#include"rsa.h"

Rsa::Rsa()//无参构造函数初始化
{
	Getkeys();
}

void Rsa::Ecrept(const char*filename, const char *fileout)//加密文件
{
	std::ifstream fin(filename,std::ifstream::binary);//输入文件流对象,按二进制方式打开
	std::ofstream fout(fileout,std::ifstream::binary);//输出文件流对象
	if (!fin.is_open())//判断输入文件是否能打开
	{
		perror("input file open failed!");
		return;
	}
	char *buffer = new char[NUMBER];//给定buffer按照字节处理
	DataType *bufferOut = new DataType[NUMBER];//按照加密后的数据类型输出
	while (!fin.eof())//文件中有内容进行处理
	{
		fin.read(buffer, NUMBER);//将内容读到缓冲区中，每次默认读256个字节
		int cnum=fin.gcount();//最近一次读取到的加密的个数
		for (int i = 0; i < cnum; i++)//对读取到的加密的按照字节的形式依次进行加密
		{
			bufferOut[i]=Ecrept((DataType)buffer[i], _key._ekey, _key._nkey);
		}
		/*
		文件操作：
			字节流读写：getline、>>、<<
			字节流读写：read、write
			*/
		fout.write((char*)bufferOut, cnum* sizeof(DataType));
	}

	delete[] buffer;//释放空间
	delete[] bufferOut;

	fin.close();//调用close将文件句柄关掉，可要可不要
	fout.close();

}
void Rsa::Dcrept(const char*filename, const char *fileout)//解密文件
{
	std::ifstream fin(filename, std::ifstream::binary);//输入文件流对象,按二进制方式打开
	std::ofstream fout(fileout, std::ifstream::binary);//输出文件流对象
	if (!fin.is_open())
	{
		perror("file open failed!");
		return;
	}
	DataType *buffer = new DataType[NUMBER];

	char *bufferOut = new char[NUMBER];
	while (!fin.eof())
	{
		fin.read((char*)buffer, NUMBER*sizeof(DataType));//读文件，读字节数
		int num = fin.gcount();//可能读不到那个大的字节，num记录当前读到的字节数
		num /= sizeof(DataType);//?
		for (int i = 0; i < num; i++)
		{
			//大数是char类型，故而需要类型转换
			bufferOut[i] = (char)Dcrept(buffer[i], _key._dkey, _key._nkey);
		}
		fout.write(bufferOut, num);
	}
	delete[] buffer;//释放
	delete[] bufferOut;

	fin.close();//调用close将文件句柄关掉，可要可不要
	fout.close();
}

void Rsa::Getkeys()
{
	DataType p1 = GetPrime();
	DataType p2 = GetPrime();
	while (p1 == p2)//判断你两数是否相同
	{
		p2 = GetPrime();//相同的话就重新获取
	}

	std::cout << "p1：" << p1 << std::endl; 
	std::cout << "p2：" << p2 << std::endl;

	DataType orla = GetOrla(p1,p2);
	std::cout << "orla：" << orla << std::endl;
	std::cout << "oqla finish" << std::endl;

	_key._nkey = GetNkey(p1,p2);//获取公共秘钥
	std::cout << "nkey：" << _key._nkey << std::endl;
	std::cout << "pkey finish" << std::endl;

	_key._ekey = GetEkey(orla);//获取加密秘钥
	std::cout << "ekey：" << _key._ekey << std::endl;
	std::cout << "ekey finish" << std::endl;

	_key._dkey = GetDkey(_key._ekey, orla);//获取解密秘钥
	std::cout << "dkey：" << _key._dkey << std::endl;
	std::cout << "dkey finish" << std::endl;

}
Key Rsa::GetallKey()
{
	return _key;
}
DataType Rsa::Ecrept(DataType data, DataType ekey, DataType nkey)//加密函数
{
	
	//pow运算溢出导致结果不对，此时需要采取快速幂取模运算
	//return (DataType)pow(data, ekey) % nkey;
	//i：0-------最后一位
	DataType Ai = data;
	DataType msge = 1;
	//data^ekey%nkey
	while (ekey)
	{
		if (ekey & 1)//拿到第0位的值
		{
			msge = (msge*Ai) % nkey;
		}
			ekey >>= 1;//右移一位相当有/2
			Ai = (Ai*Ai) % nkey;
	}
	return msge;
}

DataType Rsa::Dcrept(DataType data, DataType dkey, DataType nkey)//解密函数
{
	return Ecrept(data, dkey, nkey);
}

DataType Rsa::GetPrime()//产生一个素数
{
	std::cout << "Getprime()" << std::endl;
	//srand(time(NULL)); //这个函数最大返回的是一个整型数据，故而在大数中不能使用
	brdm::mt19937 a(time(nullptr));//随机数的发生器
	boost::random::uniform_int_distribution<DataType>dist(0, DataType(1) << 256);//指定分部，范围
	DataType prime;
	while (true)
	{
		prime = dist(a);
		//std::cout << "Bignum Random："<<prime << std::endl;
		if (IsPrimeBignum(prime))
		{
			break;
		}
	}
	std::cout << "Getprime() finish!" << std::endl;
	return prime;
}

bool Rsa::IsPrime(DataType data)//判断一个数是否为素数
{
	std::cout << "Isprime" << std::endl;
	if (data <= 0)
		return false;
	for (int i = 2; i <= sqrt(data); i++)
	{
		if (data%i == 0)
			return false;
	}
	std::cout << "Isprime() finish!" << std::endl;
	return true;
}

//判断大数是否为素数需要判断两次
//一次判断的是data是不是素数
//然后再判断的是(data - 1) / 2是不是素数
bool Rsa::IsPrimeBignum(DataType data)//判断一个大数是否为素数
{
	brdm::mt19937 a(time(nullptr));
	if (miller_rabin_test(data, 25, a))
	{
		if (miller_rabin_test((data - 1) / 2, 25, a))
		{
			return true;
		}
	}
	return false;
}

//求n=pq
DataType Rsa::GetNkey(DataType p1, DataType p2)//获取公共的部分,参数为两个素数
{
	return p1*p2;
}

//求φ(n)=(p-1)*(q-1)
DataType Rsa::GetOrla(DataType p1, DataType p2)//欧拉函数
{
	return (p1 - 1)*(p2 - 1);
}

//求e： 随机选择一个整数e，条件是1< e < φ(n)，且e与φ(n) 互质。
DataType Rsa::GetEkey(DataType orla)//加密秘钥，参数为欧拉函数即φ(n);
{
	//srand(time(NULL));
	brdm::mt19937 a(time(nullptr));//随机数的发生器
	boost::random::uniform_int_distribution<DataType>dist(2, orla);//指定分部，ekey范围是2<e<φ(n)
	DataType e;
	while (true)
	{
		e = dist(a);
		if (e > 1 && GetGcd(e, orla) == 1)//e>1,并且e与φ(n) 互质即最大公约是位1
		{
			return e;
		}
	}
}

//求d：e*d%φ(n)=1
DataType Rsa::GetDkey(DataType ekey, DataType orla)//解密秘钥，参数为加密的秘钥和公共部分
{
	DataType x = 0, y = 0;
	Exgcd(ekey, orla, x, y);
	//变换，让解密秘钥是一个比较小的正值
	return (x%orla + orla) % orla;

	/*//该算法时间复杂度高
	DataType d=orla/ekey;
	while (true)
	{
		if ((d*ekey) % orla == 1)
			return d;
		d++;
	}*/
}

//辗转相除法

DataType Rsa::GetGcd(DataType data1, DataType data2)//判断两个数最大公约数是否为1
{
	DataType tmp;
	while (tmp = (data1%data2))
	{
		data1 = data2;
		data2 = tmp;
	}
	return data2;
}

//求模反元素，即加密秘钥
DataType Rsa::Exgcd(DataType a, DataType b, DataType &x, DataType &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd= Exgcd(b, a%b, x, y);//最大公约数
	DataType x1 = x,y1=y;
	x = y1;
	y = x1 - a / b*y1;
	return gcd;
}