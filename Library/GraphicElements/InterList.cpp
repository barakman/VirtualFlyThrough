#include "InterList.h"


InterList::InterList(int iNumOfPoints,Point** aPoints)
{
	m_iNumOfPoints=iNumOfPoints;
	m_aPoints=aPoints;
}


InterList::~InterList()
{
}


void InterList::Update(double fY,List<int>* pIndexList)
{
	for (int i=0; i<Size(); i++)
	{
		Inter& sInter=Get(i);
		if (MoveUp(sInter,fY)==false)
			Remove(i--);
	}

	while (pIndexList->Size()>0)
	{
		int iIndex=pIndexList->Get(0);
		if (m_aPoints[iIndex]->m_fY>fY)
			break;

		Inter sInter;

		sInter.m_iIndex=iIndex;
		sInter.m_iDrift=-1;
		sInter.m_fSlope=0.0;
		sInter.m_fCurrX=m_aPoints[iIndex]->m_fX;
		if (MoveUp(sInter,fY)==true)
			Insert(sInter);

		sInter.m_iIndex=iIndex;
		sInter.m_iDrift=+1;
		sInter.m_fSlope=0.0;
		sInter.m_fCurrX=m_aPoints[iIndex]->m_fX;
		if (MoveUp(sInter,fY)==true)
			Insert(sInter);

		pIndexList->Remove(0);
	}
}


void InterList::Insert(const Inter& sInter)
{
	int i;
	for (i=0; i<Size(); i++)
	{
		Inter sTemp=Get(i);
		if (sInter.m_fCurrX<sTemp.m_fCurrX || (sInter.m_fCurrX==sTemp.m_fCurrX && sInter.m_fSlope<sTemp.m_fSlope))
			break;
	}

	Add(sInter,i);
}


bool InterList::MoveUp(Inter& sInter,double fY) const
{
	int iIndex = sInter.m_iIndex;
	int iDrift = sInter.m_iDrift;

	int    iCurrIndex = iIndex;
	int    iNextIndex = (iIndex+iDrift+m_iNumOfPoints)%m_iNumOfPoints;
	double fCurrY     = m_aPoints[iCurrIndex]->m_fY;
	double fNextY     = m_aPoints[iNextIndex]->m_fY;

	while (fNextY<=fY)
	{
		if (fNextY<fCurrY)
			return false;
		iCurrIndex = iNextIndex;
		iNextIndex = (iNextIndex+iDrift+m_iNumOfPoints)%m_iNumOfPoints;
		fCurrY     = fNextY;
		fNextY     = m_aPoints[iNextIndex]->m_fY;
	}

	if (sInter.m_fSlope==0.0 || iIndex!=iCurrIndex)
	{
		sInter.m_iIndex = iCurrIndex;
		double fCurrX   = m_aPoints[iCurrIndex]->m_fX;
		double fNextX   = m_aPoints[iNextIndex]->m_fX;
		sInter.m_fSlope = (fNextX-fCurrX)/(fNextY-fCurrY);
		sInter.m_fCurrX = fCurrX+sInter.m_fSlope*(fY-fCurrY);
	}
	else
		sInter.m_fCurrX+=sInter.m_fSlope;

	return true;
}
