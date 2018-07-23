#pragma once
#include "DrawTool.h"
#include "STLModell.h"
#include "KitTool.h"
//////�Զ������ݽṹ���ڱ������ŷ���
typedef struct i2Sum
{
	int i;
	double sum;
	bool operator <(const i2Sum& v1)const
	{
		if (sum<v1.sum) return true;
		return false;
	};
};


//////////�Զ���������ݽṹ////////
typedef struct Unit
{
	VECTOR2D  Dir;////����
	double f1Sum;/////��һĿ�꺯��
	double f2Sum;/////�ڶ�Ŀ�꺯��
	int  n ;////��֧�����
	vector<Unit*>  S;//֧�伯��
	int level;//////֧��ȼ�
	float distance; /////ӵ������
	double v;/////����Ⱥ�ٶ�
	Unit()
	{
		f1Sum=0;
		f2Sum=0;
		n=0;
		level =0;
	    distance =0;
		v=0;
	};

	bool operator <(const Unit& v1)const
	{
		if (f1Sum<v1.f1Sum) return true;
		return false;
	};

}UNIT,*pUNIT;

struct CompUNIT
{
	bool operator ()(const UNIT p1, const UNIT p2)
	{
		if (p1.f1Sum > p2.f1Sum) return true;
		if (p1.f1Sum < p2.f1Sum) return true;
		if (p1.f2Sum > p2.f2Sum) return true;
		if (p1.f2Sum < p2.f2Sum) return true;
		return false;
	}
};



class COptDir   
{
public:
	COptDir();
    ~COptDir();
public:
	vector<vector<int>> 	m_vecPFacetTri;
public:
	//////////////////////////��ʾ����////////////////
	void  VisualResult(vec_PVECTOR3D m_vecPFacetNorm, VECTOR3D  DirV);
	static void DrawResult(vec_PFACETTRI m_vecBlockFacet, vector<vector<int>> m_vecPFacetTri, drawTool *pDC);//�������ӿ������ų��ͷ����ϵ�֧�����
	static void  DrawResult(STLModell* pSTLModel, vector<vector<int>> 	m_vecPFacetTri, drawTool *pDC);
	static void  DrawInfo(drawTool *pDC);//�����
	static void  DrawOptiDir(drawTool *pDC, VECTOR3D m_VecDir, BOX3D ONE,double len);//�������ų��ͷ���

	//////////////////////�����Ŵ��㷨(GA) ��Ŀ��/////////
	double SA(vec_PVECTOR3D m_vecPFacetNorm,VECTOR2D  DirV,vector<double>vec_Area);
	VECTOR2D GA(STLModell *pSTL);
	vec_VECTOR2D RandomDir(int SZ);
	vector<int> GA_selectDir(vec_VECTOR2D AllDir,vector<double> AllSum);
	vec_VECTOR2D GA_Crossover(VECTOR2D v1,VECTOR2D v2);
	VECTOR2D GA_Mutation();
	//double GetTriArea(PFACETTRI ptri);
	
	////////////////////����Ӣ���Եķ�֧�������Ŵ��㷨(NSGA_II)//////
	vector<UNIT> NSGA_ii(STLModell *pSTL);
	double SE(vec_PVECTOR3D m_vecPFacetNorm,VECTOR2D  DirV,vector<double>vec_Area);
	vector<vector<UNIT>> non_dominatedSet(vec_VECTOR2D MyDirS,vec_PVECTOR3D m_vecPFacetNorm,vector<double>vec_Area);//////���ڷ�֧������
	void Distance(vector<UNIT> &vec_dominated);//////����ӵ������ Ŀ�꺯�����ӱ���ı�
	vector<UNIT> TournamentSelection(vector<vector<UNIT>> vec_MyDominated,int SZ);////������ѡ��
	vector<vector<UNIT>>  NSGA_ii_Sort(vector<vector<UNIT>> vec_MyDominated,int SZ);//////����Ϊ�´�ѭ��
	///////////////////��Ŀ������Ⱥ�㷨(MOPSO)/////////////////////////////
	vector<UNIT> MOPSO(STLModell *pSTL, QProgressBar *MyProgressBar);
	vector<UNIT>  MOPSO(vec_PFACETTRI m_vecPFacetTri, QProgressBar *MyProgressBar);
	vec_VECTOR2D MOPSO_upDate(VECTOR2D   gBest,vec_VECTOR2D ALLDir,vec_VECTOR2D  vec_Velocity,
								double &v1max,double & v2max,vec_VECTOR2D &vec_pBest);
	VECTOR2D    MOPSO_Select_gbest(vec_VECTOR2D ALLDir,vector<UNIT> Bestnums,vector<UNIT>  &ElitePopulation,
								vec_PVECTOR3D m_vecPFacetNorm,vector<double>vec_Area);
	void     MOPSO_UpdatePbest(vec_PVECTOR3D m_vecPFacetNorm,vec_VECTOR2D AllDir,vector<double>vec_Area,vec_VECTOR2D &vec_pBest);
	vector<UNIT> non_inferior(vec_VECTOR2D MyDirS,vec_PVECTOR3D m_vecPFacetNorm,vector<double>vec_Area);
};



class CGlobal
{

public:
	CGlobal(void);
	~CGlobal(void);
public:
	static 	int  m_myCtrlSet;
};

