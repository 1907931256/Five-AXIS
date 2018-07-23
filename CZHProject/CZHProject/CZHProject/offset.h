#pragma once
#include"KitTool.h"
#include "datastructure/polygon.h"
#include "STLModell.h"
typedef struct lineIntersect
{
	POINT3D p;
	int   line1Num;
	int   line2Num;
	bool  ifInto;
	bool  beused;

}LineInterS,*pLineInterS;

class Coffset
{
public:
	Coffset(void);
	~Coffset(void);
public:
	
public:
	static void GetOffset(vec_PPOLYPOLYGON	m_vecPPolyPolygons, VECTOR3D m_VecDir, vec_PPOLYPOLYGON & m_vecFillP, double FillLineWidth);
	static void GetOffset(vec_PPOLYPOLYGON	m_vecPPolyPolygons, VECTOR3D m_VecDir, vec_PPOLYPOLYGON & m_vecFillP, double FillLineWidth, int degree
						,vec_PPOLYPOLYGON &vec_lastoffset);///////���ڻ������ƫ��
	static void pretreatment(vec_PPOLYPOLYGON m_vecPPolyPolygons);///////Ԥ��������ֲ���������֮��Ĺ�ϵ
	
	static void ifdeleOffset(int &m,PPOLYPOLYGON afteroffset,double FillLineWidth);
	
	static int selfing(PPOLYGON beoffsetpoly,  PPOLYGON poly,PPOLYPOLYGON  pPolyPoly);////ȥ�Խ�
	static int incise (PPOLYPOLYGON afteroffset,PPOLYPOLYGON ploy,int & originalNum);//�����໥����
	static bool IfIncise(PPOLYGON ploy1,PPOLYGON ploy2,PPOLYPOLYGON  Newpolypoly,bool ifOutCutOut);//2������֮����໥����
	
	static PPOLYGON  offsetpiont(double d,PPOLYGON poly);//�󵥸����ߵ�ƫ�����ߺ���

	static bool  ifstop(PPOLYPOLYGON ploy,double d);//�ж��Ƿ�ֹͣ����
	static void offsetSort(PPOLYPOLYGON ployploy);//�����С���󣬲���ÿ����������
	static void offsetClassify(int &m ,int n,POLYGON beoffsetpoly,PPOLYPOLYGON ployploy,double threshold);//��ƫ�����߽��з���
	static void FlattenPoly(PPOLYGON poly1,PPOLYGON poly2,vector<LineInterS> vec_lineInter,PPOLYPOLYGON Newpolypoly);//����ƴ��
	static void ifPopBack(POINT3D p1,PPOLYGON poly1);//�Ƿ�ɾ�����һ��
	static void ExtractPoint(int Num1,int Num2,PPOLYGON poly1,PPOLYGON poly);//��ȡ��
	
	static void OffsetCircle(double degree, VECTOR3D vec_Dir, PPOLYGON ploy, PPOLYPOLYGON vec_poly);//�ҵĻ�ƫ��
	static void  OffsetCircle1(double FillLineWidth, VECTOR3D vec_Dir, PPOLYGON ploy, PPOLYPOLYGON &m_vecFillP);//֣���
	static void GetOffset1(vec_PPOLYPOLYGON	m_vecPPolyPolygons, VECTOR3D m_VecDir, vec_PPOLYPOLYGON & m_vecFillP, double FillLineWidth);
};
