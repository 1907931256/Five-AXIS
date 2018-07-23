#pragma  once
#include "QGLWidget"
#include "datastructure/GCamera.h"
#include "fenceng.h"
#include "MeshBlock.h"
//#include"Optisequence.h"
#include "DlgBlockSeq.h"

#include "BackGround.h"
#include "viewspace/ShowShader.h"
#include <QOpenGLFunctions_3_3_Core >
#include<QMessageBox>
#include <memory>
#define BUFFER_LENGTH 64

#define VIEW_FRONT         0
#define VIEW_BACK          1
#define VIEW_TOP           2
#define VIEW_BOTTOM        3
#define VIEW_RIGHT         4
#define VIEW_LEFT          5
#define VIEW_SW_ISOMETRIC  6
#define VIEW_SE_ISOMETRIC  7
#define VIEW_NE_ISOMETRIC  8
#define VIEW_NW_ISOMETRIC  9

#define ZOOM_ALL           10
#define ZOOM_IN            11
#define ZOOM_OUT           12

using namespace ViewSpace;
class WGLWidge :public QGLWidget,protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT
public:
	WGLWidge();
	virtual ~WGLWidge();

	int BkMode;
	bool m_box,m_board, fullscreen;
	vector<vec_POINT3D> p_Row;//ƽ̨�㼯
	vector<vec_POINT3D> vec_Plat;//ƽ̨��Ƭ

	vector<vec_POINT3D> p_RowRotate;//ƽ̨�㼯
	vector<vec_POINT3D> vec_PlatRotate;//ƽ̨��Ƭ

	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();                             //��ͼ����
	void DrawCoord();                          //�����û�����ϵ

private:

	COLORREF m_clrBk;       //���ڱ���ɫ
	COLORREF m_clrHighlight;//���ڸ�����ʾʱ��ģ����ɫ����ʰȡһ������ʱ��Ҫ��������ʾ
	COLORREF m_clrMaterial; //���ϵ���ɫ
	BOOL     m_bShading;    //�Ƿ������ɫ��ʾ
	GLfloat  m_vecLight[3]; //��Դ����

	BOOL     m_bSelectionMode;            //��ǰ�Ƿ���ѡ��ģʽ

	float *positionData;
	GLuint vaoHandle;
	GLuint m_VertexBuffer, m_NormalBuffer, m_IDBuffer;
	GLuint   m_selectBuff[BUFFER_LENGTH]; //ѡ�񻺴���

	ShaderModel     m_ShaderModel;
	GCamera *m_camera; drawTool *pDC;
	
	
public:
	void Zoom(double dScale);     // ���ų���
	void ZoomAll(BOX3D box);           // ����һ�����ʵ����űȣ��Խ�ģ��ȫ����ʾ�ڳ�����
	void OnViewType(UINT type);   // ʹ�õ����ӽ����۲�ģ��
	void MoveView(double dpx, double dpy);// ����ǰ�����ߴ�İٷֱ��ƶ�����������dpx��dpy�ķ�Χ��0~1
	void RotateView(double drot, short snXyz);

	/////////////OPENGL�������////////////////////////////
protected:
	void ClearBKground(); //���������ɫ
	void OnShading();     //����/�ǹ���ģʽ����

public:
	void GLSetupRC();                 //������Ⱦ����
	//////////////////�Թ�������ɫ�Ĳ�������//////////////////////

	void Shading(BOOL bShading);        //����/�ǹ���ģʽ�л�
	BOOL IsShading();                   //��ǰ�Ƿ�����ɫģʽ

	void Lighting(BOOL bLighting);      //�Ƿ�ʹ�ù�Դ
	BOOL IsLighting();

	void CreatLight();                 //�����鴴����Դ
	void SetLightDirection(float dx, float dy, float dz);  //�������ȡ��Դ����
	void GetLightDirection(float& dx, float& dy, float& dz);

	void SetBkColor(COLORREF rgb);                 //�������ȡ������ɫ
	void GetBkColor(COLORREF& rgb);

	void SetHighlightColor(COLORREF clr);         //�������ȡ��������ʾ����ɫ
	void GetHighlightColor(COLORREF& clr);

	void Highlight(BOOL bLight = TRUE);           //������/������ʾ�л�

	POINT3D BeginSelection(int xPos, int yPos);
	int EndSelection(UINT* items);
	void initVBO(STLModell  * pSTLTemp);         //�µ�OPENGL��ʾ����
	void  deleteVBO();
	void deleteModel(STLModell  *MySTL);

	bool ceshi;
	vector<vec_POINT3D> vec_Ceshi0; vector<vec_POINT3D> vec_Ceshi1;
	vector<vec_POINT3D> vec_HeadBox;//��ӡͷʵ��ģ��
	vector<vec_POINT3D> vec_PlanBoard;
	void CreatBoxcir(POINT3D Pcenter, VECTOR3D DirV);//������ӡ��ͷģ��
	POINT3D CalCenterPoint(MyBlock CurrnetBlock, VECTOR3D DirV);//���㵱ǰ�����ײ����ĵ�
	void RotateHeadBox(vector<vec_POINT3D> &vec_face, VECTOR3D curr_Dir, VECTOR3D tager_Dir);//��ת��ӡͷ��Χ��

private:
	
    void GeneratePlatform(POINT3D pr0);//����ƽ̨��
	void DrawBlockDirResult();//���ƿ鷽���Ż����
	void DrawSliceResult();//������Ƭ���
	void DrawFillResult();//���������
	void DrawSeqLayer();//���Ʋ���ʾЧ��
public:
	bool m_Headbox,m_Dirback;
	bool m_bIfShowSTL,m_IFSimple,m_Block,m_optiSeQ,m_slice, m_Fill;
	bool m_SliceSeqShow,m_Alltractory;//���տ�ӹ�˳��ֲ���ʾ�ӹ��켣
	bool m_cutline, Projectway = false;
	
	int Nublcok;
	POINT3D Plow;//��ǰ�ӿ����͵�
	POINT3D PMainlow;//���ӿ����͵�
	vector<vector<PFACETTRI>>  ALLBlock;


	STLModell  *pSTL; STLModell *pMeshZoom; STLModell *PSimple;
	fenceng *pslice; MeshBlock Pmeshblock;
	STLModell  *Pmblock; STLModell *PmblockTemp;//׷��ͶӰ������ָ�����
	COptisequence pSEQ;  DlgBlockSeq dlg;

	int NCurrentlayer;
	vec_PPOLYPOLYGON lunkuo, Fill;
	vector<vec_PPOLYPOLYGON> Blocklunkuo;//�ӿ���Ƭ�켣
	vector<vec_PPOLYPOLYGON> BlockFill;//�ӿ����켣

	vec_PPOLYPOLYGON SeqlunkuoLayer;//˳����ʾ�����ӿ���Ƭ�켣
	vec_PPOLYPOLYGON SeqFill;//˳����ʾ�����ӿ����켣


	vector<vector<PFACETTRI>>  SimALLBlock;//���������ӿ�λ��
	vector<vec_PPOLYPOLYGON> ToolpathLayer;//˳����ʾ�ӿ���Ƭ���Ƴ���켣
	vector<vec_PPOLYPOLYGON> ToolpathFill;//˳����ʾ�ӿ������Ƴ���켣
	////////////�ֿ��Ż�����////////////
	int nBlock,nShowBdir;
	vector<vector<int>> All_PairBlock;
	vector<vec_PVERT> CFpoint; bool CF;
	vector<vec_PVERT> FeaPointAll;
	///////////////�����Ż�����///////////////
	bool       m_bOptiDir;
	VECTOR3D  m_VecDir;
	vector<VECTOR3D> All_VecDir;
	vector<vector<int>> 	m_vecFacetNum;
	vector<vector<vector<int>>> All_vecFacetNum;
	bool m_IfshowDir, m_Beoptir;//�����Ż�����

	bool m_SwichBlock,Sblock;
	vector<vec_POINT3D> modelPOINT;
	vec_POINT3D  mPOINTTemp;//ʰȡ��

	vector<vector<PVERT>>path;
	vector<vector<Insepoint>> pathTrace;//׷��ͶӰ���켣��
	vector<MyBlock> Rbox;//����ģ�ͷָ��Ľ��
	vector<vector<PVERT>> RBLOOP;//�ָ��߹�˳���ݱ���

	vec_PPOLYPOLYGON BlockEdge;//�洢��߽綥��
};