#ifndef  CBackGround_H_
#define  CBackGround_H_
#include <glut.h>
#include <glaux.h>
#pragma once

namespace ViewSpace
{
	enum BackGroundColor
	{
		//CHANGE_White;//��ɫ����
		CHANGE_GRAY,//��ɫ����
		CHANGE_DEONGAREE,//��������
		CHANGE_LIGHT_BLUE//ǳ������

	};  
class CBackGround
{
public:
	static void SetBlackGround(int Modeway);
	static void RenderBackGround(BackGroundColor backgroundcolor=CHANGE_GRAY);
	
};

}
#endif
