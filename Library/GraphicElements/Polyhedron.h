#ifndef POLYHEDRON_H
#define POLYHEDRON_H


#include "Point.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  Polyhedron                                                    //
//                                                                            //
// DESCRIPTION: A polyhedron in the 3-dimensional space.                      //
//                                                                            //
// REMARKS:     The polyhedron is used for translation:                       //
//              -It maintains world points, which are the real points,        //
//               and window points, which are the projected real points.      //
//              -It first translates the real points according to the user    //
//               input data, and then projects them into the window points.   //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class Polyhedron
{
public: //Constructor + Destructor
	Polyhedron(const char* aName,int iNumOfPoints);
	virtual ~Polyhedron();
	//--------------------------------------------------------------------------
public: //Initial interface
	void Add(Point& cPoint,int iIndex);
	Point* Get(int iIndex) const;
	//--------------------------------------------------------------------------
public: //Periodical interface
	void Move(const double aMnVector[3]);
	void Turn(const double aRnMatrix[3][3]);
	void ProjectPoints();
	//--------------------------------------------------------------------------
private: //Basic attributes
	char* m_aName;        //The name of the polyhedron
	int   m_iNumOfPoints; //The number of vertices in the polyhedron
	//--------------------------------------------------------------------------
private: //Data structures
	Point* m_aWorldPoints;  //An array of the polyhedron's vertices
	Point* m_aWindowPoints; //An array of the polyhedron's projected vertices
	//--------------------------------------------------------------------------
};


#endif
