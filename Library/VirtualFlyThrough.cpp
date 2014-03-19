#include "VirtualFlyThrough.h"
#include <fstream.h>


VirtualFlyThrough::VirtualFlyThrough()
{
	m_pRenderMngr=new RenderMngr;
	m_pTranslateMngr=new TranslateMngr;

	m_pPolygonList=new List<Polygon*>;
	m_pPolyhedronList=new List<Polyhedron*>;
}


VirtualFlyThrough::~VirtualFlyThrough()
{
	ClearScene();

	delete m_pRenderMngr;
	delete m_pTranslateMngr;

	delete m_pPolygonList;
	delete m_pPolyhedronList;
}


void VirtualFlyThrough::AddToScene(const char* aFile)
{
	ifstream cFile(aFile);

	int iNumOfPolyhedrons=0;
	cFile>>iNumOfPolyhedrons;

	for (int iPolyhedronNum=0; iPolyhedronNum<iNumOfPolyhedrons; iPolyhedronNum++)
	{
		char aName[100]={0};
		cFile>>aName;
		int iNumOfPoints=0;
		cFile>>iNumOfPoints;
		int iNumOfPolygons=0;
		cFile>>iNumOfPolygons;
		Polyhedron* pPolyhedron=new Polyhedron(aName,iNumOfPoints);

		for (int iPointNum=0; iPointNum<iNumOfPoints; iPointNum++)
		{
			Point cPoint;
			cFile>>cPoint.m_fX;
			cFile>>cPoint.m_fY;
			cFile>>cPoint.m_fZ;
			pPolyhedron->Add(cPoint,iPointNum);
		}

		for (int iPolygonNum=0; iPolygonNum<iNumOfPolygons; iPolygonNum++)
		{
			int iColor=0;
			cFile>>iColor;
			int iNumOfIndices=0;
			cFile>>iNumOfIndices;
			Polygon* pPolygon=new Polygon(iColor,iNumOfIndices);

			for (int iIndexNum=0; iIndexNum<iNumOfIndices; iIndexNum++)
			{
				int iIndex=0;
				cFile>>iIndex;
				Point* pPoint;
				pPoint=pPolyhedron->Get(iIndex);
				pPolygon->Add(pPoint,iIndexNum);
			}

			m_pPolygonList->Add(pPolygon,0);
		}

		m_pPolyhedronList->Add(pPolyhedron,0);
	}
}


void VirtualFlyThrough::ClearScene()
{
	while (m_pPolygonList->Size()>0)
	{
		Polygon* pPolygon=m_pPolygonList->Get(0);
		m_pPolygonList->Remove(0);
		delete pPolygon;
	}

	while (m_pPolyhedronList->Size()>0)
	{
		Polyhedron* pPolyhedron=m_pPolyhedronList->Get(0);
		m_pPolyhedronList->Remove(0);
		delete pPolyhedron;
	}
}


void VirtualFlyThrough::SetAtLight(double fAtLight)
{
	m_pRenderMngr->SetAtLight(fAtLight);
}


void VirtualFlyThrough::SetPtLight(double fPtLight)
{
	m_pRenderMngr->SetPtLight(fPtLight);
}


void VirtualFlyThrough::SetMnThrst(double fMnThrst)
{
	m_pTranslateMngr->SetMnThrst(fMnThrst);
}


void VirtualFlyThrough::SetRnAngle(double fRnAngle)
{
	m_pTranslateMngr->SetRnAngle(fRnAngle);
}


void VirtualFlyThrough::SetMnDecrease(double fMnDecrease)
{
	m_pTranslateMngr->SetMnDecrease(fMnDecrease);
}


void VirtualFlyThrough::SetRnDecrease(double fRnDecrease)
{
	m_pTranslateMngr->SetRnDecrease(fRnDecrease);
}


void VirtualFlyThrough::ConnectDevice(Device* pDevice)
{
	m_pRenderMngr->ConnectDevice(pDevice);
}


void VirtualFlyThrough::Move(AXIS eAxis,DIRECTION eDirection)
{
	m_pTranslateMngr->Move(eAxis,eDirection);
}


void VirtualFlyThrough::Turn(AXIS eAxis,DIRECTION eDirection)
{
	m_pTranslateMngr->Turn(eAxis,eDirection);
}


void VirtualFlyThrough::ReshapeWindow(int iMinX,int iMaxX,int iMinY,int iMaxY)
{
	m_pRenderMngr->ReshapeWindow(iMinX,iMaxX,iMinY,iMaxY);
}


void VirtualFlyThrough::Process()
{
	m_pRenderMngr->Process(m_pPolygonList);
	m_pTranslateMngr->Process(m_pPolyhedronList);
}
