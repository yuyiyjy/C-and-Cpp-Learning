#include "WorkerManager.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"
using namespace std;

//构造函数
WorkerManager::WorkerManager()
{
	//在构造函数中将属性初始化
	
	//情况一：文件不存在
		ifstream ifs;
		ifs.open(FileOfEmp, ios::in);
		if (!ifs.is_open())
		{
			//文件为空
			//cout << "文件不存在" << endl;
			m_Num = 0;
			m_EmpArry = NULL;
			m_FileIsEmpty = true;
			return;
		}

	//情况二：文件存在但为空
		else if (ifs.is_open())
		{
			char ch;
			ifs >> ch;
			if (ifs.eof())
			{
				//cout << "文件为空" << endl;
				m_Num = 0;
				m_EmpArry = NULL;
				m_FileIsEmpty = true;
				return;
			}
		}

	//情况三：文件存在且不为空
		m_Num = GetEmpNum();
		m_FileIsEmpty = false;
		m_EmpArry = new worker * [m_Num];
		//初始化职工数组
		InitEmpArry();
}

//析构函数
WorkerManager::~WorkerManager()
{
	//释放掉职工数组
	if (m_EmpArry != NULL)
	{
		for (int i = 0; i < m_Num; i++)
			delete m_EmpArry[i];

		delete[] m_EmpArry;
	}
}

//打印菜单
void WorkerManager::ShowMenu()
{
	cout << "************************欢迎使用职工管理系统************************" << endl;
	cout << "************************1.退出管理程序************************" << endl;
	cout << "************************2.增加职工信息************************" << endl;
	cout << "************************3.显示职工信息************************" << endl;
	cout << "************************4.删除离职职工************************" << endl;
	cout << "************************5.修改职工信息************************" << endl;
	cout << "************************6.查找职工信息************************" << endl;
	cout << "************************7.按照编号排序************************" << endl;
	cout << "************************8.清空所有文档************************" << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}

//将职工数量加入文件中
void WorkerManager::NumToFile(int num)
{
	//创建文件
	ofstream ofs;
	ofs.open(FileOfNum, ios::out);
	ofs << num;
	ofs.close();
}

//从文件中获取职工数量
int WorkerManager::GetEmpNum()
{
	//从文件中读取数据
	ifstream ifs;
	ifs.open(FileOfNum, ios::in);
    string Num;
	getline(ifs,Num);
	ifs.close();

	int GetNum;
	//将字符串转为整型数据
	try
	{
		GetNum = stoi(Num);
	}
	catch (const invalid_argument& e) {
		std::cout << "非法输入" << std::endl;
	}
	catch (const out_of_range& e) {
		std::cout << "数值超出范围" << std::endl;
	}

	return GetNum;
}

//初始化职工数组
void WorkerManager::InitEmpArry()
{
	//读文件
	ifstream ifs;
	ifs.open(FileOfEmp, ios:: in);
    
	//读取内容
	int id;
	string name;
	int DepId;
	//索引
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> DepId)
	{
		worker* NewWorker = NULL;
		switch (DepId)
		{
		case 1:               //普通员工
			NewWorker = new employee(id, name, DepId);
			break;
		case 2:              //经理
			NewWorker = new manager(id, name, DepId);
			break;
		case 3:             //老板
			NewWorker = new boss(id, name, DepId);
			break;
		}

		//存入数组中
		m_EmpArry[index] = NewWorker;
		index++;
	}

	ifs.close();
}

//将职工信息加入文件中
void WorkerManager::AddToFile()
{
	ofstream ofs;
	ofs.open(FileOfEmp, ios::out);

	//将数组中的信息逐个写入文件
	for (int i = 0; i < m_Num; i++)
	{
		ofs << m_EmpArry[i]->m_id << " "
			<< m_EmpArry[i]->m_name << " "
			<< m_EmpArry[i]->m_depId << endl;
	}

	ofs.close();
}

//判断职工是否存在
int WorkerManager::IsExit(int id)
{
	int index = -1;

	for (int i = 0; i < m_Num; i++)
	{
		//找到该职工
		if (m_EmpArry[i]->m_id == id)
		{
			index = i;
			break;
		}
	}

	return index;
}

//增加员工
void WorkerManager::AddEmp()
{
	//询问添加员工的数量
	int AddNum;
	//大的while循环
	while (1)
	{
		cout << "请问您要添加几名新职工：" << " ";
		cin >> AddNum;
		//判断输入的合理性
		if (AddNum > 0)
		{
			//记录新空间的大小并开辟新空间
			int NewSize = m_Num + AddNum;
			worker** NewSpace = new worker * [NewSize];


			//判断原数组是否为空，不为空则需要将原数组中的元素拷贝到新数组中，并释放原数组
			if (m_EmpArry != NULL)
			{
				for (int i = 0; i < m_Num; i++)
				{
					NewSpace[i] = m_EmpArry[i];
				}
			}

			//输入新添加的员工的信息
			for (int j = 0; j < AddNum; j++)
			{
				int NewId;
				string NewName;
				int NewDepId;

				//输入编号时要防止编号重复,既要检查原数组也要检查新加入的元素
				while (1) 
				{
					cout << "请输入第" << j + 1 << "名新职工的编号：" << " ";
					cin >> NewId;

					//用于标记是否重复
					bool IsDuplicate = false;
                    
					//检查原数组
					if (m_EmpArry != NULL)
					{
						for (int i = 0; i < m_Num; i++)
						{
							if (m_EmpArry[i]->m_id == NewId)
							{
								IsDuplicate = true;
								break;              //结束for检查原数组的for循环
							}
						}
					}

					//检查新加入的元素
					for (int i = 0; i < j; i++)
					{
						if (NewSpace[m_Num + i]->m_id == NewId)
						{
							IsDuplicate = true;
							break;                   //结束检查新加入元素的for循环
						}
					}

					if (IsDuplicate)
					{
						cout << "已存在该编号，请换一个编号" << endl;
						continue;
					}

					else break;          //否则跳出循环

				}   //防止编号重复的while循环出口

				cout << "请输入第" << j + 1 << "名新职工的姓名：" << " ";
				cin >> NewName;

				worker* NewWorker = NULL;
				while (1)
				{
					cout << "请选择第" << j + 1 << "名新职工的部门：" << endl;
					cout << "1.普通职工" << endl;
					cout << "2.经理" << endl;
					cout << "3.老板" << endl;
					cin >> NewDepId;

					//根据新职工的类型创建不同的对象
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
						cout << "输入有误，请重新输入！" << endl;
						continue;                                        //如果输入有误则进入下一次while循环
					}

					//跳出小while循环
					if (NewWorker != NULL)
						break;
				}         //防止选择部门输入有误的while循环出口

				//将新职工添加到数组
				NewSpace[m_Num + j] = NewWorker;

			}  //对每一位新职工处理的for循环出口

			//更新数据
			m_Num = NewSize;
			m_EmpArry = NewSpace;
			m_FileIsEmpty = false;
			
			//结束大while循环
			cout << "成功添加" << AddNum << "名新职工" << endl;
			//写入文件
			AddToFile();
			NumToFile(m_Num);
			break;

		} //添加数量合理性的if出口

		//如果输入不合理重新进入循环输入
		else
		{
			cout << "输入有误，请重新输入！" << endl;
			continue;
		}
	}  //大while循环的出口

	//进行清屏操作
	system("pause");
	system("cls");
}

//显示所有职工信息
void WorkerManager::ShowEmp()
{
	//文件不存在或者为空
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或者文件为空" << endl;
		system("pause");
		system("cls");
		return;
	}

	else
	{
		//利用多态逐个显示职工信息
		for (int i = 0; i < m_Num; i++)
			m_EmpArry[i]->ShowInfo();
	}

	//按下任意键后清屏
	system("pause");
	system("cls");
}

void WorkerManager::DeleteEmp()
{
	//如果文件不存在或者文件为空
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		system("cls");
		return;
	}

	//利用多态逐个显示职工信息
	for (int i = 0; i < m_Num; i++)
		m_EmpArry[i]->ShowInfo();

	int DelIndex;
	cout << "请问您要删除的职工编号为：" << " ";
	cin >> DelIndex;

	//调用函数
	int index = IsExit(DelIndex);
	
	//如果找到了需要删除的职工
	if (index != -1)
	{
		//对数组进行一个前移操作
		for (int i = index; i < m_Num - 1; i++)
		{
			m_EmpArry[i] = m_EmpArry[i + 1];
		}

		//前移完毕后修改数据
		m_Num--;
		//将新数组的数据写入文件
		AddToFile();
		//将新的职工数量写入文件
		NumToFile(m_Num);

		cout << "删除成功" << endl;
	}

	else
	{
		cout << "删除失败，未找到该职工" << endl;
	}

	//按下任意键后清屏
	system("pause");
	system("cls");
}

//修改职工信息
void WorkerManager::ModifyEmp()
{
	//文件不存在或者文件为空时
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		system("cls");
		return;
	}

	//利用多态逐个显示职工信息
	for (int i = 0; i < m_Num; i++)
		m_EmpArry[i]->ShowInfo();

	int ModId;
	cout << "请问您要修改的职工的编号为：" << " ";
	cin >> ModId;

	int index = IsExit(ModId);

	//如果找到该职工
	if (index != -1)
	{
		//先将原来的信息进行删除，但删除前需要保存旧编号
		int OldId = m_EmpArry[index]->m_id;
		delete m_EmpArry[index];

		//输入新添加的员工的信息
		int NewId;
		string NewName;
		int NewDepId;

		//输入编号时要防止编号重复,只用检查原数组中除此编号以外的编号
		while (1)
		{
			cout << "请输入该名职工的新编号：" << " ";
			cin >> NewId;

			//用于标记是否重复
			bool IsDuplicate = false;

			//检查原数组
				for (int i = 0; i < m_Num; i++)
				{
					//修改的新编号可以和旧编号一样，所以当新编号与旧编号一样时直接跳出for循环，无需逐个比较
					if (NewId == OldId)
						break;

					if (m_EmpArry[i]->m_id == NewId)
					{
						IsDuplicate = true;
						break;              //结束for检查原数组的for循环
					}
				}
            
			//如果有重复
			if (IsDuplicate)
			{
				cout << "已存在该编号，请换一个编号" << endl;
				continue;
			}

			else break;          //否则跳出循环

		}   //防止编号重复的while循环出口

		cout << "请输入该名职工的新姓名：" << " ";
		cin >> NewName;

		worker* NewWorker = NULL;
		while (1)
		{
			cout << "请选择该名职工的新部门：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> NewDepId;

			//根据新职工的类型创建不同的对象
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
				cout << "输入有误，请重新输入！" << endl;
				continue;                                        //如果输入有误则进入下一次while循环
			}

			//跳出小while循环
			if (NewWorker != NULL)
				break;
		}         //防止选择部门输入有误的while循环出口

		//将新职工添加到数组
		m_EmpArry[index] = NewWorker;

		//将新的信息写入文件中
		AddToFile();

		cout << "修改成功" << endl;

	}  //找到职工的if语句出口

	else
	{
		cout << "修改失败，查无此人" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::SearchEmp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
	}

	//文件有内容
	else
	{
		cout << "1.按职工编号查" << endl;
		cout << "2.按职工姓名查" << endl;
		cout << "3.按职工岗位查" << endl;
		int SearchWay;

		//防止选择不合理的while循环
		while (1)
		{
			cout << "请选择查找方式：" << " ";
			cin >> SearchWay;
			//按编号查
			if (SearchWay == 1)
			{
				cout << "请输入您要查找的职工的编号：" << " ";
				int SearchId;
				cin >> SearchId;

				int index = IsExit(SearchId);

				//如果存在该职工
				if (index != -1)
				{
					cout << "该职工的信息如下：" << endl;
					m_EmpArry[index]->ShowInfo();
				}

				else
				{
					cout << "无职工的编号为" << SearchId << endl;
				}

				break;          //退出防止查找方式选择不合理的while循环
			}

			//按姓名查，可能有重名
			if (SearchWay == 2)
			{
				//用于标记是否找到
				bool Find1 = false;

				string SearchName;
				cout << "请输入您要查找的职工的姓名：" << " ";
				cin >> SearchName;

				//逐个检查
				for (int i = 0; i < m_Num; i++)
				{
					//找到姓名符合的职工
					if (m_EmpArry[i]->m_name == SearchName)
					{
						cout << "编号为" << m_EmpArry[i]->m_id << "的" << m_EmpArry[i]->m_name << "的信息如下：" << endl;
						m_EmpArry[i]->ShowInfo();
						//标记为找到
						Find1 = true;
						break;             //跳出for循环
					}

				}  //逐个检查的for循环

				//如果检查完还没有找到
				if (!Find1)
				{
					cout << "没有姓名为" << SearchName << "的职工" << endl;
				}

				break;                //退出防止查找方式不合理的while循环
			}

			//按岗位查
			if (SearchWay == 3)
			{
				cout << "1.普通员工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;

				while (1)
				{
					int Dep;
					cout << "请选择您要查找的岗位：" << " ";
					cin >> Dep;

					//选择普通员工
					if (Dep == 1)
					{
						//用于标记是否查找到
						bool Find2 = false;

						//逐个检查
						for (int i = 0; i < m_Num; i++)
						{
							//找到岗位符合的职工
							if (m_EmpArry[i]->m_depId == 1)
							{
								cout << "编号为" << m_EmpArry[i]->m_id << "的" << m_EmpArry[i]->m_name << "的信息如下：" << endl;
								m_EmpArry[i]->ShowInfo();
								//标记为找到
								Find2 = true;
							}
						}  //逐个检查的for循环

						//如果检查完还没有找到
						if (!Find2)
						{
							cout << "没有岗位为普通员工的职工" << endl;
						}

						break;                //退出while循环
					}

					//岗位为经理
					if (Dep == 2)
					{
						//用于标记是否查找到
						bool Find3 = false;

						//逐个检查
						for (int i = 0; i < m_Num; i++)
						{
							//找到岗位符合的职工
							if (m_EmpArry[i]->m_depId == 2)
							{
								cout << "编号为" << m_EmpArry[i]->m_id << "的" << m_EmpArry[i]->m_name << "的信息如下：" << endl;
								m_EmpArry[i]->ShowInfo();
								//标记为找到
								Find3 = true;
							}
						}  //逐个检查的for循环

						//如果检查完还没有找到
						if (!Find3)
						{
							cout << "没有岗位为经理的职工" << endl;
						}

						break;                //退出while循环
					}

					if (Dep == 3)
					{
						//用于标记是否查找到
						bool Find4 = false;

						//逐个检查
						for (int i = 0; i < m_Num; i++)
						{
							//找到岗位符合的职工
							if (m_EmpArry[i]->m_depId == 3)
							{
								cout << "编号为" << m_EmpArry[i]->m_id << "的" << m_EmpArry[i]->m_name << "的信息如下：" << endl;
								m_EmpArry[i]->ShowInfo();
								//标记为找到
								Find4 = true;
							}
						}  //逐个检查的for循环

						//如果检查完还没有找到
						if (!Find4)
						{
							cout << "没有岗位为经理的职工" << endl;
						}

						break;                //退出while循环
					}

					else
					{
						cout << "无此岗位选择项，请重新输入" << endl;
						continue;
					}
				}      //防止岗位选择不合理的while循环

				break;             //跳出防止查找方式选择不合理的while循环出口
			}      //按岗位查if出口

			else
			{
				cout << "无此查找方式选项，请重新输入" << endl;
				continue;
			}
		}   //防止查找方式选择不合理的while循环出口

	}

	system("pause");
	system("cls");

}

//根据职工编号进行排序
void WorkerManager::SortEmp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		system("cls");
	}

	else
	{
		cout << "1.按照职工编号升序排列" << endl;
		cout << "2.按照职工编号降序排列" << endl;

		int SortWay;
		//防止选择没有的排序方式选项
		while (1)
		{
			cout << "请选择排序方式：" << " ";
			cin >> SortWay;

			//用于退出while循环的标记
			bool flag = false;

			//进行选择排序，注意排序依据为职工编号
			for (int i = 0; i < m_Num; i++)
			{
				int MinOrMax=i;          //最大值或最小值的下标，初始化为i
				//从i的下一个开始选择
				for (int j = i + 1; j < m_Num; j++)
				{
					//升序排列，找最小值
					if (SortWay == 1)
					{
						if (m_EmpArry[j]->m_id < m_EmpArry[MinOrMax]->m_id)
						{
							MinOrMax = j;
						}
						flag = true;
					}

					//降序排列，找最大值
					if (SortWay == 2)
					{
						if (m_EmpArry[j]->m_id > m_EmpArry[MinOrMax]->m_id)
						{
							MinOrMax = j;
						}
						flag = true;
					}

					//否则退出内层for循环
					else
						break;

				
				}     //选择排序内层循环出口

				if (!flag)
				{
					break;              //选择错误，直接跳出外层for循环
				}

				//如果找到的最值和设定的初值不一致则交换
				if (i != MinOrMax)
				{
					worker* temp = m_EmpArry[i];
					m_EmpArry[i] = m_EmpArry[MinOrMax];
					m_EmpArry[MinOrMax] = temp;
				}

			}        //选择排序外层循环出口

			if (!flag)
			{
				cout << "无此选项，请重新输入" << endl;
				continue;
			}

			else break;

		}      //防止选择错误选项的while循环出口

		cout << "排序完成，排序结果如下：" << endl;
		//将结果写入文件
		AddToFile();
		ShowEmp();
	}
}


//清空文件
void WorkerManager::ClearFile()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
	}

	else
	{
		cout << "确定清空文件？" << endl;
		cout << "1.确定" << endl;
		cout << "2.取消" << endl;

		int select;
		//防止选择不存在的选项的while循环
		while (1)
		{
			cin >> select;

			if (select == 1)
			{
				//将数组释放
				if (m_EmpArry != NULL)
				{
					//将元素逐个释放
					for (int i = 0; i < m_Num; i++)
					{
						if (m_EmpArry[i] != NULL)
						{
							delete m_EmpArry[i];
							m_EmpArry[i] = NULL;
						}
					}
					//释放数组
					delete[] m_EmpArry;
					m_EmpArry = NULL;
				}

				//用trunc模式打开文件即可清空文件
				ofstream ofs;
				ofs.open(FileOfEmp, ios::trunc);
				ofs.close();

				ofs.open(FileOfNum, ios::out);
				ofs << "0";
				ofs.close();

				//更新数据
				m_Num = 0;
				m_FileIsEmpty = true;

				cout << "文件清除完毕" << endl;
				break;               //退出while循环
			}      //选择确定清空的if出口

			else if (select == 2)
			{
				break;             //取消清除则退出while循环
			}

			else
			{
				cout << "无此选项，请重新输入" << endl;
				continue;
			}
		}       //防止选择错误选项的while循环出口

	}

	system("pause");
	system("cls");
}

//289+891=1180行代码