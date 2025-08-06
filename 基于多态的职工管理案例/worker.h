#pragma once
#include<iostream>
#include<string>
using namespace std;

//职工抽象父类
class worker
{
public:
	//显示职工信息
	virtual void ShowInfo() = 0;

	//获取岗位名称
	virtual string GetDepName() = 0;

	//职工编号
	int m_id;
	//职工姓名
	string m_name;
	//职工部门编号
	int m_depId;

};