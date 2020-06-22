#include"bignum.h"

Bignum::Bignum(const std::string &num)
:_number(num)//调字符串的拷贝构造
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
	return Bignum(ret.first);//商的结果
}
Bignum Bignum::operator%(Bignum&bi)
{
	std::pair<std::string, std::string>ret = dev(_number, bi._number);
	return Bignum(ret.second);//余数的结果
}



//模拟加法运算
std::string Bignum::add(std::string num1, std::string num2)//加
{
	//位数补齐，在前面进行补0的操作
	int len1 = num1.size();
	int len2 = num2.size();
	int diffnum = abs(len1-len2);//计算量长度之间的差值
	int longsize = len1 > len2 ? len1 : len2;//谁的长度长取谁

	if (len1 < len2)
	{
		num1.insert(0, diffnum, '0');//头插，哪个小在哪个前面补diffnum个0
	}
	else if (len2 < len1)
	{
		num2.insert(0, diffnum, '0');
	}
	std::string ret;
	ret.resize(longsize);//operator[]

	//逐位相加
	int step = 0;//进位
	for (int i = longsize - 1; i >= 0; i--)//从最后一位开始相加
	{
		ret[i] = (num1[i] - '0') + (num2[i] - '0') + step;//对应位数字的和再加进位，加的是ASCII码的值，所以得减‘0’
		ret[i] += '0';//将加完后的值转换成字符
		//更新
		if (ret[i] > '9')
		{
			ret[i] -= 10;
			step = 1;//进位为1
		}
		else
			step = 0;//进位为0
	}
	if (step == 1)
		ret.insert(0, 1, '1');//头插一个字符‘1’，表示有进位
	return ret;
}

//假设num1>=num2的，不会存在越界的问题；
//如果遇到负数问题，就当做加一个负数问题，按加法做
std::string Bignum::sub(std::string num1, std::string num2)//减
{
	//位数补齐，在前面进行补0的操作
	int len1 = num1.size();
	int len2 = num2.size();
	int diffnum = abs(len1 - len2);//计算量长度之间的差值
	int longsize = len1 > len2 ? len1 : len2;//谁的长度长取谁

	if (len1 < len2)
	{
		num1.insert(0, diffnum, '0');//头插，哪个小在哪个前面补diffnum个0
	}
	else if (len2 < len1)
	{
		num2.insert(0, diffnum, '0');
	}

	std::string ret;
	ret.resize(longsize);//operator[]
	for (int i = longsize - 1; i >= 0; i--)
	{
		//判断是否需要借位
		if (num1[i] < num2[i])
		{
			num1[i] += 10;
			num1[i - 1]--;//更新高位
		}

		ret[i] = (num1[i] - '0')-(num2[i]-'0')+'0';//相减完成之后，就变回字符

	}

	//删除前置0
	while (ret.size() > 1 && ret[0] == '0')
	{
		ret.erase(0,1);//删除第0个位置的一个字符
	}
	return ret;
}

//模拟乘法的操作
std::string Bignum::mul(std::string num1, std::string num2)//乘
{
	//用位数低的数乘以位数高的数，num1*num2
	//简化乘法的过程
	if (num2.size() > num1.size())
	{
		swap(num1, num2);
	}

	std::string ret="0";//ret:"\0"
	for(int i = num2.size() - 1; i >= 0; i--)//从低位开始相乘
	{
		//获取当前乘数对应位的值
		int curDigit = num2[i] - '0';
		//进位
		int step = 0;
		//当前位乘积的结果
		std::string tmp = num1;
		for (int j = tmp.size() - 1; j >= 0; j--)
		{
			//逐位相乘
			tmp[j] = (tmp[j] - '0')*curDigit + step;//当前位的整数值*被乘数+进位；计算结果为整数值
			//更新进位，值
			if (tmp[j] > 9)
			{
				step = tmp[j] / 10;//进位
				tmp[j] = tmp[j] - step * 10;
			}
			else
				step = 0;//若无进位，step不需要更新，还是0

			tmp[j] += '0';//将值还原成字符
		}
		//最后判断是否需要进位
		if (step > 0)
			tmp.insert(0, 1, step + '0');//第0个位置插入一个字符（即进位值）
		//判断完进位，需要补零操作
		tmp.append(num2.size() - 1 - i, '0');
		//累加一次乘法的结果
		ret = add(ret, tmp);
	}
	return ret;
}

//借助减法实现,num1/num2
std::pair<std::string, std::string>Bignum::dev(std::string num1, std::string num2)//除；商和余数都要返回
{
	std::string ret;//商
	std::string rem=num1;//余数，余数最开始就是被除数
	//给除数进行放大,按照10的倍数放大
	int diffNum = num1.size() - num2.size();//记录两个数的位差
	num2.append(diffNum, '0');//位差为多少就给num2(除数补多少个0)
	for (int i = 0; i <= diffNum; i++)
	{
		//记录减法执行的次数
		char count = '0';
		while (true)
		{
			if (less(rem, num2))
				break;
			rem = sub(rem, num2);
			count++;
		}
		ret += count;
		//除数减少10倍
		num2.pop_back();
	}
	//删除前置的0
	while (ret.size() > 1 && ret[0] == '0')//结果的位置是大于1的，并且第0个位置是字符‘0’
	{
		ret.erase(0, 1);
	}
	//返回<商,余数>
	return make_pair(ret, rem);

}

bool Bignum::less(std::string& num1, std::string& num2)
{
	if (num1.size() < num2.size())
		return true;
	if (num1.size()>num2.size())
		return false;
	//长度相同时
	return num1 < num2;
}

//输出运算符重载
 std::ostream &operator<< (std::ostream & _cout, Bignum &bi)//访问类的私有成员
{
	 _cout << bi._number << std::endl;
	 return _cout;
}