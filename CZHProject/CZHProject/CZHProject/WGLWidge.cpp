#include "WGLWidge.h"

WGLWidge::WGLWidge()
{
	pslice = new fenceng;
	m_camera = new GCamera;
	pDC = new drawTool;
	//pSimply = new CSimplify;
	pSTL = STLModell::GetInstance();
	//pSTL = new STLModell;
	//Pmeshblock = new MeshBlock;
	pSTL = 0;
	PSimple = 0;
	pslice = 0;
	pMeshZoom = 0;
	Pmblock = 0;
	PmblockTemp = 0;
	nBlock = 0; nShowBdir = 0;
	BkMode = 0;
	//Pmeshblock = 0;
	m_ShaderModel = SMOOTH_SHADER;
	m_board = false;
	fullscreen = false;
	m_IFSimple = false;
	m_slice = false;
	m_Fill = false;
	m_SliceSeqShow = false;
	m_Alltractory = true;

	m_Block = false;
	m_box = false;
	m_cutline = true;
	m_bOptiDir = false;
	m_IfshowDir = false;
	m_Beoptir = false;
	m_SwichBlock = false;
	m_optiSeQ = false; 
	m_Headbox = false;
	m_Dirback = false;
	ceshi = false;
	CF=false;
	NCurrentlayer = 4;

	Nublcok=0;
}
WGLWidge::~WGLWidge()
{
	if (pSTL!=0)
	{
		deleteModel(pSTL);
	}
	
	if (pslice) delete pslice;
	if (pSTL) delete pSTL;

	pslice = NULL;
	pSTL = NULL;
	
	m_bIfShowSTL = false;
	m_IFSimple = false;
	m_slice = false;
}
void WGLWidge::deleteModel(STLModell  *MySTL)
{
	

	/*PHEDGE pHtemp = p.get();

	p.get()->be_pair = 1;
	pHtemp->bStatus = 1;*/

	int	nFct, nFCnt;
	PFACETTRI pFct;


	int	nCnt;
	int nCntTmp;
	nCnt = MySTL->m_vecPEdge.size();
	for (nCntTmp = 0; nCntTmp < nCnt; nCntTmp++)
	{
		delete MySTL->m_vecPEdge[nCntTmp];
	}
	MySTL->m_vecPEdge.clear();
	nCnt = MySTL->m_vecPHEdge.size();
	for (nCntTmp = 0; nCntTmp < nCnt; nCntTmp++)
	{
		delete MySTL->m_vecPHEdge[nCntTmp];
	}
	MySTL->m_vecPHEdge.clear();
	
	nCnt = MySTL->m_vecPFacetTri.size();
	for (nCntTmp = 0; nCntTmp < nCnt; nCntTmp++)
	{
		delete MySTL->m_vecPFacetTri[nCntTmp];
	}
	MySTL->m_vecPFacetTri.clear();
	
	nCnt = MySTL->m_vecPVert.size();
	for (nCntTmp = 0; nCntTmp < nCnt; nCntTmp++)
	{
		delete MySTL->m_vecPVert[nCntTmp];
	}
	MySTL->m_vecPVert.clear();
	
	nCnt = MySTL->m_vecFacetNorm.size();
	for (nCntTmp = 0; nCntTmp < nCnt; nCntTmp++)
	{
		delete MySTL->m_vecFacetNorm[nCntTmp];
	}
	MySTL->m_vecFacetNorm.clear();
}
void WGLWidge::initializeGL()
{
	initializeOpenGLFunctions();
	m_camera->init();
	m_camera->set_view_type(VIEW_SE_ISOMETRIC);
	GLSetupRC();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
////////////����������///////////////////
void WGLWidge::DrawCoord()
{
	BOOL bLighting = IsLighting();     //�رչ���ģʽ
	Lighting(FALSE);
	pDC->SetColor(RGB(0, 0, 0));
	double width, height;  //���������ʾ����Ϊ�Ӿ�����ߵ�20%
	m_camera->get_view_rect(width, height);
	double len = min(width, height);
	len *= 0.1;
	COLORREF old_clr;
	pDC->GetColor(old_clr);
	pDC->SetColor(RGB(100, 10, 200));

	glRasterPos3d(1.4*len, 0, 0);
	pDC->DrawText("X");
	glRasterPos3d(0, 1.4*len, 0);
	pDC->DrawText("Y");
	glRasterPos3d(0, 0, 1.4*len);
	pDC->DrawText("Z");
	pDC->SetColor(old_clr); //�ָ���ͼ��ɫ
	POINT3D cPt, xPt, yPt, zPt;
	xPt.x = len;
	yPt.y = len;
	zPt.z = len;

////////////////////////////////����������/////////////////
	VECTOR3D x1, x2, x3;
	x1 = VECTOR3D(len / 4,0, 0);
	pDC->SetColor(RGB(255, 0, 0));           //X�ᣬ��
	pDC->DrawLine(cPt, xPt);
	pDC->Drawcone(xPt, len/15, x1);

	x2 = VECTOR3D(0, len / 4, 0);
	pDC->SetColor(RGB(0, 255, 0));           //Y�ᣬ��
	pDC->DrawLine(cPt, yPt);
	pDC->Drawcone(yPt, len / 15, x2);

	x3 = VECTOR3D(0, 0,len / 4);
	pDC->SetColor(RGB(0, 0, 255));           //Z�ᣬ��
	pDC->DrawLine(cPt, zPt);
	pDC->Drawcone(zPt, len / 15, x3);
	Lighting(bLighting);            //�ָ�����ģʽ
	pDC->SetColor(old_clr); //�ָ���ͼ��ɫ
}

void WGLWidge::resizeGL(int width, int height)
{
	if (height == 0)height = 1;    //������0��
	if (width == 0)width = 1;
	m_camera->set_screen(width, height);
	return;
}
void WGLWidge::paintGL()
{
	ClearBKground();
	ViewSpace::CBackGround::SetBlackGround(BkMode);
	OnShading();
	m_camera->projection();
	DrawCoord();
	pDC->SetMaterialColor(RGB(75, 75, 75));
	
	
	//////////////////ģ����άʵ����ʾģ��///////////////////
	if (pSTL&&m_bIfShowSTL)
	{
		if (m_box||m_board)
		{
			pSTL->GetBox();
			if (m_box)   pDC->DrawBox(pSTL->box);//���ư�Χ��
			GeneratePlatform(POINT3D((pSTL->ONE.x0 + pSTL->ONE.x1) / 2, (pSTL->ONE.y0 + pSTL->ONE.y1) / 2, pSTL->ONE.z0));//ƽ̨�����ݲ���
		}
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, 3 * pSTL->m_vecPFacetTri.size(), GL_UNSIGNED_INT, 0);
	}
	if (PSimple&&m_IFSimple)//��ʾ��ģ��
	{
		//PSimple->Draw(pDC);
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, 3 * PSimple->m_vecPFacetTri.size(), GL_UNSIGNED_INT, 0);
	}
	if (Pmeshblock.m_Laplacian)//��ʾ������˹���κ�ģ��
	{
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, 3 * pSTL->m_vecPFacetTri.size(), GL_UNSIGNED_INT, 0);
	}
	//////////////////�����ߡ�����ʾģ��/////////////////////
	if (!Pmeshblock.vec_edge.empty())//�߽��˳��������ʾ
	{
		Pmeshblock.showEdge(pDC, Pmeshblock.vec_edge);
	}

	if (m_IFSimple&&!Pmeshblock.pSimply->edgepoint.empty())//��������ʾ
	{
		Pmeshblock.showfeatureEdge(pDC);
	}
	if (PSimple || pSTL&&!m_cutline)//��������ʾ
	{
		pSTL ? (Pmeshblock.pcboundary->showVetex(pDC, pSTL->m_vecPVert))
			: (Pmeshblock.pcboundary->showVetex(pDC, PSimple->m_vecPVert));
	}
    /////////////////////�ӿ鷽���Ż�//////////////////////
	DrawBlockDirResult();

	//////////////////////�ֿ���ʾ����///////////////////
	pDC->DrawPickPoint(mPOINTTemp);//ʰȡ����ʾ
	if (m_cutline)
	{
		for (int i = 0; i < path.size(); i++)
		{
			Pmeshblock.Render(pDC, path[i]);//�ָ�����ʾ
		}
	}
	if (CF)
	{
		//Pmeshblock.DrawPoint(pDC, CFpoint);
		Pmeshblock.DrawFeapoint(pDC, FeaPointAll);
	}
	if (ceshi)
	{
		pDC->DrawHeadBox(vec_Ceshi0, RGB(75, 75, 75));
		pDC->DrawHeadBox(vec_Ceshi1,RGB(75, 75, 75));
	}
	if (Rbox.size() != 0)//�ָ����ļ���ʾ
	{
		if (m_Headbox)
		{
			pDC->DrawHeadBox(vec_PlanBoard, RGB(75, 75, 75));
			pDC->DrawHeadBox(vec_HeadBox, RGB(238, 199, 16));//���ƴ�ӡͷ��Χ��
		}
		if (m_Block || Sblock)
		{
			BOX3D Mainbox;
			pSTL->GetMainBlockBox(Rbox[0].OneBlock,Mainbox);
			GeneratePlatform(POINT3D((Mainbox.x0 + Mainbox.x1) / 2, (Mainbox.y0 + Mainbox.y1) / 2, Mainbox.z0));//ƽ̨�����ݲ���
			
			Pmeshblock.Drawblock(pDC, Rbox);
			m_bIfShowSTL = false;
		}
		if (m_SwichBlock)
		{
			Pmeshblock.DrawSwichBlock(pDC, nBlock, Rbox);
			double width, height;
			m_camera->get_view_rect(width, height);
			double len = min(width, height);
			COptDir::DrawOptiDir(pDC, All_VecDir[nBlock], pSTL->ONE, len);//�������ų��ͷ���
		}
	}
	if (BlockEdge.size() != 0)//������߽���ʾ
	{
		pslice->Draw(pDC, BlockEdge);
	}

	/////////////////////��ӹ�˳���Ż�//////////////////////
	if (m_optiSeQ)
	{
		double width, height;  //���������ʾ����Ϊ�Ӿ�����ߵ�20%
		m_camera->get_view_rect(width, height);
		double len = min(width, height);
		len *= 0.1;
		
		COptisequence PseQ;
		PseQ.DrawResult(Rbox, All_VecDir, pDC, len);
	}
	/////////////////////��Ƭ�������ʾ///////////////////
	if (m_Alltractory)
	{
		DrawSliceResult();
		DrawFillResult();
	}
	//�ָ���켣λ�˷���
	if (ToolpathFill.size() != 0 || SimALLBlock.size() != 0)
	{
		m_Alltractory = false;
		if (ToolpathFill.size() != 0)
		{
			for (int i = 0; i < ToolpathFill.size(); i++)
			{
				COLORREF Newcolor;
				Newcolor = RGB((47 * (i + 1)) % 255, (183 * i) % 255, (197 * i) % 255);
				pslice->DrawFill(pDC, Newcolor, ToolpathFill[i]);//
			}
		}
		else
		{
			for (int i = 0; i < SimALLBlock.size(); i++)
			{
				COLORREF Newcolor;
				Newcolor = RGB((47 * (i + 1)) % 255, (183 * i) % 255, (197 * i) % 255);
				Pmeshblock.Drawblock(pDC, Newcolor, SimALLBlock[i]);//
			}
		}
		
		dlg.FindTheLow(BlockFill[0], PMainlow);
		GeneratePlatform(PMainlow);//ƽ̨�����ݲ���
	}
	if (m_board&&vec_Plat.size() != 0)  Pmeshblock.DrawPlat(pDC, vec_Plat, p_Row);//����ƽ̨
	if (!m_board&&vec_PlatRotate.size() != 0) Pmeshblock.DrawPlat(pDC, vec_PlatRotate, p_RowRotate);//����ƽ̨
	DrawSeqLayer();
}

void WGLWidge::DrawBlockDirResult()
{
	if (m_bOptiDir)
	{
		VECTOR3D  m_VecDirTemp;
		if (Rbox.size() != 0)//���ӿ鷽���Ż�
		{
			if (m_Beoptir)//�Ƿ����ڶԸ�������Ż�
			{
				COptDir::DrawResult(Rbox[nBlock].OneBlock, m_vecFacetNum, pDC);
				m_VecDirTemp = m_VecDir;
			}
			else
			{
				if (m_IfshowDir)
				{
					COptDir::DrawResult(Rbox[nShowBdir].OneBlock, All_vecFacetNum[nShowBdir], pDC);
				}
				else
				{
					for (int i = 0; i < All_vecFacetNum.size(); i++)
					{
						COptDir::DrawResult(Rbox[i].OneBlock, All_vecFacetNum[i], pDC);
					}
				}
				m_VecDirTemp = All_VecDir[nShowBdir];
			}
		}
		else//ȫ�ַ����Ż�
		{
			m_VecDirTemp = m_VecDir;
			COptDir::DrawResult(pSTL, m_vecFacetNum, pDC);
		}
		double width, height;
		m_camera->get_view_rect(width, height);
		double len = min(width, height);
		COptDir::DrawOptiDir(pDC, m_VecDirTemp, pSTL->ONE, len);//�������ų��ͷ���
		m_bIfShowSTL = false;
	}
}
void WGLWidge::DrawSliceResult()
{
	if (!m_slice) return;
	if (Blocklunkuo.size() != 0)
	{
		if (m_SwichBlock)
		{
			pslice->Draw(pDC, Blocklunkuo[nBlock]);
		}
		else
		{
			for (int i = 0; i < Blocklunkuo.size(); i++)
			{
				pslice->Draw(pDC, Blocklunkuo[i]);
				
			}
		}
	}
	else
	{
		if (lunkuo.size() != 0)
		{
			pslice->Draw(pDC, lunkuo);
		}
	}
	m_bOptiDir = false;
}
void WGLWidge::DrawFillResult()
{
	if (m_Fill)//���켣��ʾ
	{
		if (Fill.size() != 0)
		{
			pslice->Draw(pDC, Fill);
		}
		else
		{
			if (BlockFill.size() != 0)
			{
				if (m_SwichBlock)
				{
					pslice->DrawFill(pDC, BlockFill[nBlock]);
				}
				else
				{
					for (int i = 0; i < BlockFill.size(); i++)
					{
						pslice->DrawFill(pDC, BlockFill[i]);
					}
				}
			}
		}
	}
	else
	{
		if (Fill.size() != 0 || BlockFill.size() != 0)//����һ�����켣
		{
			if (Fill.size() != 0)
			{
				if (NCurrentlayer < Fill.size() - 1)
				{
					//pslice->DrawThatLayerFill(pDC, NCurrentlayer, Fill);
					pslice->DrawOneLayerFill(pDC, Fill[NCurrentlayer]);
					pslice->Draw(pDC, lunkuo, NCurrentlayer);
				}
				else
				{
					pslice->DrawFill(pDC, Fill);
				}
			}
			else
			{
				if (m_SwichBlock)
				{
					if (NCurrentlayer < BlockFill[nBlock].size() - 1)
					{
						//pslice->DrawThatLayerFill(pDC, NCurrentlayer, BlockFill[nBlock]);
						pslice->DrawOneLayerFill(pDC, BlockFill[nBlock][NCurrentlayer]);
						pslice->Draw(pDC, Blocklunkuo[nBlock], NCurrentlayer);
					}
					else
					{
						pslice->DrawFill(pDC, BlockFill[nBlock]);
					}
				}
				else
				{
					for (int i = 0; i < BlockFill.size(); i++)
					{
						if (NCurrentlayer < BlockFill[i].size() - 1)
						{
							//pslice->DrawThatLayerFill(pDC, NCurrentlayer, BlockFill[i]);
							pslice->DrawOneLayerFill(pDC, BlockFill[i][NCurrentlayer]);
							pslice->Draw(pDC, Blocklunkuo[i], NCurrentlayer);
						}
						else
						{
							pslice->DrawFill(pDC, BlockFill[i]);
						}
					}
				}
				m_Block = false; Sblock = false; m_bIfShowSTL = false;
			}
		}
		else
		{
			//��Ƭ����ʾ��
			if (Blocklunkuo.size() != 0)
			{
				if (m_SwichBlock)
				{
					if (NCurrentlayer < Blocklunkuo[nBlock].size() - 1)
					{
						pslice->DrawThatLayerFill(pDC, NCurrentlayer, Blocklunkuo[nBlock]);
					}
					else
					{
						pslice->DrawFill(pDC,Blocklunkuo[nBlock]);//
					}
				}
				else
				{
					for (int i = 0; i < Blocklunkuo.size(); i++)
					{
						if (NCurrentlayer < Blocklunkuo[i].size() - 1)
						{
							pslice->DrawThatLayerFill(pDC, NCurrentlayer, Blocklunkuo[i]);
							//pslice->DrawOneLayerFill(pDC, BlockFill[i][NCurrentlayer]);
						}
						else
						{
							pslice->DrawFill(pDC, Blocklunkuo[i]);//
						}
					}
				}
				m_Block = false; Sblock = false; m_bIfShowSTL = false;

			}
			else
			{
				if (lunkuo.size() != 0)
				{
					if (NCurrentlayer < lunkuo.size() - 1)
					{
						pslice->DrawThatLayerFill(pDC, NCurrentlayer, lunkuo);
						///pslice->DrawOneLayerFill(pDC, lunkuo[NCurrentlayer]);
					}
					m_bIfShowSTL = false;
				}
			}
		}
	}
}
void WGLWidge::DrawSeqLayer()
{
	if (!m_SliceSeqShow) return;
	if (Blocklunkuo.size() == 0) return;

	if (BlockFill.size() != 0)
	{
		if (NCurrentlayer<SeqFill.size())
		{
			pslice->DrawOneLayerFill(pDC, SeqFill[NCurrentlayer]);
			pslice->Draw(pDC, SeqlunkuoLayer, NCurrentlayer);
		}
		else
		{
			pslice->DrawFill(pDC, SeqFill);
		}
	}
	else
	{
		if (NCurrentlayer<SeqlunkuoLayer.size())
		{
			pslice->Draw(pDC, SeqlunkuoLayer, NCurrentlayer);
		}
		else
		{
			pslice->Draw(pDC, SeqlunkuoLayer);
		}
	}
}
/////////////����OPENGL��Ļ�������////////////////////////////

void WGLWidge::GLSetupRC()
{
	m_bShading = TRUE;           //ʹ����ɫģʽ
	CreatLight();
	glEnable(GL_DEPTH_TEST);     //ʹ����Ӱ
	//glEnable(GL_CULL_FACE);      //����������ڲ�
	glFrontFace(GL_CCW);          //����Ƭ������ʱ�뷽��CCW����ת��ʾģ�͵������
	////���ù�Դ
	//GLfloat lightAmbient[] = { 0.75f, 0.75f, 0.75f, 1.0f }; //���û��������ɫ���
	//GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };    //�������
	////GLfloat  specular[] = {1.0f,1.0f,1.0f,1.0f};     //�����
	////GLfloat  lightPos[] = {1.0f,1.0f,1.0f,0.0f};     //��Դλ�ã���ʸ����1,1,1����������Զ��

	//glEnable(GL_LIGHTING);                           //ʹ�ù���ģʽ
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);    //Ϊ��Դ0���û�����
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);    //Ϊ��Դ0�����������
	////glLightfv(GL_LIGHT0,GL_SPECULAR,specular);       //Ϊ��Դ0���þ����
	////glLightfv(GL_LIGHT0,GL_POSITION,lightPos);       //���ù�Դ0λ��
	//SetLightDirection(1, 1, 1);                        //���ù�Դ�ķ���
	//glEnable(GL_LIGHT0);                             //�򿪹�Դ0

	//����Ĭ�ϵ���ɫ����
	SetBkColor(RGB(0, 0, 0));            //���ñ�����Ĭ����ɫ����ɫ��
	pDC->SetMaterialColor(RGB(75, 75, 75)); //���ò��ϵ�Ĭ����ɫ(����ɫ)
	//pDC->SetMaterialColor(RGB(225, 175, 22)); //���ò��ϵ�Ĭ����ɫ
	pDC->SetBkMaterialColor(RGB(128, 128, 128));   //ģ�ͱ���
	pDC->SetColor(RGB(255, 255, 255));        //���ÿ����ʾ��Ĭ����ɫ����ɫ��
	SetHighlightColor(RGB(255, 0, 0));   //���ø�������ʾ����ɫ����ɫ��

	glPointSize(3.0);                 //���õ�Ļ��Ƴߴ�
}

/////////////////////////���պͲ��ϵ�����//////////////////////
void WGLWidge::ClearBKground()                                 //����ˢ��
{
	GLclampf r, g, b;
	//��ȡ����ɫ����m_clrBK����ɫRGB����
	r = (GLclampf)GetRValue(m_clrBk) / 255.0;
	g = (GLclampf)GetGValue(m_clrBk) / 255.0;
	b = (GLclampf)GetBValue(m_clrBk) / 255.0;

	glClearColor(1, 1, 1, 0);//���ñ���ɫΪ��ɫ
	//glClearColor(r, g, b, 0.0f);      //����������RGBA��ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ɫ��������Ȼ���
}

void WGLWidge::OnShading()                                     //����ģʽ�趨
{
	if (m_bShading)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}
void WGLWidge::Shading(BOOL bShading)
{
	m_bShading = bShading;
}
BOOL WGLWidge::IsShading()
{
	return m_bShading;
}

void WGLWidge::Lighting(BOOL bLighting)                        //���տ���
{
	if (bLighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}
BOOL WGLWidge::IsLighting()
{
	GLboolean bLighting;
	glGetBooleanv(GL_LIGHTING, &bLighting);
	return bLighting;
}
void WGLWidge::CreatLight()
{
	//bright white light - full intensity RGB values
	GLfloat lightAmbient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat lightDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	//////////////////////////////////////////////////////////////////////////
	glShadeModel(GL_SMOOTH);  //�������
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_CCW);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//�������
	glEnable(GL_BLEND);//�������

	GLfloat fGloablAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	GLfloat m_lightAmb0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat m_lightDif0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat m_lightSpe0[] = { 0.3f, 0.3f, 0.3f, 0.5f };
	//GLfloat m_lightPos0[]={1.0f,1.0f,1.0f,0.0f};

	GLfloat m_lightAmb1[] = { 0.1f, 0.1f, 0.1f, 0.5f };
	GLfloat m_lightDif1[] = { 0.3f, 0.3f, 0.3f, 0.5f };
	GLfloat m_lightSpe1[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat m_lightPos1[]={-0.3f,0.0f,1.0f,0.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDif0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpe0);
	//glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos0);
	SetLightDirection(1.0, 1.0, 0.5);

	glLightfv(GL_LIGHT1, GL_AMBIENT, m_lightAmb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_lightDif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, m_lightSpe1);
	//glLightfv(GL_LIGHT1, GL_POSITION, m_lightPos1);
	SetLightDirection(-0.3f, 0.5f, 0.2f);

	//ȫ�ֻ��������ã�����������
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fGloablAmbient);/////
	GLfloat local_view[] =
	{ 0.0 };
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	//˫����գ���Ҫ��ʾ����)
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);/////

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}
void WGLWidge::SetLightDirection(float dx, float dy, float dz) //���ù�Դ����
{
	m_vecLight[0] = dx;
	m_vecLight[1] = dy;
	m_vecLight[2] = dz;
	GLfloat lightPos[] = { dx, dy, dz, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}
void WGLWidge::GetLightDirection(float& dx, float& dy, float& dz)
{
	dx = m_vecLight[0];
	dy = m_vecLight[1];
	dz = m_vecLight[2];
}


void WGLWidge::SetBkColor(COLORREF clr)                  //���ñ�����ɫ
{
	m_clrBk = clr;
}
void WGLWidge::GetBkColor(COLORREF& clr)
{
	clr = m_clrBk;
}
void WGLWidge::SetHighlightColor(COLORREF clr)         //���ø�������ɫ
{
	m_clrHighlight = clr;
}
void WGLWidge::GetHighlightColor(COLORREF& clr)
{
	clr = m_clrHighlight;
}
void WGLWidge::Highlight(BOOL bHighlight)
{
	BYTE r, g, b;
	if (bHighlight)
	{
		r = GetRValue(m_clrHighlight);
		g = GetGValue(m_clrHighlight);
		b = GetBValue(m_clrHighlight);
	}
	else
	{
		r = GetRValue(m_clrMaterial);
		g = GetGValue(m_clrMaterial);
		b = GetBValue(m_clrMaterial);
	}
	GLfloat mat_amb_diff[] = { (GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);

}

// ���ų���,������1Ϊ��С��С��1Ϊ�Ŵ�
void WGLWidge::Zoom(double dScale)
{
	m_camera->zoom(dScale);
	update();                 //ˢ����ͼ
}

// ����һ�����ʵ����űȣ��Խ�ģ��ȫ����ʾ�ڳ�����
void WGLWidge::ZoomAll(BOX3D box)
{
	m_camera->zoom_all(box.x0, box.y0, box.z0, box.x1, box.y1, box.z1);
	update();
}

// ʹ�õ����ӽ����۲�ģ��
void WGLWidge::OnViewType(UINT type)
{
	Q_ASSERT(type >= VIEW_FRONT&&type <= VIEW_NW_ISOMETRIC);
	m_camera->set_view_type(type);
	update();
}
// ����ǰ�����ߴ�İٷֱ��ƶ�����������dpx��dpy�ķ�Χ��0~1
void WGLWidge::MoveView(double dpx, double dpy)
{
	m_camera->move_view(dpx, dpy);
	update();
}
void WGLWidge::RotateView(double drot, short snXyz)
{
	m_camera->rotate_view(drot, snXyz);
	updateGL();
}
POINT3D WGLWidge::BeginSelection(int xPos, int yPos)
{
	POINT3D P;
	m_bSelectionMode = TRUE;
	//wglMakeCurrent(m_hDC, m_hRC);
	GLint viewport[4];
	glSelectBuffer(BUFFER_LENGTH, m_selectBuff);
	P = m_camera->selection(xPos, yPos);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return P;
	//InitNames();
}
int WGLWidge::EndSelection(UINT* items)
{
	m_bSelectionMode = FALSE;
	int hits = glRenderMode(GL_RENDER);
	for (int i = 0; i < hits; i++)
	{
		items[i] = m_selectBuff[i * 4 + 3];
	}
	//wglMakeCurrent(m_hDC, NULL);
	return hits;
}
void WGLWidge::initVBO(STLModell  * pSTLTemp)
{
	int VertexNum = pSTLTemp->m_vecPVert.size();
	float *positionData = new float[3 * VertexNum];
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	int theVertex = 0;

	for (int nVer = 0; nVer < pSTLTemp->m_vecPVert.size(); nVer++)
	{

		positionData[theVertex + nVer * 3 + 0] = pSTLTemp->m_vecPVert[nVer]->x;
		positionData[theVertex + nVer * 3 + 1] = pSTLTemp->m_vecPVert[nVer]->y;
		positionData[theVertex + nVer * 3 + 2] = pSTLTemp->m_vecPVert[nVer]->z;
	}
	//�󶨶������ݵ�����������
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * VertexNum * sizeof(float), positionData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);//�������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
	//delete positionData;

	/////������ʸ����
	float *nomralData = new float[3 * VertexNum];
	theVertex = 0;

	for (int nVer = 0; nVer < pSTLTemp->m_vecPVert.size(); nVer++)
	{
		pSTLTemp->m_vecPVert[nVer]->VertexNormal = KitTool::CalcuVerNormal(pSTLTemp->m_vecPVert[nVer]);
		nomralData[theVertex + nVer * 3 + 0] = pSTLTemp->m_vecPVert[nVer]->VertexNormal.dx;
		nomralData[theVertex + nVer * 3 + 1] = pSTLTemp->m_vecPVert[nVer]->VertexNormal.dy;
		nomralData[theVertex + nVer * 3 + 2] = pSTLTemp->m_vecPVert[nVer]->VertexNormal.dz;
	}
	glGenBuffers(1, &m_NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * VertexNum * sizeof(float), nomralData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);//��ʸ
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);//��ʸ
	delete nomralData;

	/////������������
	int meshNum = pSTLTemp->m_vecPFacetTri.size();
	int *triIndex;
	triIndex = new int[3 * meshNum];
	for (int nmesh = 0; nmesh < pSTLTemp->m_vecPFacetTri.size(); nmesh++)
	{
		triIndex[nmesh * 3 + 0] = pSTLTemp->m_vecPFacetTri[nmesh]->m_PVerts[0]->VertexID;
		triIndex[nmesh * 3 + 1] = pSTLTemp->m_vecPFacetTri[nmesh]->m_PVerts[1]->VertexID;
		triIndex[nmesh * 3 + 2] = pSTLTemp->m_vecPFacetTri[nmesh]->m_PVerts[2]->VertexID;
	}
	///���������鴫�ݵ��Դ�
	glEnableVertexAttribArray(2);
	glGenBuffers(1, &m_IDBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * meshNum * sizeof(int), triIndex, GL_STATIC_DRAW);
	////ɾ��������������ڴ�
	delete triIndex;
}
void WGLWidge::deleteVBO()
{
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_NormalBuffer);
}
void WGLWidge::GeneratePlatform(POINT3D pr0)
{
	if (vec_Plat.size() > 0) vec_Plat.clear();
	if (p_Row.size() > 0) p_Row.clear();
	for (int i = -5; i < 5;i++)
	{
		vec_POINT3D p_cross;
		for (int j = -5; j < 5;j++)
		{
			POINT3D p0;
			p0.x = pr0.x+i * 8;
			p0.y = pr0.y +j* 8;
			p0.z = pr0.z;
			p_cross.push_back(p0);
		}
		p_Row.push_back(p_cross);
	}
	bool RightDir = false;
	vec_POINT3D vec_Face; VECTOR3D DirZ = VECTOR3D(0, 0, 1);
	for (int i = 0; i < p_Row.size()-1;i++)
	{
		int nct = i + 1;
		for (int j = 0; j < p_Row[i].size() - 1; j++)
		{
			POINT3D p0,p1,p2;
			int nrt = j + 1; vec_Face.clear();
			p0 = p_Row[i][j];
			p1 = p_Row[nct][j];
			p2 = p_Row[nct][nrt];
			RightDir = KitTool::JudgeFaceDir(p0, p1, p2, DirZ);
			if (RightDir)
			{
				vec_Face.push_back(p0); vec_Face.push_back(p1); vec_Face.push_back(p2);
			}
			else
			{
				vec_Face.push_back(p1); vec_Face.push_back(p0); vec_Face.push_back(p2);
			}
			vec_Plat.push_back(vec_Face);

			vec_Face.clear();
			p0 = p_Row[i][j];
			p1 = p_Row[i][nrt];
			p2 = p_Row[nct][nrt];
			RightDir = KitTool::JudgeFaceDir(p0, p1, p2, DirZ);
			if (RightDir)
			{
				vec_Face.push_back(p0); vec_Face.push_back(p1); vec_Face.push_back(p2);
			}
			else
			{
				vec_Face.push_back(p1); vec_Face.push_back(p0); vec_Face.push_back(p2);
			}
			vec_Plat.push_back(vec_Face);
		}
	}
}
void WGLWidge::RotateHeadBox(vector<vec_POINT3D> &vec_face, VECTOR3D curr_Dir, VECTOR3D tager_Dir)
{

	double theta = _AngleBetween3D(curr_Dir, tager_Dir);
	VECTOR3D uAxis = curr_Dir * tager_Dir;
	uAxis.Normalize();
	MATRIX3D TM = TM.CreateRotateMatrix(theta, uAxis);
	for (int i = 0; i < vec_face.size(); i++)
	{
		vec_POINT3D poly;
		poly = vec_face[i];
		for (int j = 0; j < poly.size(); j++)
		{
			POINT3D Temp;
			Temp.x = poly[j].x;
			Temp.y = poly[j].y;
			Temp.z = poly[j].z;
			Temp = Temp*TM;
			poly[j].x = Temp.x;
			poly[j].y = Temp.y;
			poly[j].z = Temp.z;
		}
		vec_face[i] = poly;
	}
}
POINT3D WGLWidge::CalCenterPoint(MyBlock CurrnetBlock, VECTOR3D DirV)
{
	VECTOR3D DirZ = VECTOR3D(0, 0, 1);
	//DirV.dx = All_VecDir[2].dx; DirV.dy = -All_VecDir[2].dy; DirV.dz = -All_VecDir[2].dz;
	vector<vec_POINT3D> vec_face;
	for (int i = 0; i < CurrnetBlock.OneBlock.size(); i++)
	{
		vec_POINT3D Oneface; POINT3D p00;
		for (int j = 0; j < 3; j++)
		{
			p00.x = CurrnetBlock.OneBlock[i]->m_PVerts[j]->x;
			p00.y = CurrnetBlock.OneBlock[i]->m_PVerts[j]->y;
			p00.z = CurrnetBlock.OneBlock[i]->m_PVerts[j]->z;
			Oneface.push_back(p00);
		}
		vec_face.push_back(Oneface);
	}
	RotateHeadBox(vec_face, DirV, DirZ);
	double x0, y0, z0, x1, y1, z1;
	x0 = x1 = vec_face[1][0].x;
	y0 = y1 = vec_face[1][0].y;
	z0 = z1 = vec_face[1][0].z;

	for (int i = 0; i < vec_face.size(); i++)
	{
		for (int n = 0; n < 3; n++)
		{
			if (vec_face[i][n].x < x0)
				x0 = vec_face[i][n].x;
			if (vec_face[i][n].x > x1)
				x1 = vec_face[i][n].x;
			if (vec_face[i][n].y < y0)
				y0 = vec_face[i][n].y;
			if (vec_face[i][n].y > y1)
				y1 = vec_face[i][n].y;
			if (vec_face[i][n].z < z0)
				z0 = vec_face[i][n].z;
			if (vec_face[i][n].z > z1)
				z1 = vec_face[i][n].z;
		}
	}
	POINT3D Cenpoint;
	Cenpoint.x = (x0 + x1) / 2; Cenpoint.y = (y0 + y1) / 2; Cenpoint.z = z0;
	return Cenpoint;
}
void WGLWidge::CreatBoxcir(POINT3D Pcenter, VECTOR3D DirV)
{
	POINT3D p0, p1, p2, p3, p00, p01, p02, p03;
	POINT3D p000, p001, p002, p003;
	p000 = POINT3D(Pcenter.x - 2, Pcenter.y - 2, Pcenter.z); p001 = POINT3D(Pcenter.x - 2, Pcenter.y + 2, Pcenter.z);
	p002 = POINT3D(Pcenter.x + 2, Pcenter.y - 2, Pcenter.z); p003 = POINT3D(Pcenter.x + 2, Pcenter.y + 2, Pcenter.z);


	p0 = POINT3D(Pcenter.x - 10, Pcenter.y - 10, Pcenter.z+8); p1 = POINT3D(Pcenter.x - 10, Pcenter.y + 10, Pcenter.z+8);
	p2 = POINT3D(Pcenter.x + 10, Pcenter.y - 10, Pcenter.z+8); p3 = POINT3D(Pcenter.x + 10, Pcenter.y + 10, Pcenter.z+8);
	p00 = POINT3D(Pcenter.x - 10, Pcenter.y - 10, Pcenter.z + 78); p01 = POINT3D(Pcenter.x - 10, Pcenter.y + 10, Pcenter.z + 78);
	p02 = POINT3D(Pcenter.x + 10, Pcenter.y - 10, Pcenter.z + 78); p03 = POINT3D(Pcenter.x + 10, Pcenter.y + 10, Pcenter.z + 78);
	////////////////////����ĳ�����/////////////////////////
	//�µ���---��ȥ���±�//
	vec_POINT3D pface; VECTOR3D v_Normal; POINT3D OneNormal;
	
	//�ϵ���//
	VECTOR3D DirZ = VECTOR3D(0, 0, 1);
	DirZ.dx = 0; DirZ.dy = 0; DirZ.dz = 1;

	if (KitTool::JudgeFaceDir(p00, p01, p02, DirZ))
	{
		pface.push_back(p00); pface.push_back(p01); pface.push_back(p02);
	}
	else
	{
		pface.push_back(p01); pface.push_back(p00); pface.push_back(p02);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p01, p03, p02, DirZ))
	{
		pface.push_back(p01); pface.push_back(p03); pface.push_back(p02);
	}
	else
	{
		pface.push_back(p03); pface.push_back(p01); pface.push_back(p02);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//�����//
	DirZ.dx = 0; DirZ.dy = -1; DirZ.dz = 0;

	if (KitTool::JudgeFaceDir(p00, p0, p2, DirZ))
	{
		pface.push_back(p00); pface.push_back(p0); pface.push_back(p2);
	}
	else
	{
		pface.push_back(p0); pface.push_back(p00); pface.push_back(p2);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p00, p2, p02, DirZ))
	{
		pface.push_back(p00); pface.push_back(p2); pface.push_back(p02);
	}
	else
	{
		pface.push_back(p2); pface.push_back(p00); pface.push_back(p02);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//�Ҳ���//
	DirZ.dx = 0; DirZ.dy = 1; DirZ.dz = 0;

	if (KitTool::JudgeFaceDir(p01, p1, p3, DirZ))
	{
		pface.push_back(p01); pface.push_back(p1); pface.push_back(p3);
	}
	else
	{
		pface.push_back(p1); pface.push_back(p01); pface.push_back(p3);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p01, p3, p03, DirZ))
	{
		pface.push_back(p01); pface.push_back(p3); pface.push_back(p03);
	}
	else
	{
		pface.push_back(p3); pface.push_back(p01); pface.push_back(p03);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//ǰ����//
	DirZ.dx = 1; DirZ.dy = 0; DirZ.dz = 0;

	if (KitTool::JudgeFaceDir(p02, p2, p3, DirZ))
	{
		pface.push_back(p02); pface.push_back(p2); pface.push_back(p3);
	}
	else
	{
		pface.push_back(p2); pface.push_back(p02); pface.push_back(p3);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p02, p3, p03, DirZ))
	{
		pface.push_back(p02); pface.push_back(p3); pface.push_back(p03);
	}
	else
	{
		pface.push_back(p3); pface.push_back(p02); pface.push_back(p03);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//�����//
	DirZ.dx = -1; DirZ.dy = 0; DirZ.dz = 0;

	if (KitTool::JudgeFaceDir(p00, p0, p1, DirZ))
	{
		pface.push_back(p00); pface.push_back(p0); pface.push_back(p1);
	}
	else
	{
		pface.push_back(p0); pface.push_back(p00); pface.push_back(p1);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p00, p1, p01, DirZ))
	{
		pface.push_back(p00); pface.push_back(p1); pface.push_back(p01);
	}
	else
	{
		pface.push_back(p1); pface.push_back(p00); pface.push_back(p01);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	////////////////////�����������/////////////////////////
	//�µ���//
	DirZ = VECTOR3D(0, 0, -1);

	if (KitTool::JudgeFaceDir(p000, p001, p002, DirZ))
	{
		pface.push_back(p000); pface.push_back(p001); pface.push_back(p002);
	}
	else
	{
		pface.push_back(p001); pface.push_back(p000); pface.push_back(p002);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p001, p003, p002, DirZ))
	{
		pface.push_back(p001); pface.push_back(p003); pface.push_back(p002);
	}
	else
	{
		pface.push_back(p003); pface.push_back(p001); pface.push_back(p002);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//ǰ����//
	VECTOR3D R1 = p003 - p002; VECTOR3D R2 = p3 - p003;
	DirZ = R1*R2;
	if (KitTool::JudgeFaceDir(p002, p003, p2, DirZ))
	{
		pface.push_back(p002); pface.push_back(p003); pface.push_back(p2);
	}
	else
	{
		pface.push_back(p003); pface.push_back(p002); pface.push_back(p2); 
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p003, p3, p2, DirZ))
	{
		pface.push_back(p003); pface.push_back(p3); pface.push_back(p2);
	}
	else
	{
		pface.push_back(p3); pface.push_back(p3); pface.push_back(p2);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//�����//
	 R1 = p000 - p001;  R2 = p0 - p000;
	DirZ = R1*R2;
	if (KitTool::JudgeFaceDir(p001, p000, p1, DirZ))
	{
		pface.push_back(p001); pface.push_back(p000); pface.push_back(p1);
	}
	else
	{
		pface.push_back(p000); pface.push_back(p001); pface.push_back(p1);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	if (KitTool::JudgeFaceDir(p000, p0, p1, DirZ))
	{
		pface.push_back(p000); pface.push_back(p0); pface.push_back(p1);
	}
	else
	{
		pface.push_back(p0); pface.push_back(p000); pface.push_back(p1);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	//�����//
	 R1 = p002 - p000; R2 = p2 - p002;
	DirZ = R1*R2;
	if (KitTool::JudgeFaceDir(p0, p000, p002, DirZ))
	{
		pface.push_back(p0); pface.push_back(p000); pface.push_back(p002);
	}
	else
	{
		pface.push_back(p000); pface.push_back(p0); pface.push_back(p002);
	}
	vec_HeadBox.push_back(pface); pface.clear();


	if (KitTool::JudgeFaceDir(p002, p2, p0, DirZ))
	{
		pface.push_back(p002); pface.push_back(p2); pface.push_back(p0);
	}
	else
	{
		pface.push_back(p2); pface.push_back(p002); pface.push_back(p0);
	}
	vec_HeadBox.push_back(pface); pface.clear();

	//�Ҳ���//
	R1 = p001 - p003; R2 = p1 - p002;
	DirZ = R1*R2;
	if (KitTool::JudgeFaceDir(p003, p001, p3, DirZ))
	{
		pface.push_back(p003); pface.push_back(p001); pface.push_back(p3);
	}
	else
	{
		pface.push_back(p001); pface.push_back(p003);  pface.push_back(p3);
	}
	vec_HeadBox.push_back(pface); pface.clear();


	if (KitTool::JudgeFaceDir(p3, p001, p1, DirZ))
	{
		pface.push_back(p3); pface.push_back(p001); pface.push_back(p1);
	}
	else
	{
		pface.push_back(p001); pface.push_back(p3); pface.push_back(p1);
	}
	vec_HeadBox.push_back(pface); pface.clear();
	DirZ.dx = 0; DirZ.dy = 0; DirZ.dz = 1;
	RotateHeadBox(vec_HeadBox, DirZ, DirV);
	//������ʸ��
	for (int i = 0; i < vec_HeadBox.size(); i++)
	{
		p0 = vec_HeadBox[i][0]; p1 = vec_HeadBox[i][1]; p2 = vec_HeadBox[i][2];
		v_Normal = KitTool::CalcuPfacNormal(p0, p1, p2);
		OneNormal.x = v_Normal.dx; OneNormal.y = v_Normal.dy; OneNormal.z = v_Normal.dz;
		pface.clear(); pface.push_back(OneNormal); pface.push_back(p0); pface.push_back(p1); pface.push_back(p2);
		vec_HeadBox[i] = pface;
	}
}