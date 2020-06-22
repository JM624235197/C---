#include<time.h>
#include<iostream>
#include<fstream>
//#include<ostream>
#include<math.h>
#include"rsa.h"

Rsa::Rsa()//�޲ι��캯����ʼ��
{
	Getkeys();
}

void Rsa::Ecrept(const char*filename, const char *fileout)//�����ļ�
{
	std::ifstream fin(filename,std::ifstream::binary);//�����ļ�������,�������Ʒ�ʽ��
	std::ofstream fout(fileout,std::ifstream::binary);//����ļ�������
	if (!fin.is_open())//�ж������ļ��Ƿ��ܴ�
	{
		perror("input file open failed!");
		return;
	}
	char *buffer = new char[NUMBER];//����buffer�����ֽڴ���
	DataType *bufferOut = new DataType[NUMBER];//���ռ��ܺ�������������
	while (!fin.eof())//�ļ��������ݽ��д���
	{
		fin.read(buffer, NUMBER);//�����ݶ����������У�ÿ��Ĭ�϶�256���ֽ�
		int cnum=fin.gcount();//���һ�ζ�ȡ���ļ��ܵĸ���
		for (int i = 0; i < cnum; i++)//�Զ�ȡ���ļ��ܵİ����ֽڵ���ʽ���ν��м���
		{
			bufferOut[i]=Ecrept((DataType)buffer[i], _key._ekey, _key._nkey);
		}
		/*
		�ļ�������
			�ֽ�����д��getline��>>��<<
			�ֽ�����д��read��write
			*/
		fout.write((char*)bufferOut, cnum* sizeof(DataType));
	}

	delete[] buffer;//�ͷſռ�
	delete[] bufferOut;

	fin.close();//����close���ļ�����ص�����Ҫ�ɲ�Ҫ
	fout.close();

}
void Rsa::Dcrept(const char*filename, const char *fileout)//�����ļ�
{
	std::ifstream fin(filename, std::ifstream::binary);//�����ļ�������,�������Ʒ�ʽ��
	std::ofstream fout(fileout, std::ifstream::binary);//����ļ�������
	if (!fin.is_open())
	{
		perror("file open failed!");
		return;
	}
	DataType *buffer = new DataType[NUMBER];

	char *bufferOut = new char[NUMBER];
	while (!fin.eof())
	{
		fin.read((char*)buffer, NUMBER*sizeof(DataType));//���ļ������ֽ���
		int num = fin.gcount();//���ܶ������Ǹ�����ֽڣ�num��¼��ǰ�������ֽ���
		num /= sizeof(DataType);//?
		for (int i = 0; i < num; i++)
		{
			//������char���ͣ��ʶ���Ҫ����ת��
			bufferOut[i] = (char)Dcrept(buffer[i], _key._dkey, _key._nkey);
		}
		fout.write(bufferOut, num);
	}
	delete[] buffer;//�ͷ�
	delete[] bufferOut;

	fin.close();//����close���ļ�����ص�����Ҫ�ɲ�Ҫ
	fout.close();
}

void Rsa::Getkeys()
{
	DataType p1 = GetPrime();
	DataType p2 = GetPrime();
	while (p1 == p2)//�ж��������Ƿ���ͬ
	{
		p2 = GetPrime();//��ͬ�Ļ������»�ȡ
	}

	std::cout << "p1��" << p1 << std::endl; 
	std::cout << "p2��" << p2 << std::endl;

	DataType orla = GetOrla(p1,p2);
	std::cout << "orla��" << orla << std::endl;
	std::cout << "oqla finish" << std::endl;

	_key._nkey = GetNkey(p1,p2);//��ȡ������Կ
	std::cout << "nkey��" << _key._nkey << std::endl;
	std::cout << "pkey finish" << std::endl;

	_key._ekey = GetEkey(orla);//��ȡ������Կ
	std::cout << "ekey��" << _key._ekey << std::endl;
	std::cout << "ekey finish" << std::endl;

	_key._dkey = GetDkey(_key._ekey, orla);//��ȡ������Կ
	std::cout << "dkey��" << _key._dkey << std::endl;
	std::cout << "dkey finish" << std::endl;

}
Key Rsa::GetallKey()
{
	return _key;
}
DataType Rsa::Ecrept(DataType data, DataType ekey, DataType nkey)//���ܺ���
{
	
	//pow����������½�����ԣ���ʱ��Ҫ��ȡ������ȡģ����
	//return (DataType)pow(data, ekey) % nkey;
	//i��0-------���һλ
	DataType Ai = data;
	DataType msge = 1;
	//data^ekey%nkey
	while (ekey)
	{
		if (ekey & 1)//�õ���0λ��ֵ
		{
			msge = (msge*Ai) % nkey;
		}
			ekey >>= 1;//����һλ�൱��/2
			Ai = (Ai*Ai) % nkey;
	}
	return msge;
}

DataType Rsa::Dcrept(DataType data, DataType dkey, DataType nkey)//���ܺ���
{
	return Ecrept(data, dkey, nkey);
}

DataType Rsa::GetPrime()//����һ������
{
	std::cout << "Getprime()" << std::endl;
	//srand(time(NULL)); //���������󷵻ص���һ���������ݣ��ʶ��ڴ����в���ʹ��
	brdm::mt19937 a(time(nullptr));//������ķ�����
	boost::random::uniform_int_distribution<DataType>dist(0, DataType(1) << 256);//ָ���ֲ�����Χ
	DataType prime;
	while (true)
	{
		prime = dist(a);
		//std::cout << "Bignum Random��"<<prime << std::endl;
		if (IsPrimeBignum(prime))
		{
			break;
		}
	}
	std::cout << "Getprime() finish!" << std::endl;
	return prime;
}

bool Rsa::IsPrime(DataType data)//�ж�һ�����Ƿ�Ϊ����
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

//�жϴ����Ƿ�Ϊ������Ҫ�ж�����
//һ���жϵ���data�ǲ�������
//Ȼ�����жϵ���(data - 1) / 2�ǲ�������
bool Rsa::IsPrimeBignum(DataType data)//�ж�һ�������Ƿ�Ϊ����
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

//��n=pq
DataType Rsa::GetNkey(DataType p1, DataType p2)//��ȡ�����Ĳ���,����Ϊ��������
{
	return p1*p2;
}

//���(n)=(p-1)*(q-1)
DataType Rsa::GetOrla(DataType p1, DataType p2)//ŷ������
{
	return (p1 - 1)*(p2 - 1);
}

//��e�� ���ѡ��һ������e��������1< e < ��(n)����e���(n) ���ʡ�
DataType Rsa::GetEkey(DataType orla)//������Կ������Ϊŷ����������(n);
{
	//srand(time(NULL));
	brdm::mt19937 a(time(nullptr));//������ķ�����
	boost::random::uniform_int_distribution<DataType>dist(2, orla);//ָ���ֲ���ekey��Χ��2<e<��(n)
	DataType e;
	while (true)
	{
		e = dist(a);
		if (e > 1 && GetGcd(e, orla) == 1)//e>1,����e���(n) ���ʼ����Լ��λ1
		{
			return e;
		}
	}
}

//��d��e*d%��(n)=1
DataType Rsa::GetDkey(DataType ekey, DataType orla)//������Կ������Ϊ���ܵ���Կ�͹�������
{
	DataType x = 0, y = 0;
	Exgcd(ekey, orla, x, y);
	//�任���ý�����Կ��һ���Ƚ�С����ֵ
	return (x%orla + orla) % orla;

	/*//���㷨ʱ�临�Ӷȸ�
	DataType d=orla/ekey;
	while (true)
	{
		if ((d*ekey) % orla == 1)
			return d;
		d++;
	}*/
}

//շת�����

DataType Rsa::GetGcd(DataType data1, DataType data2)//�ж����������Լ���Ƿ�Ϊ1
{
	DataType tmp;
	while (tmp = (data1%data2))
	{
		data1 = data2;
		data2 = tmp;
	}
	return data2;
}

//��ģ��Ԫ�أ���������Կ
DataType Rsa::Exgcd(DataType a, DataType b, DataType &x, DataType &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd= Exgcd(b, a%b, x, y);//���Լ��
	DataType x1 = x,y1=y;
	x = y1;
	y = x1 - a / b*y1;
	return gcd;
}