#pragma once
#include "worker.h"
using namespace std;

//������
class manager :public worker
{
public:

	//���캯��
	manager(int id, string name, int depId);

	//��ʾְ����Ϣ
	void ShowInfo();

	//��ȡ��λ����
	string GetDepName();

};


