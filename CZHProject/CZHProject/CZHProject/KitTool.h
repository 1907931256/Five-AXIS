#pragma once
#include "STLModell.h"
#include "datastructure/mesh.h"
#include "datastructure/GeomBase.h"
#include "datastructure/solidMesh.h"
#include "datastructure/solidPolygon.h"
#include "K-d tree/Vec.h"
#include <queue>  
#include<iostream>  
#include<queue>  
#include<stdlib.h>  
using namespace std;
class KitTool
{
public:
	KitTool();
	virtual ~KitTool();

public:

	//////////////////����������///////////////////////
	 static void Ranktwodigit(double &d1, double &d2);//�Ƚ��������Ĵ�С
	 static void Rankthreedigit(PFACETTRI &PFc0, double d0, double d1, double d2);//�Ƚ��������Ĵ�С
	 static void Rankthreedigit(PFACETTRI &PFc0, vector<double> re,double &value);//�Ƚ��������Ĵ�С,������һ����Сֵ
	 void Ranktwopoint(PHEDGE &PHEdge_1, PHEDGE &PHEdge_2);
	 void Ranktwoedge(PHEDGE &PHEdge_0, PHEDGE PHEdge_1, PHEDGE PHEdge_2);
	 static bool RankPfact(PFACETTRI Pfact_0, PFACETTRI Pfact_1);//ȷ���������
	 static bool RankPfact1(PFACETTRI Pfact_0, PFACETTRI Pfact_1);//ȷ���������(�����۵�����С����)
	 static void Thelest(PFACETTRI Pfact_0, float &Zmin);
	 static void RankAllfact(STLModell* pMeshTri, vector<PFACETTRI> &vec_fac); //���������������СZֵ��С����
	 static void RankAlledge(vector<PEDGE> &vec_edg);//�Ա߱��������
	 static bool RankPedge(PEDGE edge_0,PEDGE edge_1);//ȷ���������
	 static bool Comparepoint(PFACETTRI Pfact_0, POINT3D p0);//�Ƚ����������Ƿ����
	 static void  RankCircle(PPOLYGON &ploy);

	 static void closedBoundary(vec_PHEDGE m_vecPHEdge, PPOLYPOLYGON polypoly);//�԰�ߵĶ����������
	 /////////////////����ƽ����������Ƭ�Ľ��㺯��////////////////////
	 static bool CalPlanePointIntPoint(POINT3D p00, POINT3D p10, float Zt, POINT3D &p);//ˮƽ����������Ƭ�Ľ���
	 static bool CalPlaneLineIntersectPoint(POINT3D linePoint, POINT3D linePointend, float Zt, POINT3D &p);
	 static bool CalPlaneLineIntPoint(POINT3D p00, POINT3D p10, POINT3D plane_point, VECTOR3D dir, POINT3D &p, int &vertType);//����ƽ����������Ƭ�Ľ���
	 static bool CalPlaneLineIntPoint(POINT3D p00, POINT3D p10, POINT3D plane_point, VECTOR3D dir, POINT3D &p);//����ƽ����������Ƭ�Ľ���
	 static VECTOR3D PlanePointDistance(POINT3D p0, POINT3D p1, VECTOR3D u); ///�㵽ƽ��ľ��뺯��
	 static double  PlanePointDistance(POINT3D p0, double a, double b, double c, double d)//�㵽ƽ��ľ���
	 {
		 return fabs(a*p0.x + b*p0.y + c*p0.z + d) / sqrt(a*a + b*b + c*c);

	 };
	 //////////////������Ƭ���ܳ������/////////
	 static void Gettriperimeter(PHEDGE ph0, double &cir);//��֪һ�߼��������ε��ܳ�
	 static double AreaTri(PPOINT3D pPoint1, PPOINT3D pPoint2, PPOINT3D pPoint3);//������Ƭ�����
	 static double AreaTri(POINT3D pPoint1, POINT3D pPoint2, POINT3D pPoint3);//������Ƭ�����
	 static double AreaTri(PVERT pPoint1, PVERT pPoint2, POINT3D pPoint3);//������Ƭ�����
	 static double AreaTri(PVERT pPoint1, POINT3D pPoint2, POINT3D pPoint3);//������Ƭ�����
	 static double GetTriArea(PFACETTRI ptri);/////////////////���������Ƭ�����
	 /////////������Ƭ����Ϳռ��֮���ת������/////////////
	 static POINT3D PVERTtoPOINT3D(PVERT pv);
	 static void POINT3DtoPVERT(POINT3D p, PVERT pv);

	 static double CalGaussCurvature(PVERT pVer);///���㶥��ĸ�˹����
	 static double CalcuVerMeanCurvature(PVERT pVer);///���㶥���ƽ������
	 static double AreaTriMixSum(PVERT pVer);//һ������������ܺ�
	 static double AreaTriMix(PPOINT3D pPoint1, PPOINT3D pPoint2, PPOINT3D pPoint3);//���㶥��һ��������������εĻ�����������������Ϊ��ָ�붥��[pPoint1]���ڵĲ��ֵ������
	 static POINT3D Center(PHEDGE trigle);///������Ƭ�����ĵ�
	 static PVECTOR3D CalcuPfacNormal(PVERT pVer0, PVERT pVer1, PVERT pVer2);///������Ƭ�ķ�ʸ
	 static VECTOR3D CalcuPfacNormal(POINT3D pVer0, POINT3D pVer1, POINT3D pVer2);///������Ƭ�ķ�ʸ
	 static VECTOR3D CalcuVerNormal(PVERT pVer);////���㶥��ķ�ʸ,�Ե����������������ڼн�ΪȨֵ��������Ƭ��
	 static VECTOR3D CalcuVerNormal(PVERT pVer, PFACETTRI pFac);////����ռ��ķ�ʸ

	 static double CalcuPointCurve(PVERT A);////���㶥������ֵ
	 static BOOL FindOneRing(PVERT& pVer, vec_PVERT& vecpVer);////���������һ�����򶥵�
	 static BOOL FindOneRing_New(PVERT& pVer, vec_PVERT& vecpVer);////���������һ�����򶥵�(���㷨)
	 static BOOL FindOneRing_Me(PVERT& pVer, vec_PVERT& vecpVer);////���������һ�����򶥵�(�ҵ��㷨)

	 static BOOL FindOnePH(PVERT A, vec_PHEDGE& vecpH);//���������һ��������
     static BOOL FindOneRFac(PVERT pVer, vec_PFACETTRI& vecpFac);//���������һ��������Ƭ.  ������������ȥ���ˡ�
	 static BOOL FindTwoRing_new(PVERT pVer, vec_PVERT& vecpVerT);//���������Ķ��������
	 static BOOL FindTwoRing(PVERT pVer, vec_PFACETTRI& vecpFacT);
	 static void FindedgeOnering(PHEDGE Ph0, vector<PFACETTRI> &vecper);//Ѱ�Ұ�ߵ�һ��������Ƭ
	 static void FindedgeOneringvertex_Me(PHEDGE Ph0,vec_PVERT& vecpVer);////������ߵ�һ�����򶥵�(�ҵ��㷨)
	 static BOOL FindPOneRFAC(PFACETTRI pFac, vec_PFACETTRI& vecpFacP);///������Ƭ��һ��������Ƭ
	 static BOOL FindPOneRFAC_NEW(PFACETTRI pFac, vec_PFACETTRI& vecpFacP);///������Ƭ��һ��������Ƭ
	 static BOOL FindPOneRVetex(PFACETTRI pFac, vec_PVERT& vecpVer);///������Ƭ��һ�����򶥵�
	 static void FindPtwoRFAC(PFACETTRI pFac, vec_PFACETTRI& vecpFacP);///������Ƭ�Ķ���������Ƭ

	 static BOOL FindFourRing(PVERT pVer, vec_PVERT& vecpVerT);//�����������Ľ������

	 static BOOL KitTool::FinOneFac_Less(PFACETTRI pfc0);


	 static double CalcuPOINTV(PVERT A);//���㶥��İ�͹��
	 static void create_current_Frenet(MATRIX3D& currentM, VECTOR3D LineNor, POINT3D Center);//�����ֲ�����ϵ,����һ���ֲ�����ϵ
	 static void create_BACK_Frenet(MATRIX3D& currentB, VECTOR3D LineNor, POINT3D Center);//�ֲ�����ϵ��ԭ����������
	 static void create_current_matriX(MATRIX3D& matriX, double a);//��X��תa��
	 static void create_current_matriZ(MATRIX3D& matriZ, double a);//������Z����ת������
	 void cone_delel(vector<double>& vec_dis);//���ܵ����Ѱ
	 void create_cone_new(vector<VECTOR3D>& m_vecVECTOR3D, VECTOR3D LineNorZ, VECTOR3D LineNor, POINT3D orig, double angA, int numB);
	 BOOL IntersectTriangle(POINT3D orig, VECTOR3D dir, POINT3D v0, POINT3D v1, POINT3D v2);//������
	 void Dijkstra_Point_ST_EN_new(PVERT ST, PVERT EN, map<PVERT, PVERT>& Path, vector<PVERT>& BLOOP, vec_PVERT& m_vecPVert);//����֮�����·��
	double dis(POINT3D A, POINT3D B);

	void ClearTheList(STLModell *pMeshTriDate);
	static void ClearTheList(Blockpath &OneBlock);
	void StoretheMeshTri(STLModell *pMeshTri, STLModell *pMeshTriDat, int Onetime);
	static void StoreFactandVer(vec_PFACETTRI vec_Fact, vec_PFACETTRI &vec_PFact, vec_PVERT &m_vecPVert, map<VERT, int> &map_Vert, map<VERT, int>::iterator &iter, int &vetexID);
	static void CreateEdgeTopByFctVert(Blockpath &OneBlock);//�������������Ϣ
	static bool JudgeFaceDir(POINT3D v00, POINT3D v10, POINT3D v20, VECTOR3D FaceDir);//�ж���Ƭ�����Ƿ���ȷ

	static bool judeorientation(PPOLYGON poly);
	static bool pointInpoly(POINT3D p, PPOLYGON poly);
	static double GetPolypolyArea(PPOLYPOLYGON ppolypolygon);
	static double GetPolyArea(PPOLYGON poly);
	static void  RotateAllFacet(vector<PFACETTRI> &OneBlock, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת������Ƭ����
	static void  RotatePolygon(vec_PPOLYPOLYGON pployploy, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת��ģ��
	static void  RotateOneRingPolygon(PPOLYGON ploy, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת��
	static void  RotateTwoRingPolygon(PPOLYPOLYGON vec_poly, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת��
	static 	void FindCircleNearPoint(POINT3D p, POINT3D &NearP, PPOLYGON poly);//���������ĵ�
	static 	void FindCircleNearPoint1(POINT3D p, int &num, PPOLYGON poly);//���������ĵ�

	static double GetPerimeter(POLYGON poly);//���㻷���ܳ�
	static bool lineSegInter(POINT3D p1, POINT3D p2, POINT3D p3, POINT3D p4, POINT3D &p);
};

