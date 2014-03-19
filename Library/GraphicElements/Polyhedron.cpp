#include "Polyhedron.h"
#include <string.h>


#define DISTANCE Point::m_fDistance


Polyhedron::Polyhedron(const char* aName,int iNumOfPoints)
{
	m_aName=new char[strlen(aName)+1];
	strcpy(m_aName,aName);

	m_iNumOfPoints=iNumOfPoints;
	m_aWorldPoints=new Point[m_iNumOfPoints];
	m_aWindowPoints=new Point[m_iNumOfPoints];
}


Polyhedron::~Polyhedron()
{
	delete[] m_aName;
	delete[] m_aWorldPoints;
	delete[] m_aWindowPoints;
}


void Polyhedron::Add(Point& cPoint,int iIndex)
{
	m_aWorldPoints[iIndex]=cPoint;
}


Point* Polyhedron::Get(int iIndex) const
{
	return m_aWindowPoints+iIndex;
}


void Polyhedron::Move(const double aMnVector[3])
{
	for (int i=0; i<m_iNumOfPoints; i++)
	{
		m_aWorldPoints[i].m_fX+=aMnVector[0];
		m_aWorldPoints[i].m_fY+=aMnVector[1];
		m_aWorldPoints[i].m_fZ+=aMnVector[2];
	}
}


void Polyhedron::Turn(const double aRnMatrix[3][3])
{
	for (int i=0; i<m_iNumOfPoints; i++)
	{
		double fX=m_aWorldPoints[i].m_fX;
		double fY=m_aWorldPoints[i].m_fY;
		double fZ=m_aWorldPoints[i].m_fZ+DISTANCE;

		m_aWorldPoints[i].m_fX=fX*aRnMatrix[0][0]+fY*aRnMatrix[1][0]+fZ*aRnMatrix[2][0];
		m_aWorldPoints[i].m_fY=fX*aRnMatrix[0][1]+fY*aRnMatrix[1][1]+fZ*aRnMatrix[2][1];
		m_aWorldPoints[i].m_fZ=fX*aRnMatrix[0][2]+fY*aRnMatrix[1][2]+fZ*aRnMatrix[2][2]-DISTANCE;
	}
}


void Polyhedron::ProjectPoints()
{
	for (int i=0; i<m_iNumOfPoints; i++)
	{
		double fFactor=DISTANCE/(m_aWorldPoints[i].m_fZ+DISTANCE);

		m_aWindowPoints[i].m_fX=m_aWorldPoints[i].m_fX*fFactor;
		m_aWindowPoints[i].m_fY=m_aWorldPoints[i].m_fY*fFactor;
		m_aWindowPoints[i].m_fZ=m_aWorldPoints[i].m_fZ*fFactor;
		m_aWindowPoints[i].m_bIsInFront=m_aWorldPoints[i].m_fZ>-DISTANCE;
	}
}
