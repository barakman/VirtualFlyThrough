#include "IndexList.h"


IndexList::IndexList(int iNumOfPoints,Point** aPoints)
{
	m_iNumOfPoints=iNumOfPoints;
	m_aPoints=aPoints;
}


IndexList::~IndexList()
{
}


void IndexList::Create()
{
	double fY1;
	double fY2=m_aPoints[0]->m_fY;

	bool bCandidate=false;
	for (int i=0; i<m_iNumOfPoints; i++)
	{
		fY1=fY2;
		fY2=m_aPoints[(i+1)%m_iNumOfPoints]->m_fY;
		if (fY1>fY2)
			bCandidate=true;
		else if (fY1<fY2 && bCandidate==true)
		{
			Insert(i);
			bCandidate=false;
		}
	}

	if (bCandidate==true)
	{
		for (int j=0; j<m_iNumOfPoints-1; j++)
		{
			fY1=fY2;
			fY2=m_aPoints[j+1]->m_fY;
			if (fY1>fY2)
				break;
			else if (fY1<fY2)
			{
				Insert(j);
				break;
			}
		}
	}
}


void IndexList::Insert(int iIndex)
{
	int i;
	for (i=0; i<Size(); i++)
	{
		int iTemp=Get(i);
		if (m_aPoints[iIndex]->m_fY<m_aPoints[iTemp]->m_fY)
			break;
	}

	Add(iIndex,i);
}
