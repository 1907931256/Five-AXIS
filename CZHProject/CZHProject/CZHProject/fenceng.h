#pragma once
#include <map>
#include <algorithm> 
#include"DrawTool.h"

#include "Mix.h"
#include "helical_path.h"
#include "unicursal.h"
////////////////////�ӿ���
#define    OFFSETFILL        0
#define    LINFILL           1
#define    MIXFILL           2
#define    SPINFILL          3
#define    UNICURSALFILL     4

class fenceng 
{
public:
	fenceng();
	virtual ~fenceng();

public:
	KitTool *kit;
	
public: 
	void GetEvenslice(STLModell* pMeshTri, vec_PPOLYPOLYGON &lunkuo, VECTOR3D DirV, float Even_Thickness, QProgressBar  *progressBar);
	void GetBlockEvenslice(vector<MyBlock> &Rbox, vector<vec_PPOLYPOLYGON> &lunkuo, vector<VECTOR3D> &All_VecDir, float Even_Thickness, QProgressBar  *progressBar);

	void GetBlockFillResult(vector<vec_PPOLYPOLYGON> Blocklunkuo, vector<VECTOR3D> All_VecDir, vector<vec_PPOLYPOLYGON> &BlockFill, QProgressBar  *progressBar, double FillDia, int Fillway);
	void GetFillResult(vec_PPOLYPOLYGON lunkuo, VECTOR3D Vec_Dir, vec_PPOLYPOLYGON &FillResult, QProgressBar  *progressBar, double FillDia, int Fillway);

	
	void Calthecenterpoint(Blockpath OneBlock, VECTOR3D Current_Dir,POINT3D &p0D);//��ȡ��ǰ��ָ�ƽ������ĵ�
	void CaltheFarpoint(Blockpath OneBlock, VECTOR3D Current_Dir,POINT3D p0D, POINT3D &p1D);//��ȡģ���Ͼ��뵱ǰ�ָ�ƽ�����Զ�ĵ�
	void Caleachlayerboundarypoint(Blockpath OneBlock, vec_PPOLYPOLYGON &lunkuo, bool IfFir, VECTOR3D Curr_Dir, float dept, QProgressBar  *progressBar);//�෽��ֲ㺯��
	bool Checkphedgegood(PFACETTRI Pfact, PHEDGE &PHE, PHEDGE &PHE_0, POINT3D planeVer, POINT3D &face_point, VECTOR3D Curr_Dir);

	bool IntersectLinePlane(POINT3D LinePt, VECTOR3D LineNor, PFACETTRI pFacTri, POINT3D &InterP);

	void Caleachlayerboundarypoint(STLModell* pMeshTri, vec_PPOLYPOLYGON &lunkuo, float dept, QProgressBar  *progressBar);//�ҵķֲ㺯��
    bool Checkphedgegood(PFACETTRI Pfact, PHEDGE &PHE, PHEDGE &PHE_0, POINT3D &face_point, float Zt);

	PPOLYPOLYGON GetHighSlice(STLModell *pSTL, float thickness_h);//By Lin�ֲ㺯��,2017.11.8���޸�
	bool CrossZ(PVERT p1, PVERT p2, double z, POINT3D &p3D);//By Lin

	void clear(vec_PPOLYPOLYGON &lunkuo);
	static  void  RotateModel(STLModell* STL, VECTOR3D curr_Dir, VECTOR3D tager_Dir);
	void  RotatesliceModel(vector<PPOLYPOLYGON> &lunkuo, VECTOR3D curr_Dir, VECTOR3D tager_Dir);
	
	
	void CaleachBlockboundarypoint(Blockpath pMeshTri, vec_PPOLYPOLYGON &lunkuo, float dept);//�õ�����ĳ��͹켣
	PPOLYPOLYGON GetHighSlice(Blockpath pMeshTri, float thickness_h,double startpoint);//By Lin�ֲ㺯��
	void CreateEdgeTopByFctVert(Blockpath &pMeshTri, vec_PFACETTRI m_vecpFact);

	bool IfAcuteAngle(VECTOR3D Dir, VECTOR3D Diz);//�鿴�Ƿ�Ϊ���
	bool FindSupportBlock(Blockpath OneBlock);//�鿴��ǰ��Ƭ�Ƿ��н϶���Ƭ��Z�ᴹֱ
	void FindBlockHole(Blockpath &OneBlock, vector<PFACETTRI> &vec_Pface, VECTOR3D vec_Dir, bool IfMb);
	void HoleRepair(vector<vector<POINT3D>> &vec_Face, VECTOR3D vec_Dir, PPOLYGON ploy);//���ӿ��޲��׶����ؽ����˹�ϵ
	void LoopOneFace(bool IfThree, VECTOR3D FaceDir, vector<POINT3D> Face, vector<vector<POINT3D>> &vec_Face);//��һ�������ν���ϸ��
	bool IfBoundFace(vector<POINT3D> Face, vector<POINT3D> vec_Point);//�ж�һ���������Ƿ�߽�������
	void StoreTheBlock(vec_PFACETTRI m_vecPFact, Blockpath  &OneBlock);
	
	void LoopOnehole(VECTOR3D vec_Dir, PPOLYGON ploy, vector<vector<POINT3D>> &vec_Face);//��һ���׶�����ϸ��
	void LoopOnehole1(VECTOR3D vec_Dir, PPOLYGON ploy, vector<vector<POINT3D>> &vec_Face,POINT3D &Pceshi);//��һ���׶�����ϸ��
	void WipeErrorLayer(vec_PPOLYPOLYGON &lunkuo);

	void  UpdateBlockBox(MyBlock pMeshTri, BOX3D &ONE);
	void  UpdateBlockBox(Blockpath pMeshTri, BOX3D &ONE);
	void  RotateBlockModel(Blockpath pMeshTri, VECTOR3D curr_Dir, VECTOR3D tager_Dir);

	////////////////////////////////��ͼ����////////////////
	static void  Draw(drawTool *pDC, vec_PPOLYPOLYGON Plunkuo);//�ֲ�������ʾ
	static void  Draw(drawTool *pDC, vec_PPOLYPOLYGON Plunkuo,int nLayer);//�ֲ�������ʾ,�ض���Ŀ
	static void  DrawOneLayerFill(drawTool *pDC, PPOLYPOLYGON Polypoly);//һ�����������ʾ
	static void  DrawThatLayerFill(drawTool *pDC, int CurrentLayer, vec_PPOLYPOLYGON Plunkuo);//��0�㵽��ǰ�����������ʾ
	static void  DrawFill(drawTool *pDC, vec_PPOLYPOLYGON Plunkuo);//���������ʾ
	static void  DrawFill(drawTool *pDC, COLORREF newcolor,vec_PPOLYPOLYGON Plunkuo);//���������ʾ
};

