#include "manager.h"
using namespace std;

//构造函数
manager::manager(int id, string name, int depId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depId = depId;
}

//显示职工信息
void manager::ShowInfo()
{
	cout << "编号：" << m_id
		<< "\t姓名：" << m_name
		<< "\t岗位：" << GetDepName()
		<< "\t职责：管理普通员工，接受老板的差遣" << endl;
}

//获取岗位名称
string manager::GetDepName()
{
	return "经理";
}