#pragma once
#include "worker.h"

//��ְͨ����
class employee :public worker
{
public:

	//���캯��
	employee(int id, string name, int depId);

	//��ʾְ����Ϣ
	void ShowInfo();

	//��ȡ��λ����
    string GetDepName();
};
