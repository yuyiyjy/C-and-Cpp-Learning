#include "WorkerManager.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

int main()
{
	//����һ���������
	WorkerManager wm;
	//��ӡ�˵�

	int choice;

	while (1)
	{
		wm.ShowMenu();
		cout << "����������ѡ��" << " ";
		cin >> choice;

		switch (choice)
		{
		case 1:                   //�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 2:                   //������ְ��
			wm.AddEmp();
			break;
		case 3:                  //��ʾ����ְ����Ϣ
			wm.ShowEmp();
			break;
		case 4:                 //ɾ��ְ��
			wm.DeleteEmp();
			break;
		case 5:                 //�޸�ְ����Ϣ
			wm.ModifyEmp();
			break;
		case 6:                 //����ְ��
			wm.SearchEmp();
			break;
		case 7:                //����ְ����Ž�������
			wm.SortEmp();
			break;
		case 8:                //����ļ�
			wm.ClearFile();
			break;
		default:
			{
				cout << "�����������������룡" << endl;
				system("pause");
				system("cls");
				break;
			}
		}

	}

	return 0;
}

