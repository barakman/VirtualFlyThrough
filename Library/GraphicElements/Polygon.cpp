#include "Polygon.h"
#include <math.h>


#define DISTANCE Point::m_fDistance


Polygon::Polygon(int iColor,int iNumOfPoints)
{
	m_iColorR=(iColor>>16)&0xFF;
	m_iColorG=(iColor>> 8)&0xFF;
	m_iColorB=(iColor>> 0)&0xFF;
	m_iNumOfPoints=iNumOfPoints;

	m_aPoints=new Point*[m_iNumOfPoints];
	m_pIndexList=new IndexList(m_iNumOfPoints,m_aPoints);
	m_pInterList=new InterList(m_iNumOfPoints,m_aPoints);
}


Polygon::~Polygon()
{
	delete[] m_aPoints;
	delete m_pIndexList;
	delete m_pInterList;
}


void Polygon::Add(Point* pPoint,int iIndex)
{
	m_aPoints[iIndex]=pPoint;
}


bool Polygon::Reset(int& iY)
{
	for (int i=0; i<m_iNumOfPoints; i++)
		if (m_aPoints[i]->m_bIsInFront==false)
			return false;

	CalculateParameters();
	if (m_fCoeffC==0.0)
		return false;

	m_pIndexList->Clear();
	m_pIndexList->Create();

	int iMinIndex=m_pIndexList->Get(0);
	iY=(int)ceil(m_aPoints[iMinIndex]->m_fY);

	m_pInterList->Clear();
	return true;
}


bool Polygon::ScanLn(int iY)
{
	m_pInterList->Update(iY,m_pIndexList);
	return m_pInterList->Size()>0;
}


#define ROUND(x) (int)(x<0.0? x-0.5:x+0.5)


void Polygon::FillLn(int iY,int iMinX,int iMaxX,double* aDepthBuffer,
                     double fAtLight,double fPtLight,Device* pDevice)
{
	for (int i=0; i<m_pInterList->Size(); i+=2)
	{
		Inter sInter0=m_pInterList->Get(i+0);
		Inter sInter1=m_pInterList->Get(i+1);
		int iCurrX0=ROUND(sInter0.m_fCurrX);
		int iCurrX1=ROUND(sInter1.m_fCurrX);

		int iX0=(iCurrX0>iMinX? iCurrX0:iMinX);
		int iX1=(iCurrX1<iMaxX? iCurrX1:iMaxX);
		double fZ=-(m_fCoeffA*(double)iX0+m_fCoeffB*(double)iY+m_fCoeffD)/m_fCoeffC;

		while (iX0<iX1)
		{
			if (aDepthBuffer[iX0-iMinX]>fZ)
			{
				aDepthBuffer[iX0-iMinX]=fZ;
				double fDistance=DISTANCE*DISTANCE/(DISTANCE-fZ);
				if (fDistance<1.0)
					fDistance=1.0;
				double fLight=fAtLight+fPtLight/fDistance*m_fNormalLight;
				int iColorR=(int)(m_iColorR*fLight);
				int iColorG=(int)(m_iColorG*fLight);
				int iColorB=(int)(m_iColorB*fLight);
				pDevice->SetPixel(iX0,iY,iColorR,iColorG,iColorB);
			}
			iX0++;
			fZ-=m_fSlopeZ;
		}
	}
}


void Polygon::CalculateParameters()
{
	double fX0=m_aPoints[0]->m_fX;
	double fX1=m_aPoints[1]->m_fX;
	double fX2=m_aPoints[2]->m_fX;
	double fY0=m_aPoints[0]->m_fY;
	double fY1=m_aPoints[1]->m_fY;
	double fY2=m_aPoints[2]->m_fY;
	double fZ0=m_aPoints[0]->m_fZ;
	double fZ1=m_aPoints[1]->m_fZ;
	double fZ2=m_aPoints[2]->m_fZ;

	m_fCoeffA=fY0*(fZ1-fZ2)+fY1*(fZ2-fZ0)+fY2*(fZ0-fZ1);
	m_fCoeffB=fZ0*(fX1-fX2)+fZ1*(fX2-fX0)+fZ2*(fX0-fX1);
	m_fCoeffC=fX0*(fY1-fY2)+fX1*(fY2-fY0)+fX2*(fY0-fY1);

	m_fCoeffD=-fX0*(fY1*fZ2-fZ1*fY2)+fX1*(fY0*fZ2-fZ0*fY2)-fX2*(fY0*fZ1-fZ0*fY1);
	m_fSlopeZ=m_fCoeffA/m_fCoeffC;
	m_fNormalLight=fabs(m_fCoeffC/sqrt(m_fCoeffA*m_fCoeffA+m_fCoeffB*m_fCoeffB+m_fCoeffC*m_fCoeffC));
}
