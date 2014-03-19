#ifndef INDEX_LIST_H
#define INDEX_LIST_H


#include "Point.h"
#include "..\GenericClasses\List.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  IndexList                                                     //
//                                                                            //
// DESCRIPTION: A list of local-minimum vertex indices.                       //
//                                                                            //
// REMARKS:     Derives from Class List<int>.                                 //
//              Maintains the critical points of a polygon.                   //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class IndexList : public List<int>
{
public: //Constructor + Destructor
	IndexList(int iNumOfPoints,Point** aPoints);
	virtual ~IndexList();
	//--------------------------------------------------------------------------
public: //Interface operations
	void Create();
	//--------------------------------------------------------------------------
private: //Internal operations
	void Insert(int iIndex);
	//--------------------------------------------------------------------------
private: //Basic attributes
	int m_iNumOfPoints; //The number of vertices in the polygon
	Point**  m_aPoints; //An array of the polygon's vertices
	//--------------------------------------------------------------------------
};


#endif
