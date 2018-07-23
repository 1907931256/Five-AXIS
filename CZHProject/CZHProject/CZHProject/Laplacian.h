#include "STLModell.h"
#include"KitTool.h"
#include <Eigen/Sparse>
typedef Eigen::SparseMatrix<double> SpMat;//typedef�ض���
typedef Eigen::Triplet<double> T;

class CLaplacian
{
public:
	void change(vec_PVERT& m_vecLpvert,STLModell* &pCSTLModel,vector<POINT3D>& m_vecLp,vec_VECTOR3D& m_vecV);
	void back(vec_PVERT& m_vecLpvert, STLModell* &pCSTLModel, vector<POINT3D>& m_vecLp, vec_VECTOR3D& m_vecV);
	void selectP(STLModell* &pCSTLModel, vector<int>& m_vecSL);//ѡ����ƶ���
protected:
private:
};