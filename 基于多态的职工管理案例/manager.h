#pragma once
#include "worker.h"
using namespace std;

//经理类
class manager :public worker
{
public:

	//构造函数
	manager(int id, string name, int depId);

	//显示职工信息
	void ShowInfo();

	//获取岗位名称
	string GetDepName();

};


