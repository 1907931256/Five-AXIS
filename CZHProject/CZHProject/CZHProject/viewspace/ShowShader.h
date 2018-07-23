#ifndef  CShowShader_H_
#define  CShowShader_H_
#pragma once
#include "STLModell.h"
#include "K-d tree/Vec.h"
#include "KitTool.h"
namespace ViewSpace
{
	enum ShaderModel
	{
		SMOOTH_SHADER,//ƽ����ɫ
		PLANE_SHADER,//ƽ����ɫ
		WIRE_FRAME,//�߿�ģʽ
		HIDE_WIRE_FRAME//�����߿�

	}; 
	class CShowShader
	{
	public:
		CShowShader();
		~CShowShader();
	public:
		/*vector<vec> vec_nomal; vector<point> vec_point;*/
	public:
		//COLORREF m_clrMaterial; //���ϵ���ɫ

		static void ShaderWireFrame(STLModell*Tmesh);
		static void PlaneShaderModel(STLModell*Tmesh);
		static void SmoothShaderModel(STLModell*Tmesh);
		static void ShaderMesh(STLModell*Tmesh, ShaderModel shadermodle0, vector<vec> vec_nomal, vector<point> vec_point, vector<vec> vec_facenomal);
		static void HideWireFrame(STLModell*Tmesh/*, vector<vec> vec_nomal, vector<point> vec_point*/);
		static void SetMaterialColor(COLORREF clr);
	};
}
#endif
