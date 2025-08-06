#include "employee.h"
#include<iostream>
using namespace std;

//构造函数
employee::employee(int id, string name, int depId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depId = depId;
}

//显示职工信息
void employee::ShowInfo()
{
	cout << "编号：" << m_id
		<< "\t姓名：" << m_name
		<< "\t岗位：" << GetDepName()
		<< "\t职责：完成经理下达的任务" << endl;
}

//获取岗位名称
string employee::GetDepName()
{
	return "普通员工";
}