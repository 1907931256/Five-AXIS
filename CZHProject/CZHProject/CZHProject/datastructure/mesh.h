#pragma once

#include "GeomBase.h"

struct   HalfEdge;
struct   Edge;
struct   Vertex;
struct	 Facet;
struct   FacetTri;


typedef struct   HalfEdge//��߽ṹ
{
	Vertex*   pVertEnd;   // vertex at the end of the half-edge
	HalfEdge* pHEdgePair;   // oppositely oriented adjacent half-edge 
    Facet*    pFacetAdj;         // face the half-edge borders
	HalfEdge* pHEdgeNext;   // next half-edge around the face
	HalfEdge* pHEdgePre;
	BOOL      be_pair;
	bool      bStatus;
	bool      bused;
	int       m_IDHEdge;
	vector<FacetTri*>   vec_FOneFac;//�ų��ڽӺ��һ��������Ƭ
	//////////////////�����ʱ�õ�////////////////////////
	Vertex*    Pvet;
	double value;
	HalfEdge(){
		pVertEnd = 0;
		pHEdgePair = 0;
		pFacetAdj = 0;
		pHEdgeNext = 0;
		pHEdgePre = 0;
		m_IDHEdge = 0;
		bStatus = false;
		be_pair = 0;
		bused = 0;
		Pvet = 0;
		value = 0;
	};
}HEDGE,*PHEDGE;


typedef struct   Edge//��
{
	Vertex*   pVertStart;
	Vertex*   pVertEnd;
	HalfEdge* pHEdgeAdj;
	BOOL      bStatus;
	int       m_nIDEdge;
	//////////////////�����ʱ�õ�////////////////////////
	Edge(){
		pVertStart = 0;
		pVertEnd = 0;
		pHEdgeAdj = 0;
		m_nIDEdge = 0;
		bStatus = FALSE;
	};
}EDGE, *PEDGE;


typedef struct   Vertex: public tagPoint3D//�����ζ���
{
	HalfEdge* pHEdgeOut;  // one of the half-edges emantating from the vertex
	int   m_id;
	vector<FacetTri*>   vec_OneFac;//һ��������Ƭ
	BOOL      bSharpVer;
	int VertexID;
	double Sdegree;//����Ĳ�ƽ����
	double cdrgee;//���������
	VECTOR3D VertexNormal;

	BOOL      bStatus;
	BOOL      bused;
	BOOL      theEND;
	Vertex(){
		pHEdgeOut = 0; bStatus = FALSE;
		VertexID = 0; Sdegree = 0; cdrgee = 0; m_id = 0; theEND = 0; bused = 0;
		VertexNormal = VECTOR3D(0, 0, 0); bSharpVer = false;
		//GausCur =0;
	};
}VERT,*PVERT;

typedef struct	Facet  //��Ƭ
{
	HalfEdge* pHEdge; // one of the half-edges bordering the face
	bool beused;
	BOOL      bStatus;
	PVECTOR3D m_PFacetNorm;

	Facet(){pHEdge = 0;
	        beused = false;
			m_PFacetNorm = 0; bStatus = FALSE;
	};
} FACET, *PFACET;

typedef struct FacetTri:public Facet  //������Ƭ
{
	PVERT m_PVerts[3];
	bool befrost;//��������
	bool becut;
	bool beboard;
	int Fnumber;
	int Nblock;
	int       ID;
	/////////�����ʱ�õ���//////////////
	bool beused;
	vector<FacetTri*>   vec_FOneFac;//�ų��ڽӺ��һ��������Ƭ
	double value;
	bool beSelect;
	PVERT Pvet;
	FacetTri()
	{
		m_PVerts[0] = m_PVerts[1] = m_PVerts[2] = 0; beSelect = false; beboard = 0; becut = 0; beused = 0; befrost = 0; value = 0; Pvet = 0; ID = -1; Fnumber = -1; Nblock = 0;
	}
	int  num;
}FACETTRI, *PFACETTRI;
/////�Լ�д�Ľṹ��
typedef struct SpaceInset
{
	int Epoint;//���������
	POINT3D pTemp;//��������
	PVERT InsEdge_Start;//�������ڱߵ����
	PVERT InsEdge_End;//�������ڱߵ��յ�

	PVERT NearVert;//���㿿������ĵ�
	PHEDGE PVertAdj;
	PFACETTRI pFac;//�������ڵ���Ƭ
	SpaceInset(){

		Epoint = 0; InsEdge_Start = NULL; InsEdge_End = NULL; NearVert = NULL; PVertAdj = NULL; pFac = NULL;
	}
}Insepoint, *PInsepoint;
typedef struct SpaceBlock
{
	bool Status;
	vector<PFACETTRI>  OneBlock;
	vector<SpaceBlock> OneBlockPair;//����ڽӿ���Ϣ
	vector<int> vec_PairBlock;
	POINT3D box_p0;
	POINT3D box_p1;
	SpaceBlock(){
		Status = 0;
	}
}MyBlock, *PMyBlock;

typedef struct AllBlock
{
	vector<PHEDGE>	m_vecPHEdge;
	vector<PEDGE>	m_vecPEdge;
	vector<PVERT>	m_vecPVert;
	vector<PFACETTRI>	m_vecPFacetTri;
	AllBlock(){
	}
}Blockpath, *PBlockpath;
typedef	vector<PHEDGE> vec_PHEDGE;
typedef vec_PHEDGE::iterator it_vec_PHEDGE;
typedef	vector<HEDGE> vec_HEDGE;
typedef vec_HEDGE::iterator it_vec_HEDGE;

typedef	vector<PEDGE> vec_PEDGE;
typedef    vec_PEDGE::iterator it_vec_PEDGE;
typedef	vector<EDGE> vec_EDGE;
typedef    vec_EDGE::iterator it_vec_EDGE;

typedef	vector<PVERT> vec_PVERT;
typedef    vec_PVERT::iterator it_vec_PVERT;
typedef	vector<VERT> vec_VERT;
typedef    vec_VERT::iterator it_vec_VERT;

typedef	vector<PFACET> vec_PFACET;
typedef    vec_PFACET::iterator it_vec_PFACET;
typedef	vector<FACET> vec_FACET;
typedef    vec_FACET::iterator it_vec_FACET;

typedef	vector<PFACETTRI> vec_PFACETTRI;
typedef    vec_PFACETTRI::iterator it_vec_PFACETTRI;
typedef	vector<FACETTRI> vec_FACETTRI;
typedef    vec_FACETTRI::iterator it_vec_FACETTRI;
