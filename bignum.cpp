#include"bignum.h"

Bignum::Bignum(const std::string &num)
:_number(num)//���ַ����Ŀ�������
{
}

Bignum Bignum::operator+(Bignum&bi)
{
	std::string ret= add(_number, bi._number);
	return Bignum(ret);
}

Bignum Bignum::operator-(Bignum&bi)
{
	std::string ret = sub(_number, bi._number);
	return Bignum(ret);
}
Bignum Bignum::operator*(Bignum&bi)
{
	std::string ret = mul(_number, bi._number);
	return Bignum(ret);
}
Bignum Bignum::operator/(Bignum&bi)
{
	std::pair<std::string, std::string>ret = dev(_number, bi._number);
	return Bignum(ret.first);//�̵Ľ��
}
Bignum Bignum::operator%(Bignum&bi)
{
	std::pair<std::string, std::string>ret = dev(_number, bi._number);
	return Bignum(ret.second);//�����Ľ��
}



//ģ��ӷ�����
std::string Bignum::add(std::string num1, std::string num2)//��
{
	//λ�����룬��ǰ����в�0�Ĳ���
	int len1 = num1.size();
	int len2 = num2.size();
	int diffnum = abs(len1-len2);//����������֮��Ĳ�ֵ
	int longsize = len1 > len2 ? len1 : len2;//˭�ĳ��ȳ�ȡ˭

	if (len1 < len2)
	{
		num1.insert(0, diffnum, '0');//ͷ�壬�ĸ�С���ĸ�ǰ�油diffnum��0
	}
	else if (len2 < len1)
	{
		num2.insert(0, diffnum, '0');
	}
	std::string ret;
	ret.resize(longsize);//operator[]

	//��λ���
	int step = 0;//��λ
	for (int i = longsize - 1; i >= 0; i--)//�����һλ��ʼ���
	{
		ret[i] = (num1[i] - '0') + (num2[i] - '0') + step;//��Ӧλ���ֵĺ��ټӽ�λ���ӵ���ASCII���ֵ�����Եü���0��
		ret[i] += '0';//��������ֵת�����ַ�
		//����
		if (ret[i] > '9')
		{
			ret[i] -= 10;
			step = 1;//��λΪ1
		}
		else
			step = 0;//��λΪ0
	}
	if (step == 1)
		ret.insert(0, 1, '1');//ͷ��һ���ַ���1������ʾ�н�λ
	return ret;
}

//����num1>=num2�ģ��������Խ������⣻
//��������������⣬�͵�����һ���������⣬���ӷ���
std::string Bignum::sub(std::string num1, std::string num2)//��
{
	//λ�����룬��ǰ����в�0�Ĳ���
	int len1 = num1.size();
	int len2 = num2.size();
	int diffnum = abs(len1 - len2);//����������֮��Ĳ�ֵ
	int longsize = len1 > len2 ? len1 : len2;//˭�ĳ��ȳ�ȡ˭

	if (len1 < len2)
	{
		num1.insert(0, diffnum, '0');//ͷ�壬�ĸ�С���ĸ�ǰ�油diffnum��0
	}
	else if (len2 < len1)
	{
		num2.insert(0, diffnum, '0');
	}

	std::string ret;
	ret.resize(longsize);//operator[]
	for (int i = longsize - 1; i >= 0; i--)
	{
		//�ж��Ƿ���Ҫ��λ
		if (num1[i] < num2[i])
		{
			num1[i] += 10;
			num1[i - 1]--;//���¸�λ
		}

		ret[i] = (num1[i] - '0')-(num2[i]-'0')+'0';//������֮�󣬾ͱ���ַ�

	}

	//ɾ��ǰ��0
	while (ret.size() > 1 && ret[0] == '0')
	{
		ret.erase(0,1);//ɾ����0��λ�õ�һ���ַ�
	}
	return ret;
}

//ģ��˷��Ĳ���
std::string Bignum::mul(std::string num1, std::string num2)//��
{
	//��λ���͵�������λ���ߵ�����num1*num2
	//�򻯳˷��Ĺ���
	if (num2.size() > num1.size())
	{
		swap(num1, num2);
	}

	std::string ret="0";//ret:"\0"
	for(int i = num2.size() - 1; i >= 0; i--)//�ӵ�λ��ʼ���
	{
		//��ȡ��ǰ������Ӧλ��ֵ
		int curDigit = num2[i] - '0';
		//��λ
		int step = 0;
		//��ǰλ�˻��Ľ��
		std::string tmp = num1;
		for (int j = tmp.size() - 1; j >= 0; j--)
		{
			//��λ���
			tmp[j] = (tmp[j] - '0')*curDigit + step;//��ǰλ������ֵ*������+��λ��������Ϊ����ֵ
			//���½�λ��ֵ
			if (tmp[j] > 9)
			{
				step = tmp[j] / 10;//��λ
				tmp[j] = tmp[j] - step * 10;
			}
			else
				step = 0;//���޽�λ��step����Ҫ���£�����0

			tmp[j] += '0';//��ֵ��ԭ���ַ�
		}
		//����ж��Ƿ���Ҫ��λ
		if (step > 0)
			tmp.insert(0, 1, step + '0');//��0��λ�ò���һ���ַ�������λֵ��
		//�ж����λ����Ҫ�������
		tmp.append(num2.size() - 1 - i, '0');
		//�ۼ�һ�γ˷��Ľ��
		ret = add(ret, tmp);
	}
	return ret;
}

//��������ʵ��,num1/num2
std::pair<std::string, std::string>Bignum::dev(std::string num1, std::string num2)//�����̺�������Ҫ����
{
	std::string ret;//��
	std::string rem=num1;//�����������ʼ���Ǳ�����
	//���������зŴ�,����10�ı����Ŵ�
	int diffNum = num1.size() - num2.size();//��¼��������λ��
	num2.append(diffNum, '0');//λ��Ϊ���پ͸�num2(���������ٸ�0)
	for (int i = 0; i <= diffNum; i++)
	{
		//��¼����ִ�еĴ���
		char count = '0';
		while (true)
		{
			if (less(rem, num2))
				break;
			rem = sub(rem, num2);
			count++;
		}
		ret += count;
		//��������10��
		num2.pop_back();
	}
	//ɾ��ǰ�õ�0
	while (ret.size() > 1 && ret[0] == '0')//�����λ���Ǵ���1�ģ����ҵ�0��λ�����ַ���0��
	{
		ret.erase(0, 1);
	}
	//����<��,����>
	return make_pair(ret, rem);

}

bool Bignum::less(std::string& num1, std::string& num2)
{
	if (num1.size() < num2.size())
		return true;
	if (num1.size()>num2.size())
		return false;
	//������ͬʱ
	return num1 < num2;
}

//������������
 std::ostream &operator<< (std::ostream & _cout, Bignum &bi)//�������˽�г�Ա
{
	 _cout << bi._number << std::endl;
	 return _cout;
}