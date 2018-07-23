#pragma once
#include <iostream>
using namespace std;
class MyQueue
{
public:
	MyQueue(int queueCapacity);
	virtual ~MyQueue();
	void ClearQueue();//��ն���
	bool QueueEmpty()const;//�пն���
	bool QueueFull()const;
	int QueueLength() const;//���г���
	bool EnQueue(int element);//��Ԫ�����
	bool DeQueue(int &element);//��Ԫ�س���
	void QueueTraverse();//��������

	////////���ζ��еı�����
private:
	int* m_pQueue;//��������ָ��
	int m_iQueueLen;//����Ԫ�ظ���
	int m_iQueueCapacity;//������������
	int m_iHead;//��ͷ
	int m_iTail;//��β
};

