#pragma  once
#include "datastructure/GeomBase.h"
#include <glaux.h>
#include "QtOpenGL"
#include "glut.h"
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
class drawTool 
{
public:
	drawTool();
	virtual ~drawTool();
	COLORREF m_clrMaterial; //���ϵ���ɫ
	COLORREF m_clr;         //�ǹ���ģʽ�µ�ģ����ɫ

	COLORREF	m_clrBkMaterial;  //for normal rendering
	void SetMaterialColor(COLORREF clr);            //�������ȡ������ɫ
	void GetMaterialColor(COLORREF& clr);
	void SetBkMaterialColor(COLORREF clr);
	void SetColor(COLORREF rgb);                  //�������ȡ�ǹ���ģʽ�µĻ�����ɫ
	void GetColor(COLORREF& rgb);

	static void	DrawText(char* string, int flag = 12);
	string itos(int i);//intתstring����
public:
	void DrawBox(BOX3D bot);
	void DrawHeadBox(vector<vec_POINT3D> vec_face, COLORREF clr);//���ƴ�ӡͷ
	void DrawSphere(const POINT3D& cen, double r);
	void DrawPickPoint(const vector<POINT3D> &modelPOINT);//���ƽ���ʰȡ��
	void DrawPoint(const POINT3D&);            //����һ���ռ��
	void DrawLine(const POINT3D& sp, const POINT3D& ep);//����һ��ֱ��
	void Drawcone(const POINT3D &cen, double r, VECTOR3D &h);
	virtual void DrawTriChip(double n0, double n1, double n2, double v00, double v01, double v02,       //����һ��������Ƭ
		double v10, double v11, double v12, double v20, double v21, double v22);
};