#include "WorkerManager.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"
using namespace std;

//���캯��
WorkerManager::WorkerManager()
{
	//�ڹ��캯���н����Գ�ʼ��
	
	//���һ���ļ�������
		ifstream ifs;
		ifs.open(FileOfEmp, ios::in);
		if (!ifs.is_open())
		{
			//�ļ�Ϊ��
			//cout << "�ļ�������" << endl;
			m_Num = 0;
			m_EmpArry = NULL;
			m_FileIsEmpty = true;
			return;
		}

	//��������ļ����ڵ�Ϊ��
		else if (ifs.is_open())
		{
			char ch;
			ifs >> ch;
			if (ifs.eof())
			{
				//cout << "�ļ�Ϊ��" << endl;
				m_Num = 0;
				m_EmpArry = NULL;
				m_FileIsEmpty = true;
				return;
			}
		}

	//��������ļ������Ҳ�Ϊ��
		m_Num = GetEmpNum();
		m_FileIsEmpty = false;
		m_EmpArry = new worker * [m_Num];
		//��ʼ��ְ������
		InitEmpArry();
}

//��������
WorkerManager::~WorkerManager()
{
	//�ͷŵ�ְ������
	if (m_EmpArry != NULL)
	{
		for (int i = 0; i < m_Num; i++)
			delete m_EmpArry[i];

		delete[] m_EmpArry;
	}
}

//��ӡ�˵�
void WorkerManager::ShowMenu()
{
	cout << "************************��ӭʹ��ְ������ϵͳ************************" << endl;
	cout << "************************1.�˳��������************************" << endl;
	cout << "************************2.����ְ����Ϣ************************" << endl;
	cout << "************************3.��ʾְ����Ϣ************************" << endl;
	cout << "************************4.ɾ����ְְ��************************" << endl;
	cout << "************************5.�޸�ְ����Ϣ************************" << endl;
	cout << "************************6.����ְ����Ϣ************************" << endl;
	cout << "************************7.���ձ������************************" << endl;
	cout << "************************8.��������ĵ�************************" << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

//��ְ�����������ļ���
void WorkerManager::NumToFile(int num)
{
	//�����ļ�
	ofstream ofs;
	ofs.open(FileOfNum, ios::out);
	ofs << num;
	ofs.close();
}

//���ļ��л�ȡְ������
int WorkerManager::GetEmpNum()
{
	//���ļ��ж�ȡ����
	ifstream ifs;
	ifs.open(FileOfNum, ios::in);
    string Num;
	getline(ifs,Num);
	ifs.close();

	int GetNum;
	//���ַ���תΪ��������
	try
	{
		GetNum = stoi(Num);
	}
	catch (const invalid_argument& e) {
		std::cout << "�Ƿ�����" << std::endl;
	}
	catch (const out_of_range& e) {
		std::cout << "��ֵ������Χ" << std::endl;
	}

	return GetNum;
}

//��ʼ��ְ������
void WorkerManager::InitEmpArry()
{
	//���ļ�
	ifstream ifs;
	ifs.open(FileOfEmp, ios:: in);
    
	//��ȡ����
	int id;
	string name;
	int DepId;
	//����
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> DepId)
	{
		worker* NewWorker = NULL;
		switch (DepId)
		{
		case 1:               //��ͨԱ��
			NewWorker = new employee(id, name, DepId);
			break;
		case 2:              //����
			NewWorker = new manager(id, name, DepId);
			break;
		case 3:             //�ϰ�
			NewWorker = new boss(id, name, DepId);
			break;
		}

		//����������
		m_EmpArry[index] = NewWorker;
		index++;
	}

	ifs.close();
}

//��ְ����Ϣ�����ļ���
void WorkerManager::AddToFile()
{
	ofstream ofs;
	ofs.open(FileOfEmp, ios::out);

	//�������е���Ϣ���д���ļ�
	for (int i = 0; i < m_Num; i++)
	{
		ofs << m_EmpArry[i]->m_id << " "
			<< m_EmpArry[i]->m_name << " "
			<< m_EmpArry[i]->m_depId << endl;
	}

	ofs.close();
}

//�ж�ְ���Ƿ����
int WorkerManager::IsExit(int id)
{
	int index = -1;

	for (int i = 0; i < m_Num; i++)
	{
		//�ҵ���ְ��
		if (m_EmpArry[i]->m_id == id)
		{
			index = i;
			break;
		}
	}

	return index;
}

//����Ա��
void WorkerManager::AddEmp()
{
	//ѯ�����Ա��������
	int AddNum;
	//���whileѭ��
	while (1)
	{
		cout << "������Ҫ��Ӽ�����ְ����" << " ";
		cin >> AddNum;
		//�ж�����ĺ�����
		if (AddNum > 0)
		{
			//��¼�¿ռ�Ĵ�С�������¿ռ�
			int NewSize = m_Num + AddNum;
			worker** NewSpace = new worker * [NewSize];


			//�ж�ԭ�����Ƿ�Ϊ�գ���Ϊ������Ҫ��ԭ�����е�Ԫ�ؿ������������У����ͷ�ԭ����
			if (m_EmpArry != NULL)
			{
				for (int i = 0; i < m_Num; i++)
				{
					NewSpace[i] = m_EmpArry[i];
				}
			}

			//��������ӵ�Ա������Ϣ
			for (int j = 0; j < AddNum; j++)
			{
				int NewId;
				string NewName;
				int NewDepId;

				//������ʱҪ��ֹ����ظ�,��Ҫ���ԭ����ҲҪ����¼����Ԫ��
				while (1) 
				{
					cout << "�������" << j + 1 << "����ְ���ı�ţ�" << " ";
					cin >> NewId;

					//���ڱ���Ƿ��ظ�
					bool IsDuplicate = false;
                    
					//���ԭ����
					if (m_EmpArry != NULL)
					{
						for (int i = 0; i < m_Num; i++)
						{
							if (m_EmpArry[i]->m_id == NewId)
							{
								IsDuplicate = true;
								break;              //����for���ԭ�����forѭ��
							}
						}
					}

					//����¼����Ԫ��
					for (int i = 0; i < j; i++)
					{
						if (NewSpace[m_Num + i]->m_id == NewId)
						{
							IsDuplicate = true;
							break;                   //��������¼���Ԫ�ص�forѭ��
						}
					}

					if (IsDuplicate)
					{
						cout << "�Ѵ��ڸñ�ţ��뻻һ�����" << endl;
						continue;
					}

					else break;          //��������ѭ��

				}   //��ֹ����ظ���whileѭ������

				cout << "�������" << j + 1 << "����ְ����������" << " ";
				cin >> NewName;

				worker* NewWorker = NULL;
				while (1)
				{
					cout << "��ѡ���" << j + 1 << "����ְ���Ĳ��ţ�" << endl;
					cout << "1.��ְͨ��" << endl;
					cout << "2.����" << endl;
					cout << "3.�ϰ�" << endl;
					cin >> NewDepId;

					//������ְ�������ʹ�����ͬ�Ķ���
					switch (NewDepId)
					{
					case 1:
						NewWorker = new employee(NewId, NewName, NewDepId);
						break;
					case 2:
						NewWorker = new manager(NewId, NewName, NewDepId);
						break;
					case 3:
						NewWorker = new boss(NewId, NewName, NewDepId);
						break;
					default:
						cout << "�����������������룡" << endl;
						continue;                                        //������������������һ��whileѭ��
					}

					//����Сwhileѭ��
					if (NewWorker != NULL)
						break;
				}         //��ֹѡ�������������whileѭ������

				//����ְ����ӵ�����
				NewSpace[m_Num + j] = NewWorker;

			}  //��ÿһλ��ְ�������forѭ������

			//��������
			m_Num = NewSize;
			m_EmpArry = NewSpace;
			m_FileIsEmpty = false;
			
			//������whileѭ��
			cout << "�ɹ����" << AddNum << "����ְ��" << endl;
			//д���ļ�
			AddToFile();
			NumToFile(m_Num);
			break;

		} //������������Ե�if����

		//������벻�������½���ѭ������
		else
		{
			cout << "�����������������룡" << endl;
			continue;
		}
	}  //��whileѭ���ĳ���

	//������������
	system("pause");
	system("cls");
}

//��ʾ����ְ����Ϣ
void WorkerManager::ShowEmp()
{
	//�ļ������ڻ���Ϊ��
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ��" << endl;
		system("pause");
		system("cls");
		return;
	}

	else
	{
		//���ö�̬�����ʾְ����Ϣ
		for (int i = 0; i < m_Num; i++)
			m_EmpArry[i]->ShowInfo();
	}

	//���������������
	system("pause");
	system("cls");
}

void WorkerManager::DeleteEmp()
{
	//����ļ������ڻ����ļ�Ϊ��
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		system("cls");
		return;
	}

	//���ö�̬�����ʾְ����Ϣ
	for (int i = 0; i < m_Num; i++)
		m_EmpArry[i]->ShowInfo();

	int DelIndex;
	cout << "������Ҫɾ����ְ�����Ϊ��" << " ";
	cin >> DelIndex;

	//���ú���
	int index = IsExit(DelIndex);
	
	//����ҵ�����Ҫɾ����ְ��
	if (index != -1)
	{
		//���������һ��ǰ�Ʋ���
		for (int i = index; i < m_Num - 1; i++)
		{
			m_EmpArry[i] = m_EmpArry[i + 1];
		}

		//ǰ����Ϻ��޸�����
		m_Num--;
		//�������������д���ļ�
		AddToFile();
		//���µ�ְ������д���ļ�
		NumToFile(m_Num);

		cout << "ɾ���ɹ�" << endl;
	}

	else
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
	}

	//���������������
	system("pause");
	system("cls");
}

//�޸�ְ����Ϣ
void WorkerManager::ModifyEmp()
{
	//�ļ������ڻ����ļ�Ϊ��ʱ
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		system("cls");
		return;
	}

	//���ö�̬�����ʾְ����Ϣ
	for (int i = 0; i < m_Num; i++)
		m_EmpArry[i]->ShowInfo();

	int ModId;
	cout << "������Ҫ�޸ĵ�ְ���ı��Ϊ��" << " ";
	cin >> ModId;

	int index = IsExit(ModId);

	//����ҵ���ְ��
	if (index != -1)
	{
		//�Ƚ�ԭ������Ϣ����ɾ������ɾ��ǰ��Ҫ����ɱ��
		int OldId = m_EmpArry[index]->m_id;
		delete m_EmpArry[index];

		//��������ӵ�Ա������Ϣ
		int NewId;
		string NewName;
		int NewDepId;

		//������ʱҪ��ֹ����ظ�,ֻ�ü��ԭ�����г��˱������ı��
		while (1)
		{
			cout << "���������ְ�����±�ţ�" << " ";
			cin >> NewId;

			//���ڱ���Ƿ��ظ�
			bool IsDuplicate = false;

			//���ԭ����
				for (int i = 0; i < m_Num; i++)
				{
					//�޸ĵ��±�ſ��Ժ;ɱ��һ�������Ե��±����ɱ��һ��ʱֱ������forѭ������������Ƚ�
					if (NewId == OldId)
						break;

					if (m_EmpArry[i]->m_id == NewId)
					{
						IsDuplicate = true;
						break;              //����for���ԭ�����forѭ��
					}
				}
            
			//������ظ�
			if (IsDuplicate)
			{
				cout << "�Ѵ��ڸñ�ţ��뻻һ�����" << endl;
				continue;
			}

			else break;          //��������ѭ��

		}   //��ֹ����ظ���whileѭ������

		cout << "���������ְ������������" << " ";
		cin >> NewName;

		worker* NewWorker = NULL;
		while (1)
		{
			cout << "��ѡ�����ְ�����²��ţ�" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> NewDepId;

			//������ְ�������ʹ�����ͬ�Ķ���
			switch (NewDepId)
			{
			case 1:
				NewWorker = new employee(NewId, NewName, NewDepId);
				break;
			case 2:
				NewWorker = new manager(NewId, NewName, NewDepId);
				break;
			case 3:
				NewWorker = new boss(NewId, NewName, NewDepId);
				break;
			default:
				cout << "�����������������룡" << endl;
				continue;                                        //������������������һ��whileѭ��
			}

			//����Сwhileѭ��
			if (NewWorker != NULL)
				break;
		}         //��ֹѡ�������������whileѭ������

		//����ְ����ӵ�����
		m_EmpArry[index] = NewWorker;

		//���µ���Ϣд���ļ���
		AddToFile();

		cout << "�޸ĳɹ�" << endl;

	}  //�ҵ�ְ����if������

	else
	{
		cout << "�޸�ʧ�ܣ����޴���" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::SearchEmp()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}

	//�ļ�������
	else
	{
		cout << "1.��ְ����Ų�" << endl;
		cout << "2.��ְ��������" << endl;
		cout << "3.��ְ����λ��" << endl;
		int SearchWay;

		//��ֹѡ�񲻺����whileѭ��
		while (1)
		{
			cout << "��ѡ����ҷ�ʽ��" << " ";
			cin >> SearchWay;
			//����Ų�
			if (SearchWay == 1)
			{
				cout << "��������Ҫ���ҵ�ְ���ı�ţ�" << " ";
				int SearchId;
				cin >> SearchId;

				int index = IsExit(SearchId);

				//������ڸ�ְ��
				if (index != -1)
				{
					cout << "��ְ������Ϣ���£�" << endl;
					m_EmpArry[index]->ShowInfo();
				}

				else
				{
					cout << "��ְ���ı��Ϊ" << SearchId << endl;
				}

				break;          //�˳���ֹ���ҷ�ʽѡ�񲻺����whileѭ��
			}

			//�������飬����������
			if (SearchWay == 2)
			{
				//���ڱ���Ƿ��ҵ�
				bool Find1 = false;

				string SearchName;
				cout << "��������Ҫ���ҵ�ְ����������" << " ";
				cin >> SearchName;

				//������
				for (int i = 0; i < m_Num; i++)
				{
					//�ҵ��������ϵ�ְ��
					if (m_EmpArry[i]->m_name == SearchName)
					{
						cout << "���Ϊ" << m_EmpArry[i]->m_id << "��" << m_EmpArry[i]->m_name << "����Ϣ���£�" << endl;
						m_EmpArry[i]->ShowInfo();
						//���Ϊ�ҵ�
						Find1 = true;
						break;             //����forѭ��
					}

				}  //�������forѭ��

				//�������껹û���ҵ�
				if (!Find1)
				{
					cout << "û������Ϊ" << SearchName << "��ְ��" << endl;
				}

				break;                //�˳���ֹ���ҷ�ʽ�������whileѭ��
			}

			//����λ��
			if (SearchWay == 3)
			{
				cout << "1.��ͨԱ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;

				while (1)
				{
					int Dep;
					cout << "��ѡ����Ҫ���ҵĸ�λ��" << " ";
					cin >> Dep;

					//ѡ����ͨԱ��
					if (Dep == 1)
					{
						//���ڱ���Ƿ���ҵ�
						bool Find2 = false;

						//������
						for (int i = 0; i < m_Num; i++)
						{
							//�ҵ���λ���ϵ�ְ��
							if (m_EmpArry[i]->m_depId == 1)
							{
								cout << "���Ϊ" << m_EmpArry[i]->m_id << "��" << m_EmpArry[i]->m_name << "����Ϣ���£�" << endl;
								m_EmpArry[i]->ShowInfo();
								//���Ϊ�ҵ�
								Find2 = true;
							}
						}  //�������forѭ��

						//�������껹û���ҵ�
						if (!Find2)
						{
							cout << "û�и�λΪ��ͨԱ����ְ��" << endl;
						}

						break;                //�˳�whileѭ��
					}

					//��λΪ����
					if (Dep == 2)
					{
						//���ڱ���Ƿ���ҵ�
						bool Find3 = false;

						//������
						for (int i = 0; i < m_Num; i++)
						{
							//�ҵ���λ���ϵ�ְ��
							if (m_EmpArry[i]->m_depId == 2)
							{
								cout << "���Ϊ" << m_EmpArry[i]->m_id << "��" << m_EmpArry[i]->m_name << "����Ϣ���£�" << endl;
								m_EmpArry[i]->ShowInfo();
								//���Ϊ�ҵ�
								Find3 = true;
							}
						}  //�������forѭ��

						//�������껹û���ҵ�
						if (!Find3)
						{
							cout << "û�и�λΪ�����ְ��" << endl;
						}

						break;                //�˳�whileѭ��
					}

					if (Dep == 3)
					{
						//���ڱ���Ƿ���ҵ�
						bool Find4 = false;

						//������
						for (int i = 0; i < m_Num; i++)
						{
							//�ҵ���λ���ϵ�ְ��
							if (m_EmpArry[i]->m_depId == 3)
							{
								cout << "���Ϊ" << m_EmpArry[i]->m_id << "��" << m_EmpArry[i]->m_name << "����Ϣ���£�" << endl;
								m_EmpArry[i]->ShowInfo();
								//���Ϊ�ҵ�
								Find4 = true;
							}
						}  //�������forѭ��

						//�������껹û���ҵ�
						if (!Find4)
						{
							cout << "û�и�λΪ�����ְ��" << endl;
						}

						break;                //�˳�whileѭ��
					}

					else
					{
						cout << "�޴˸�λѡ�������������" << endl;
						continue;
					}
				}      //��ֹ��λѡ�񲻺����whileѭ��

				break;             //������ֹ���ҷ�ʽѡ�񲻺����whileѭ������
			}      //����λ��if����

			else
			{
				cout << "�޴˲��ҷ�ʽѡ�����������" << endl;
				continue;
			}
		}   //��ֹ���ҷ�ʽѡ�񲻺����whileѭ������

	}

	system("pause");
	system("cls");

}

//����ְ����Ž�������
void WorkerManager::SortEmp()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}

	else
	{
		cout << "1.����ְ�������������" << endl;
		cout << "2.����ְ����Ž�������" << endl;

		int SortWay;
		//��ֹѡ��û�е�����ʽѡ��
		while (1)
		{
			cout << "��ѡ������ʽ��" << " ";
			cin >> SortWay;

			//�����˳�whileѭ���ı��
			bool flag = false;

			//����ѡ������ע����������Ϊְ�����
			for (int i = 0; i < m_Num; i++)
			{
				int MinOrMax=i;          //���ֵ����Сֵ���±꣬��ʼ��Ϊi
				//��i����һ����ʼѡ��
				for (int j = i + 1; j < m_Num; j++)
				{
					//�������У�����Сֵ
					if (SortWay == 1)
					{
						if (m_EmpArry[j]->m_id < m_EmpArry[MinOrMax]->m_id)
						{
							MinOrMax = j;
						}
						flag = true;
					}

					//�������У������ֵ
					if (SortWay == 2)
					{
						if (m_EmpArry[j]->m_id > m_EmpArry[MinOrMax]->m_id)
						{
							MinOrMax = j;
						}
						flag = true;
					}

					//�����˳��ڲ�forѭ��
					else
						break;

				
				}     //ѡ�������ڲ�ѭ������

				if (!flag)
				{
					break;              //ѡ�����ֱ���������forѭ��
				}

				//����ҵ�����ֵ���趨�ĳ�ֵ��һ���򽻻�
				if (i != MinOrMax)
				{
					worker* temp = m_EmpArry[i];
					m_EmpArry[i] = m_EmpArry[MinOrMax];
					m_EmpArry[MinOrMax] = temp;
				}

			}        //ѡ���������ѭ������

			if (!flag)
			{
				cout << "�޴�ѡ�����������" << endl;
				continue;
			}

			else break;

		}      //��ֹѡ�����ѡ���whileѭ������

		cout << "������ɣ����������£�" << endl;
		//�����д���ļ�
		AddToFile();
		ShowEmp();
	}
}


//����ļ�
void WorkerManager::ClearFile()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}

	else
	{
		cout << "ȷ������ļ���" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.ȡ��" << endl;

		int select;
		//��ֹѡ�񲻴��ڵ�ѡ���whileѭ��
		while (1)
		{
			cin >> select;

			if (select == 1)
			{
				//�������ͷ�
				if (m_EmpArry != NULL)
				{
					//��Ԫ������ͷ�
					for (int i = 0; i < m_Num; i++)
					{
						if (m_EmpArry[i] != NULL)
						{
							delete m_EmpArry[i];
							m_EmpArry[i] = NULL;
						}
					}
					//�ͷ�����
					delete[] m_EmpArry;
					m_EmpArry = NULL;
				}

				//��truncģʽ���ļ���������ļ�
				ofstream ofs;
				ofs.open(FileOfEmp, ios::trunc);
				ofs.close();

				ofs.open(FileOfNum, ios::out);
				ofs << "0";
				ofs.close();

				//��������
				m_Num = 0;
				m_FileIsEmpty = true;

				cout << "�ļ�������" << endl;
				break;               //�˳�whileѭ��
			}      //ѡ��ȷ����յ�if����

			else if (select == 2)
			{
				break;             //ȡ��������˳�whileѭ��
			}

			else
			{
				cout << "�޴�ѡ�����������" << endl;
				continue;
			}
		}       //��ֹѡ�����ѡ���whileѭ������

	}

	system("pause");
	system("cls");
}

//289+891=1180�д���