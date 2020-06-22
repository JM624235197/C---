#pragma once
#include<string>
#include<utility>//pair��ͷ�ļ�
#include<iostream>
class Bignum
{

public:
	Bignum(){}//�޲ι���
	Bignum(const std::string &num);//���캯����ͨ���ַ������г�ʼ��
	Bignum(const int num);//Ҳ����ͨ���������ֽ��г�ʼ��
	//���������
	Bignum operator+(Bignum&bi);
	Bignum operator-(Bignum&bi);
	Bignum operator*(Bignum&bi);
	Bignum operator / (Bignum&bi);
	Bignum operator%(Bignum&bi);
	//������������
	friend std::ostream &operator<< (std::ostream & _cout, Bignum &bi);

	/*
	�Լ���������չʵ����Щ������Ĳ���

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
	//ͨ���ַ�����ʾ
	std::string _number;

	//������&�������ַ�����˵�����ǳ�������⣬��ֵ��Ч�ʲ��Ǻܸߣ����ݱ仯��������const
	//�������ò���ֱ�Ӵ��ַ����ģ����ַ������ܻ�������ʽ����ת��

	//��ֵ����������
	std::string add(std::string num1, std::string num2);//��
	std::string sub(std::string num1, std::string num2);//��
	std::string mul(std::string num1, std::string num2);//��
	std::pair<std::string, std::string>dev(std::string num1, std::string num2);//�����̺�������Ҫ����
	bool less(std::string& num1, std::string& num2);

};