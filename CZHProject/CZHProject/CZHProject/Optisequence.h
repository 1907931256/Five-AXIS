#pragma once
#include "DrawTool.h"
#include "STLModell.h"
#include "KitTool.h"
#include "DrawTool.h"
#include "DlgInterveResult.h"
#include <time.h>
#define  AuxZero  0.000001
//////////�Զ���������ݽṹ////////
typedef struct SUnit
{
	vector<int> Sequence;
	double f1Sum;/////��һĿ�꺯��,��С�ڽ�
	double f2Sum;/////�ڶ�Ŀ�꺯��,��С�ƶ�����
	int  n;////��֧�����
	vector<SUnit*>  S;//֧�伯��
	int level;//////֧��ȼ�
	float distance; /////ӵ������
	double v;/////����Ⱥ�ٶ�
	SUnit()
	{
		f1Sum = 0;
		f2Sum = 0;
		n = 0;
		level = 0;
		distance = 0;
		v = 0;
	};

	bool operator <(const SUnit& v1)const
	{
		if (f1Sum < v1.f1Sum) return true;
		return false;
	};

}SUNIT, *pSUNIT;
//�Զ�����������
typedef struct IntervBlock
{
	vector<vec_POINT3D> ModelDate;
	vector<vec_POINT3D> BoxDate;
	bool status;
	IntervBlock()
	{
		status = false;
	};

}SInterB, *pSInterB;


struct SCompUNIT
{
	bool operator ()(const SUNIT p1, const SUNIT p2)
	{
		if (p1.f1Sum > p2.f1Sum) return true;
		if (p1.f1Sum < p2.f1Sum) return true;
		if (p1.f2Sum > p2.f2Sum) return true;
		if (p1.f2Sum < p2.f2Sum) return true;
		return false;
	}
};
class COptisequence
{
public:
	KitTool Pkit;
	COptisequence();
	 ~COptisequence();
	 vector<SUNIT>  MOPSO(vector<MyBlock> Rbox, vector<VECTOR3D> &All_VecDir,DlgInterveResult &InterveResult, QProgressBar *MyProgressBar);
	 vector<vector<int>> RandomDir(int SZ, vector<MyBlock> Rbox, vector<VECTOR3D> &All_VecDir, DlgInterveResult &InterveResult, QProgressBar *MyProgressBar);//��ʼ��Ⱥ
	 vector<SUNIT> non_inferior(vector<vector<int>> &MyDirS, vector<VECTOR3D> &All_VecDir, vector<MyBlock> Rbox);//��֧��ȼ�����
	 //void IfAcuteAngle(VECTOR3D &Dir, VECTOR3D Diz);//�鿴���ŷ����Ƿ���Z�᷽��Ϊ��ǣ�����ͷ���
	 double TheLestAngle(vector<int> Sqence, vector<VECTOR3D> All_VecDir);//�԰ڶ��Ƕ���СΪĿ����Ż�����
	 double TheLestDistance(vector<int> Sqence, vector<VECTOR3D> All_VecDir, vector<MyBlock> Rbox);//����ͷ�ƶ�������СΪĿ����Ż�����
	 int RC1(vector<int> Sqence, vector<MyBlock> Rbox);//���ڽ�ԭ��ΪĿ����Ż�����
	 int RC2(vector<int> Sqence, vector<MyBlock> Rbox);//������ԭ��ΪĿ����Ż�����
	 void UpdateBlockBox(vector<PFACETTRI> pMeshTri, BOX3D &ONE);
	 void SaveOptiResult(vector<MyBlock> &Rbox, vector<VECTOR3D> &All_VecDir, vector<int> Sequence);//�����Ż����
	 
	 //�����麯��
	 void UpdateBox(vector<MyBlock> Rbox);//���¿�İ�Χ����Ϣ
	 void Creatboarddate(vector<vec_POINT3D> &vec_face, POINT3D pcenter);//����ƽ̨����Ƭ����
	 POINT3D CalCenterPoint(MyBlock CurrnetBlock,VECTOR3D DirV);//���㵱ǰ�����ײ����ĵ�
	 void CreatHeadboxdate(vector<vec_POINT3D> &vec_face, POINT3D Pcenter,VECTOR3D DirV);//������ͷ�����Χ������
	 void JoinCurrentBlock(vector<SInterB>&AllModelInfor, MyBlock CurrnetBlock);//����ǰ����Ƭ��Ϣ��������Ƭ��
	 void RotateHeadBox(vector<vec_POINT3D> &vec_face, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת��ӡͷ��Χ��

	 void RotateBlock(MyBlock &OneBlock, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת�ָ��
	 void RotateDir(vector<VECTOR3D> &Vec_Dir, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת���ų��ͷ���
	 bool JudetheInsert(vec_POINT3D Pfac1, vec_POINT3D Pfac2,POINT3D pCenter,VECTOR3D Dir);//�ж�������Ƭ���޽���
	 bool GetIntereResult(vector<SInterB> &AllModelInfor, MyBlock CurrnetBlock, vector<vec_POINT3D> vec_Head, POINT3D pCenter, VECTOR3D Dir,int &InteBlock);//��ȡ������
	 
	 void DrawResult(vector<MyBlock> Rbox, vector<VECTOR3D> All_VecDir, drawTool *pDC, double len);

	 bool GettheBlockpath(vec_PPOLYPOLYGON &OnelRotateBlock, POINT3D Plow, MATRIX3D TM);
	 void CalRotateMaix(VECTOR3D &Dir_now, MATRIX3D &TM);
	 void TranRbox(vector<MyBlock> &Rbox,POINT3D plow);//ƽ�ƿ�ָ�ģ��
	 void TranRbox(vector<vec_PPOLYPOLYGON> &BlockFill, POINT3D plow);//ƽ�ƿ������
};

