#ifndef MYQT_H
#define MYQT_H
//#include "LoginDlg.h"
#include "ZoomDlg.h"
#include "RoughdetectDlg.h"
#include "MeshSaveDlg.h"
#include "BoxDLg.h"
#include "TanshexianDlg.h"
#include "BlackgroundDlg.h"
#include <QtWidgets/QMainWindow>
#include "ui_myqt.h"
#include "QGLWidget"
#include "WGLWidge.h"

#include "viewspace/ShowShader.h"
#include "time.h" 
#include "DlgOptisequence.h"


#define ROTATE_ANGLE   -0.08726646260
#define ROTATE_ANGLE_NEG   0.08726646260
class MyQT : public QMainWindow
{
	Q_OBJECT

public:
	MyQT(QWidget *parent = 0);
	~MyQT();
public:
	WGLWidge  *opgl;
private:   
	Ui::MyQTClass *ui;
public:
	QPoint pOld;
	bool MouseDown;
	bool m_bifCtrl;
	QPoint mousepickpoint;

	int m_laplacian;
	double simpletime;
	VECTOR3D    m_VecDir;
	float m_equdept,m_mindept,Diamer,rate,ratepercent;

	
	
public:
	/////�����ڻ��ƺ���/////////
	void keyPressEvent(QKeyEvent *e);
	void paintEvent(QPaintEvent *); 
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void  mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void setprogressbar();
	void Displayparameter(int choe);
	///////////�ۺ���////////
public slots :

/////////////////////��ͼ����/////////////////////////////
	void ViewBack();
	void ViewBottom();
	void ViewFront();
	void ViewLeft();
	void ViewRight();
	void ViewTop();
	void ViewIsometric();
	void ViewZoomall();
	void ViewZoomin();
	void ViewShade();
	void Viewshow();
	void ShowBoard();
	void ShowBox();
	void ShowBlock();

	void ActionMenu();
	void ActionWelcome();
	void ActionBlock();
	void ActionPathdesign();
	/////////////////////���ܺ���/////////////////////////////
	void FileOpen();
	void Linput(QString);

	void MeshZoom();
	void MeshSave();

	void SimplifyGrid();
	void Calmeshdegree();


	void Detectvetex();
	void Detectedge();
	void Skeletonizing();

	void Laplacian();
	void Laplacianback();
	void LaplacianFeature();

	POINT3D ScreenToPoint(QPoint P);
	void CutLineshow();
	void CutLineTrace();
	void CutLineDir();

	void MeshBlock();//�ֿ�
	void MeshBlockOpti();
	void DetectBlock();//�޲��׶�
	void BlockSave();
	void BlockSwitch();//�ֿ����л�
	
	void DirTackBack();//���Ż�������
	void ShowOpti();//��ʾ��ֲ㷽��
	void ChangeDir();//��������ֲ㷽��
	void OptiDir();//�ӿ����ų��ͷ����Ż�

	void BlockSQ();//�Ż��ӿ�ӹ�˳��
	void ShowSeQ();//�л���ʾ�ӹ�˳��
	void ShowHeadbox();//��ʾ��ӡͷ��Χ��
	void Ceshi();

	void Slicing();//��Ƭ
	void Shadeslice();//������Ƭ

	void OnFill();//ƫ�����
	void SeqLayerShow();//���տ�ӹ�˳��ֲ���ʾ�ӹ��켣
	void saveFillResult();//�Լ��±���ʽ����·�����

	void SimlateResult();
	void SimlastBlock();
	void SimNextBlock();
};

#endif // MYQT_H
