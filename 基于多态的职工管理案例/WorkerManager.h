#pragma once
//自定义头文件 用来实现显示菜单、对职工进行增删改查等操作、以及管理文件
#include<iostream>
#include "worker.h"
#include<fstream>

//定义文件宏常量
//用于保存职工信息
#define FileOfEmp "EmpFile.txt"
//用于保存已存入的职工数量
#define FileOfNum "NumFile.txt"

//自定义头文件 用来实现显示菜单、对职工进行增删改查等操作、以及管理文件

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//析构函数
	~WorkerManager();

	//显示菜单
	void ShowMenu();

	//退出系统
	void ExitSystem();

	//增加职工信息
	void AddEmp();

	//显示所有职工信息
	void ShowEmp();

	//判断职工是否存在，如果存在返回其在数组中的位置，不存在则返回-1
	int IsExit(int id);

	//删除职工
	void DeleteEmp();

	//修改职工信息
	void ModifyEmp();

	//查找职工
	void SearchEmp();

	//根据职工编号进行排序
	void SortEmp();

	//清空文件
	void ClearFile();

	//将职工信息保存进文件中
	void AddToFile();

	//初始化职工数组
	void InitEmpArry();

	//将职工数量写入文件
	void NumToFile(int num);

	//获取文件中已存入的职工数量
	int GetEmpNum();

	//已添加的员工数量和员工数组
	int m_Num;
	worker** m_EmpArry;
	//文件是否为空的标志
	bool m_FileIsEmpty;
};
