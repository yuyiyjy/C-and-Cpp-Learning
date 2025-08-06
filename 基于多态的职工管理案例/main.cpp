#include "WorkerManager.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

int main()
{
	//创建一个管理对象
	WorkerManager wm;
	//打印菜单

	int choice;

	while (1)
	{
		wm.ShowMenu();
		cout << "请输入您的选择：" << " ";
		cin >> choice;

		switch (choice)
		{
		case 1:                   //退出系统
			wm.ExitSystem();
			break;
		case 2:                   //增加新职工
			wm.AddEmp();
			break;
		case 3:                  //显示所有职工信息
			wm.ShowEmp();
			break;
		case 4:                 //删除职工
			wm.DeleteEmp();
			break;
		case 5:                 //修改职工信息
			wm.ModifyEmp();
			break;
		case 6:                 //查找职工
			wm.SearchEmp();
			break;
		case 7:                //根据职工编号进行排序
			wm.SortEmp();
			break;
		case 8:                //清空文件
			wm.ClearFile();
			break;
		default:
			{
				cout << "输入有误，请重新输入！" << endl;
				system("pause");
				system("cls");
				break;
			}
		}

	}

	return 0;
}

