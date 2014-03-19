#include "VirtualFlyThrough.h"
#include <stdio.h>


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
	FILE* pFile=fopen(aFile,"rt");

	int iNumOfPolyhedrons=0;
	fscanf(pFile,"%d",&iNumOfPolyhedrons);

	for (int iPolyhedronNum=0; iPolyhedronNum<iNumOfPolyhedrons; iPolyhedronNum++)
	{
		char aName[100]={0};
		int  iNumOfPoints=0;
		int  iNumOfPolygons=0;
		fscanf(pFile,"%s%d%d",aName,&iNumOfPoints,&iNumOfPolygons);
		Polyhedron* pPolyhedron=new Polyhedron(aName,iNumOfPoints);

		for (int iPointNum=0; iPointNum<iNumOfPoints; iPointNum++)
		{
			Point cPoint;
			fscanf(pFile,"%lf%lf%lf",&cPoint.m_fX,&cPoint.m_fY,&cPoint.m_fZ);
			pPolyhedron->Add(cPoint,iPointNum);
		}

		for (int iPolygonNum=0; iPolygonNum<iNumOfPolygons; iPolygonNum++)
		{
			int iColor=0;
			int iNumOfIndices=0;
			fscanf(pFile,"%x%d",&iColor,&iNumOfIndices);
			Polygon* pPolygon=new Polygon(iColor,iNumOfIndices);

			for (int iIndexNum=0; iIndexNum<iNumOfIndices; iIndexNum++)
			{
				int iIndex=0;
				fscanf(pFile,"%d",&iIndex);
				pPolygon->Add(pPolyhedron->Get(iIndex),iIndexNum);
			}

			m_pPolygonList->Add(pPolygon,0);
		}

		m_pPolyhedronList->Add(pPolyhedron,0);
	}

	fclose(pFile);
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
