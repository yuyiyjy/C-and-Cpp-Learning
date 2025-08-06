#pragma once
//�Զ���ͷ�ļ� ����ʵ����ʾ�˵�����ְ��������ɾ�Ĳ�Ȳ������Լ������ļ�
#include<iostream>
#include "worker.h"
#include<fstream>

//�����ļ��곣��
//���ڱ���ְ����Ϣ
#define FileOfEmp "EmpFile.txt"
//���ڱ����Ѵ����ְ������
#define FileOfNum "NumFile.txt"

//�Զ���ͷ�ļ� ����ʵ����ʾ�˵�����ְ��������ɾ�Ĳ�Ȳ������Լ������ļ�

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//��������
	~WorkerManager();

	//��ʾ�˵�
	void ShowMenu();

	//�˳�ϵͳ
	void ExitSystem();

	//����ְ����Ϣ
	void AddEmp();

	//��ʾ����ְ����Ϣ
	void ShowEmp();

	//�ж�ְ���Ƿ���ڣ�������ڷ������������е�λ�ã��������򷵻�-1
	int IsExit(int id);

	//ɾ��ְ��
	void DeleteEmp();

	//�޸�ְ����Ϣ
	void ModifyEmp();

	//����ְ��
	void SearchEmp();

	//����ְ����Ž�������
	void SortEmp();

	//����ļ�
	void ClearFile();

	//��ְ����Ϣ������ļ���
	void AddToFile();

	//��ʼ��ְ������
	void InitEmpArry();

	//��ְ������д���ļ�
	void NumToFile(int num);

	//��ȡ�ļ����Ѵ����ְ������
	int GetEmpNum();

	//����ӵ�Ա��������Ա������
	int m_Num;
	worker** m_EmpArry;
	//�ļ��Ƿ�Ϊ�յı�־
	bool m_FileIsEmpty;
};
