#include "employee.h"
#include<iostream>
using namespace std;

//���캯��
employee::employee(int id, string name, int depId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depId = depId;
}

//��ʾְ����Ϣ
void employee::ShowInfo()
{
	cout << "��ţ�" << m_id
		<< "\t������" << m_name
		<< "\t��λ��" << GetDepName()
		<< "\tְ����ɾ����´������" << endl;
}

//��ȡ��λ����
string employee::GetDepName()
{
	return "��ͨԱ��";
}