#include "boss.h"
using namespace std;

// ���캯��
boss::boss(int id, string name, int depId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depId = depId;
}

//��ʾְ����Ϣ
void boss::ShowInfo()
{
	cout << "��ţ�" << m_id
		<< "\t������" << m_name
		<< "\t��λ��" << GetDepName()
		<< "\tְ�𣺹���˾��������" << endl;
}

//��ȡ��λ����
string boss::GetDepName()
{
	return "�ϰ�";
}