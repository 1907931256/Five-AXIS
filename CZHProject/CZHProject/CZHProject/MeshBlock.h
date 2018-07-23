#pragma once
#include "DijkstraGeodesic.h"
#include"Boundary.h"
#include "Laplacian.h"
#include "CSimplify.h"
#include "DlgOpti.h"
#include <math.h>
class MeshBlock
{
public:
	MeshBlock();
	virtual ~MeshBlock();
public:
	KitTool PkiTool;
	Cboundary *pcboundary; CLaplacian *pLaplacian; 
	CSimplify *pSimply; CDijkstraGeodesic pcedie;

public:

	//������˹����ǰ�Ĳ���
	vec_POINT3D m_vecLp;
	vec_VECTOR3D m_vecV;
	bool m_Laplacian;
	vector<EDGE> vec_edge;
	

public:
	void SharpEdgeDetection(STLModell *pMeshTri, vec_EDGE &vec_edge);//�����ʶ��
	void featurPOINT(vec_PFACETTRI& m_vecPFacetTri, vec_PHEDGE& m_vecPHEdge, vec_PVERT& m_vecPVert, double &NVlimit);//�ҵ���������

	bool CutLineTraceProjection(vector<POINT3D> pt, vector<PVERT>&path, vector<Insepoint> &pathTemp, STLModell* m_Tmesh);//׷��ͶӰ����ָ���
	void CutTraceProjection(vector<Insepoint> pathTemp, vec_PFACETTRI& m_vecPFacetTri, vec_PVERT& m_vecPVert, STLModell* m_Tmesh);
	bool CalVetexNormal(PVERT p0, PVERT p1, PVERT p2, PVECTOR3D FaceNormal);//ͨ����ʸ�ı䶥��˳��
	void PickPoint(vector<POINT3D> pt, vector<PVERT>&path, STLModell* m_Tmesh);//��ؾ��뷨ʰȡ�ָ���
	bool CalDispath(PVERT& PVer,PVERT Rpoint, double &Sdist,vector<PVERT> path);//�����㵽������С����
	//�Ż��ָ���
	bool CutLineDir(vector<vec_PVERT> &FeaPointAll, vector<vec_PVERT> &CFpoint, vector<MyBlock> &Rbox, vector<VECTOR3D> All_VecDir, vector<vector<PVERT>>&path, vector<vector<Insepoint>> &pathTrace, STLModell* m_Tmesh);//�Ż���ָ��ߣ�����һ��������ų��ͷ���
	bool CutLineDir1(vector<vec_PVERT> &CFpoint, vector<MyBlock> &Rbox, vector<VECTOR3D> All_VecDir, vector<vector<PVERT>>&path, vector<vector<Insepoint>> &pathTrace);//�Ż���ָ��ߣ��������������������㣩
	bool CutLineDir2(vector<vec_PVERT> &CFpoint, vector<MyBlock> &Rbox, vector<VECTOR3D> All_VecDir, vector<vector<PVERT>>&path, vector<vector<Insepoint>> &pathTrace, vec_PVERT m_vecPVert);//�Ż���ָ��ߣ��������������������㣩

	bool IfNeedLoop(vector<Insepoint> path);//�鿴�Ƿ���Ҫ����ϸ��
	void Updatecutline(vector<vector<PVERT>> &path, vector<vector<Insepoint>>  pathTemp, vec_PVERT m_vecPVert);//����δ������ı߽��߶���

	//��ͼ����/////////////////////////
	void showfeatureEdge(drawTool *pDC);//˳�����Ӳ���ʾ�����߽�
	void showEdge(drawTool *pDC, vec_EDGE vec_Edge);//��������ʾ
	void Render(drawTool* pDC, vector<PVERT> m_Path_Point);//���Ʒָ���

	void DrawPoint(drawTool* pDC, vector<vec_PVERT> CFpoint);//�Ż��ָ������Ű�����ʾ
	void DrawFeapoint(drawTool* pDC, vector<vec_PVERT> FeaPointAll);//�ָ��߰���������ʾ
	void Drawblock(drawTool* pDC, vector<MyBlock> &Rbox);//���ƿ�ָ���
	void Drawblock(drawTool* pDC, COLORREF newcolor, vec_PFACETTRI& m_vecPFacetTri);//���ƿ�ָ���

	void DrawSwichBlock(drawTool *pDC, int nBlock, vector<MyBlock> &Rbox);//���Ʒָ��ӿ�
	void Getreadblock(vec_PFACETTRI& m_vecPFacetTri, vector<vector<int>> All_PairBlock, vector<MyBlock> &Rbox);//ʶ�����ģ�ͷָ��
	void DrawPlat(drawTool* pDC, vector<vec_POINT3D> PlatFace, vector<vec_POINT3D> p_Row);//����ƽ̨
};
