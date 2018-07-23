#pragma once
#include "STLModell.h"
#include "datastructure/mesh.h"
#include "datastructure/solidMesh.h"
#include "datastructure/solidPolygon.h"
#include "KitTool.h"
#include "datastructure/GeomBase.h"
#include "time.h" 
#include <omp.h>
#include "eigen\Eigen"
#include "viewspace\QRoundProgressBar.h"

#include "Timer.h"
using namespace Eigen;
using Eigen::MatrixXd;

////////////////////�ӿ���
#define    EDGESUB         0
#define    ME           1
#define    SMOOTH       2
#define    ZHANGXING    3
class CSimplify
{
public:
	CSimplify();
	virtual ~CSimplify();
protected:

	//Ԥ�ȶ������ߵıȽ����㷨��
	struct Compedge
	{
		bool operator ()(const PEDGE pE1, const PEDGE pE2)
		{
			if (pE1->pVertEnd->m_id == pE2->pVertStart->m_id)
			{
				if (pE1->pVertStart->m_id != pE2->pVertEnd->m_id)
				{
					return true;
				}
				else{ return false; }
			}
			else
			{
				return false;
			}
			return false;
		}
	};
	struct ErrorValue
	{
		double Valchoose;
		PVERT P0;
		ErrorValue()
		{
			Valchoose = 0;
			P0 = new VERT;
		}
	};

public:
	double featureTimeTemp, TriangleTimeTemp;
	double featureTime, TriangleTime;
	vec_POINT3D edgepoint;

public:
	KitTool *Kit;
	//////////////�����////////////////////////

	void GetsimpleResult(STLModell *pMeshTri, STLModell *pSimple, int simpway, int R, int ratepercent, QProgressBar  *progressBar);//���е�����ü򻯽��
	void EvaluatemeshQuality(STLModell *pMeshTri, double &neq);//���������
	void PushUntreatedFace(vector<PFACETTRI>  vec_Temp, STLModell *pSimple, map<VERT, int>map_Vert,
		map<VERT, int>::iterator iter, int VetxID, int Onetime);//��δ�������Ƭ��������

	////////////////���۵��򻯣����Σ���ʽ/////////////////////
	void EdgesimpleResult(STLModell *pMeshTri, STLModell *pSimple, float R);//��ñ߼򻯽��
	BOOL Judgelegal(PEDGE Pedge, vector<PFACETTRI> &vecper);//�ж�һ�����Ƿ���Ա��۵�
	void AssortTriangle(vector<PEDGE>  vecPedge);//ʶ�����������Ƭ�����б��
	void CalerrorLittleValue(PHEDGE Ph0, PVERT p0);///�����������۵����ͱ��涥��ĺ���
	MatrixXd Planeeuate(PFACETTRI PFc0);//��һ��������Ƭ���ڵ�ƽ�淽��
	void Planeeuate(PFACETTRI PFc0, vector<double> &facepare);//��С���������ƽ�淽��
	void CalValue_pointplane(PHEDGE Ph0, vec_PFACETTRI vecper);
	//////////////////////������Ƭ�򻯷�ʽ///////////////////////
	/*�ҵļ��㷨*/
	void TrianglesimpleResultMe(STLModell *pMeshTri, STLModell *pSimple, float R, int Onetime);//�����Ƭ�򻯽��
	void MarkparticularArea(STLModell *pMeshTri, STLModell *pSimple, map<VERT, int> &map_Vert,
		map<VERT, int>::iterator &iter, int &VetxID);//SOD�����㷨������������۵���������
	BOOL Markboundary(STLModell *pMeshTri, STLModell *pMeshDate);//��ǲ��۵��߽�������������
	void CalvalueAndpoint(vector<PFACETTRI> vecPfact);//�����������۵����¶�����۵�����
	BOOL Judgelegal(POINT3D p0, POINT3D p1, POINT3D p2);//�жϱ߽��Ƿ���Ա��۵�
	BOOL Judgelegal(PFACETTRI PFc0);//�ж�һ���������Ƿ���Ա��۵�

	void AcqnewVertex_curdegree(PFACETTRI Pfact);//���Ȳ�ֵ��ȡ�ڲ��������¶���
	void AcqnewVertex_Oneofthree(PFACETTRI Pfact, vec_PFACETTRI vecper);//����ѡһ��ȡ�¶���
	void AcqnewVertex_Gravity(PFACETTRI Pfact);//������Ϊ�¶���
	void CalValue_pointplane(PFACETTRI Pfact,vec_PFACETTRI vecper);//��������ȸĽ���
	void CalValue_Wmsa(PFACETTRI pFac);//�����Ȩƽ���÷�ʸ���������
	void CalValue_Fitcurve(PFACETTRI pFac);//��С�����������
	void CalValue_Fitplane(PFACETTRI pFac);//��С����ƽ�����
	void CalValue_QEM(PFACETTRI pFac, vec_PFACETTRI vecper);//���������


	///////////////һ�ֻ��ڲ�ƽ���ȵ������μ��㷨////////////////
	void TrianglesimplesmoothResult(STLModell *pMeshTri, STLModell *pSimple, float R);//��ñ߼򻯽��
	void CalSmoothDegree(PVERT p0, vec_PVERT OneRingvert);//�������񶥵�Ĳ�ƽ����
	void CalerrorLittleValue(vector<PFACETTRI>  vecPfact);///�����������۵����ͱ��涥��ĺ���
	BOOL Judgelegalsmooth(PFACETTRI PFact, vector<PFACETTRI> &vecper);//�ж�һ���������Ƿ���Ա��۵�
	BOOL EliminatetheReapetedFace(PFACETTRI Pf0, vector<PFACETTRI> vecper);//ȥ�����۵�������ظ�����

	///////////////һ�ֻ����������ֵĵ������μ��㷨////////////////
	void TrianglesimpleResult(STLModell *pMeshTri, STLModell *pSimple, float R);
	void AssortTriangle(vector<PFACETTRI> vecPfact, double &Lsmin, double &Lsmax);
	BOOL EliminatetheReapetedFace(PVERT p0, PVERT p1, int j, vector<PFACETTRI> vecper);//ȥ�����۵�������ظ�����
	void CalerrorLittleValue(PFACETTRI Pf0, PVERT p0);
	void Checkparticular(PFACETTRI &PFc0, double t0);/////////�ж�һ���������Ƿ�Ϊ����������
	BOOL Judgelegal(PFACETTRI PFc0, vector<PFACETTRI> &vecper);//�Ϸ��Լ��
	double Longdegree(PFACETTRI PFact);//����������
	double SumRingArea(PVERT P0);//������һ�����������
	double SumRingPfacArea(PFACETTRI PFact);//������Ƭ��һ�����������
	double Lshapedegree(PFACETTRI PFact);//���������εľֲ������
	void AcqnewVertex(PFACETTRI PFact, double &value);//��ȡ�ڲ��������¶���
};

