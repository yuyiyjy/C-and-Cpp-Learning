#pragma once
#include<iostream>
#include<string>
using namespace std;

//ְ��������
class worker
{
public:
	//��ʾְ����Ϣ
	virtual void ShowInfo() = 0;

	//��ȡ��λ����
	virtual string GetDepName() = 0;

	//ְ�����
	int m_id;
	//ְ������
	string m_name;
	//ְ�����ű��
	int m_depId;

};