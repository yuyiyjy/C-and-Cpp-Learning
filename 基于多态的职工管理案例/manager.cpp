#include "manager.h"
using namespace std;

//���캯��
manager::manager(int id, string name, int depId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depId = depId;
}

//��ʾְ����Ϣ
void manager::ShowInfo()
{
	cout << "��ţ�" << m_id
		<< "\t������" << m_name
		<< "\t��λ��" << GetDepName()
		<< "\tְ�𣺹�����ͨԱ���������ϰ�Ĳ�ǲ" << endl;
}

//��ȡ��λ����
string manager::GetDepName()
{
	return "����";
}