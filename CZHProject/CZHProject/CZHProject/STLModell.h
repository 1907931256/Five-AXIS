#pragma once
#include "datastructure/solidMesh.h"
#include "datastructure/polygon.h"
#include "DrawTool.h"
#include "datastructure/mesh.h"
#include "K-d tree/KDtree.h"
#include "sys/stat.h"
#include <map>
//д���õ�//
#include <cstdlib>
#include <iostream>
#include <fstream>
#define COND_READ(cond, where, len) do { if ((cond) && !fread((void *)&(where), (len), 1, f)) return false; } while (0)
//Ԥ�ȶ������ߵıȽ����㷨��
struct CompPEDGE
{
	bool operator ()(const PEDGE pE1, const PEDGE pE2)
	{
		if (pE1->pVertStart < pE2->pVertStart) return true;
		if (pE1->pVertStart > pE2->pVertStart) return false;
		if (pE1->pVertEnd < pE2->pVertEnd) return true;
		if (pE1->pVertEnd > pE2->pVertEnd) return false;
		return false;
	}
};


class STLModell :public CSolidMeshTri
{

public:
	static STLModell* GetInstance();
	STLModell();
	~STLModell();
	static  MATRIX3D CreateRotateMatrix(double da, VECTOR3D v);
	static  MATRIX3D CreateTranMatrix(VECTOR3D v);
	static void CreateEdgeTopByFctVert(STLModell* pMeshTri);

	bool LoadTextSTLFile(const char *ffile, vector<VECTOR3D> &All_VecDir, vector<vector<int>> &All_PairBlock, QProgressBar  *progressBar);
	bool LoadSTLFile(const char *ffile, QProgressBar  *progressBar);
	bool IsTextFile(const char *strFileName);
	void Zooommesh(STLModell* pMeshTri, STLModell* pMeshTemp, float _xzoom, float _yzoom, float _zzoom);

	bool write_stl(STLModell* pMeshTri, FILE *f);//д��Ϊ�����Ƹ�ʽ�ļ�
	void Write_STL(STLModell* pMeshTri, const QString _filepath);//д��Ϊ�ı���ʽ�ļ�

	void Write_STLSEG(vector<MyBlock> &Rbox, vector<VECTOR3D> All_VecDir, const QString _filepath);//д���ָ���Ϊ�ı���ʽ�ļ�

	void Write_BlockFillResult(vector<vec_PPOLYPOLYGON> BlockFill, vector<vec_PPOLYPOLYGON> Blocklunkuo, vector<VECTOR3D> All_VecDir, const QString _filepath);//д���ֿ������
	void Write_FillResult(vec_PPOLYPOLYGON ModelFill,vec_PPOLYPOLYGON Modellunkuo, VECTOR3D Dir, const QString _filepath);//д��ģ�͵�һ���������

	bool we_are_little_endian();
	void swap_int(int &x);
	void swap_float(float &x);
	void swap_unsigned(volatile unsigned &x);
	virtual bool	IsEmpty();
	virtual	void	UpdateBox();
	virtual void     Draw(drawTool *pDC);
	void    GetBox();
	void  GetMainBlockBox(vector<PFACETTRI>  OneBlock, BOX3D &ONE);//��ȡ���ӿ��Χ�д�С
public:
	BOX3D    box;
	drawTool*pdc;
	KDtree *m_Tmesh_KD;
	BOX3D ONE;
};



