#pragma once
#include "worker.h"
using namespace std;

class boss :public worker
{
public:

	//���캯��
	boss(int id, string name, int depId);

	//��ʾְ����Ϣ
	void ShowInfo();

	//��ȡ��λ����
	string GetDepName();
};
