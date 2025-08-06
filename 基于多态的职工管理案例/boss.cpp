#include "boss.h"
using namespace std;

// 构造函数
boss::boss(int id, string name, int depId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depId = depId;
}

//显示职工信息
void boss::ShowInfo()
{
	cout << "编号：" << m_id
		<< "\t姓名：" << m_name
		<< "\t岗位：" << GetDepName()
		<< "\t职责：管理公司各种事务" << endl;
}

//获取岗位名称
string boss::GetDepName()
{
	return "老板";
}