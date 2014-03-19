#include "TranslateMngr.h"
#include <math.h>


#define PI 3.1415926535898


TranslateMngr::TranslateMngr()
{
	for (int iAxis=0; iAxis<3; iAxis++)
	{
		m_aMnAtAxis[iAxis]=0.0;
		m_aRnAtAxis[iAxis]=0.0;
	}
}


TranslateMngr::~TranslateMngr()
{
}


void TranslateMngr::SetMnThrst(double fMnThrst)
{
	m_fMnThrst=fMnThrst;
}


void TranslateMngr::SetRnAngle(double fRnAngle)
{
	m_fRnAngle=fRnAngle;
}


void TranslateMngr::SetMnDecrease(double fMnDecrease)
{
	m_fMnDecrease=fMnDecrease;
}


void TranslateMngr::SetRnDecrease(double fRnDecrease)
{
	m_fRnDecrease=fRnDecrease;
}


void TranslateMngr::Move(AXIS eAxis,DIRECTION eDirection)
{
	m_aMnAtAxis[eAxis]-=m_fMnThrst*eDirection;
}


void TranslateMngr::Turn(AXIS eAxis,DIRECTION eDirection)
{
	m_aRnAtAxis[eAxis]-=m_fRnAngle*eDirection;
}


void TranslateMngr::Process(List<Polyhedron*>* pPolyhedronList)
{
	double aMnVector[3]={0,0,0};
	double aRnMatrix[3][3]={{1,0,0},{0,1,0},{0,0,1}};

	CalculateMnVector(aMnVector);
	CalculateRnMatrix(aRnMatrix);

	for (int i=0; i<pPolyhedronList->Size(); i++)
	{
		Polyhedron* pPolyhedron=pPolyhedronList->Get(i);
		pPolyhedron->Move(aMnVector);
		pPolyhedron->Turn(aRnMatrix);
		pPolyhedron->ProjectPoints();
	}

	for (int iAxis=0; iAxis<3; iAxis++)
	{
		m_aMnAtAxis[iAxis]*=1.0-m_fMnDecrease;
		m_aRnAtAxis[iAxis]*=1.0-m_fRnDecrease;
	}
}


void TranslateMngr::CalculateMnVector(double aMnVector[3])
{
	for (int iAxis=0; iAxis<3; iAxis++)
		aMnVector[iAxis]+=m_aMnAtAxis[iAxis];
}


void TranslateMngr::CalculateRnMatrix(double aRnMatrix[3][3])
{
	for (int iAxis=0; iAxis<3; iAxis++)
	{
		double aMat1[3][3];
		double aMat2[3][3]={{1,0,0},{0,1,0},{0,0,1}};
		double aMat3[3][3]={{0,0,0},{0,0,0},{0,0,0}};

		for (int a=0; a<3; a++)
			for (int b=0; b<3; b++)
				aMat1[a][b]=aRnMatrix[a][b];

		aMat2[(iAxis+1)%3][(iAxis+1)%3]=+cos(m_aRnAtAxis[iAxis]*PI/180.0);
		aMat2[(iAxis+1)%3][(iAxis+2)%3]=-sin(m_aRnAtAxis[iAxis]*PI/180.0);
		aMat2[(iAxis+2)%3][(iAxis+1)%3]=+sin(m_aRnAtAxis[iAxis]*PI/180.0);
		aMat2[(iAxis+2)%3][(iAxis+2)%3]=+cos(m_aRnAtAxis[iAxis]*PI/180.0);

		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				for (int k=0; k<3; k++)
					aMat3[i][j]+=aMat1[i][k]*aMat2[k][j];

		for (int x=0; x<3; x++)
			for (int y=0; y<3; y++)
				aRnMatrix[x][y]=aMat3[x][y];
	}
}
