#ifndef INTER_LIST_H
#define INTER_LIST_H


#include "Point.h"
#include "..\GenericClasses\List.h"


struct Inter
{
	int    m_iIndex; //The index of the edge's first vertex
	int    m_iDrift; //The direction towards the edge's second vertex
	double m_fSlope; //The inverse of the edge's slope
	double m_fCurrX; //The edge's intersection with the current scanline
};


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  InterList                                                     //
//                                                                            //
// DESCRIPTION: A list of edge-scanline intersections.                        //
//                                                                            //
// REMARKS:     Derives from Class List<Inter>.                               //
//              Maintains the active edges of a polygon.                      //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class InterList : public List<Inter>
{
public: //Constructor + Destructor
	InterList(int iNumOfPoints,Point** aPoints);
	virtual ~InterList();
	//--------------------------------------------------------------------------
public: //Interface operations
	void Update(double fY,List<int>* pIndexList);
	//--------------------------------------------------------------------------
private: //Internal operations
	void Insert(const Inter& sInter);
	bool MoveUp(Inter& sInter,double fY) const;
	//--------------------------------------------------------------------------
private: //Basic attributes
	int m_iNumOfPoints; //The number of vertices in the polygon
	Point**  m_aPoints; //An array of the polygon's vertices
	//--------------------------------------------------------------------------
};


#endif
