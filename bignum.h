#pragma once
#include<string>
#include<utility>//pair的头文件
#include<iostream>
class Bignum
{

public:
	Bignum(){}//无参构造
	Bignum(const std::string &num);//构造函数，通过字符串进行初始化
	Bignum(const int num);//也可以通过整型数字进行初始化
	//运算符重载
	Bignum operator+(Bignum&bi);
	Bignum operator-(Bignum&bi);
	Bignum operator*(Bignum&bi);
	Bignum operator / (Bignum&bi);
	Bignum operator%(Bignum&bi);
	//输出运算符重载
	friend std::ostream &operator<< (std::ostream & _cout, Bignum &bi);

	/*
	自己还可以扩展实现这些运算符的操作

	//++a
	Bignum& operator++();
	//a++
	Bignum& operator++(int);
	//--a
	Bignum& operator--();
	//a--
	Bignum& operator--(int);


	Bignum& operator+=(Bignum&bi);
	Bignum& operator-=(Bignum&bi);
	Bignum& operator*=(Bignum&bi);
	Bignum& operator/= (Bignum&bi);
	Bignum& operator%=(Bignum&bi);*/



private:
	//通过字符串表示
	std::string _number;

	//传引用&，对于字符串来说设计深浅拷贝问题，传值的效率不是很高，数据变化，不能用const
	//给成引用不能直接传字符串的，传字符串可能会引起隐式类型转换

	//传值，不传引用
	std::string add(std::string num1, std::string num2);//加
	std::string sub(std::string num1, std::string num2);//减
	std::string mul(std::string num1, std::string num2);//乘
	std::pair<std::string, std::string>dev(std::string num1, std::string num2);//除；商和余数都要返回
	bool less(std::string& num1, std::string& num2);

};