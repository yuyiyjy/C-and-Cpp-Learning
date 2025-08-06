#pragma once
#include "worker.h"
using namespace std;

class boss :public worker
{
public:

	//构造函数
	boss(int id, string name, int depId);

	//显示职工信息
	void ShowInfo();

	//获取岗位名称
	string GetDepName();
};
