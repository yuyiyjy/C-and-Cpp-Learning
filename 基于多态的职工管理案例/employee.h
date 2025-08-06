#pragma once
#include "worker.h"

//普通职工类
class employee :public worker
{
public:

	//构造函数
	employee(int id, string name, int depId);

	//显示职工信息
	void ShowInfo();

	//获取岗位名称
    string GetDepName();
};
