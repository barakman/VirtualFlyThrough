#include "RenderMngr.h"


#define INFINITUDE 1.7E308


RenderMngr::RenderMngr()
{
	m_aDepthBuffer=0;
	m_aPolygonLists=0;
}


RenderMngr::~RenderMngr()
{
	if (m_aDepthBuffer!=0)
		delete[] m_aDepthBuffer;
	if (m_aPolygonLists!=0)
		delete[] m_aPolygonLists;
}


void RenderMngr::SetAtLight(double fAtLight)
{
	m_fAtLight=fAtLight;
	m_fPtLight=1.0-m_fAtLight;

	m_pDevice->SetGray(m_fAtLight);
}


void RenderMngr::SetPtLight(double fPtLight)
{
	m_fPtLight=fPtLight;
	m_fAtLight=1.0-m_fPtLight;

	m_pDevice->SetGray(m_fAtLight);
}


void RenderMngr::ConnectDevice(Device* pDevice)
{
	m_pDevice=pDevice;
}


void RenderMngr::ReshapeWindow(int iMinX,int iMaxX,int iMinY,int iMaxY)
{
	m_iMinX=iMinX;
	m_iMaxX=iMaxX;
	m_iMinY=iMinY;
	m_iMaxY=iMaxY;

	if (m_aDepthBuffer!=0)
		delete[] m_aDepthBuffer;
	if (m_aPolygonLists!=0)
		delete[] m_aPolygonLists;

	if (m_iMaxX>m_iMinX)
		m_aDepthBuffer=new double[m_iMaxX-m_iMinX];
	else
		m_aDepthBuffer=0;

	if (m_iMaxY>m_iMinY)
		m_aPolygonLists=new List<Polygon*>[m_iMaxY-m_iMinY];
	else
		m_aPolygonLists=0;

	m_pDevice->SetViewport(m_iMinX,m_iMaxX,m_iMinY,m_iMaxY);
}


void RenderMngr::Process(List<Polygon*>* pPolygonList)
{
	m_pDevice->Clear();

	FindEachLinePolygons(pPolygonList);
	DrawEachLinePolygons(pPolygonList);

	m_pDevice->Refresh();
}


void RenderMngr::FindEachLinePolygons(List<Polygon*>* pPolygonList)
{
	for (int i=0; i<pPolygonList->Size(); i++)
	{
		Polygon* pPolygon=pPolygonList->Get(i);
		int iY;

		if (pPolygon->Reset(iY)==false)
			continue;

		if (iY<m_iMinY)
			iY=m_iMinY;

		if (iY>=m_iMaxY)
			continue;

		List<Polygon*>* pCurrLinePolygons=m_aPolygonLists+iY-m_iMinY;
		pCurrLinePolygons->Add(pPolygon,pCurrLinePolygons->Size());
	}
}


void RenderMngr::DrawEachLinePolygons(List<Polygon*>* pPolygonList)
{
	List<Polygon*> cCurrLinePolygons;

	for (int iY=m_iMinY; iY<m_iMaxY; iY++)
	{
		cCurrLinePolygons.Append(m_aPolygonLists[iY-m_iMinY]);
		if (cCurrLinePolygons.Size()==0)
			continue;

		for (int iX=m_iMinX; iX<m_iMaxX; iX++)
			m_aDepthBuffer[iX-m_iMinX]=INFINITUDE;

		for (int i=0; i<cCurrLinePolygons.Size(); i++)
		{
			Polygon* pPolygon=cCurrLinePolygons.Get(i);
			if (pPolygon->ScanLn(iY)==true)
				pPolygon->FillLn(iY,m_iMinX,m_iMaxX,m_aDepthBuffer,m_fAtLight,m_fPtLight,m_pDevice);
			else
				cCurrLinePolygons.Remove(i--);
		}
	}
}
