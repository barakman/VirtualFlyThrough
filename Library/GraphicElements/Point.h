#ifndef POINT_H
#define POINT_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  Point                                                         //
//                                                                            //
// DESCRIPTION: A point in the 3-dimensional space.                           //
//                                                                            //
// REMARKS:     All attributes are public, in order to minimize access time.  //
//              The constructor is used as a default constructor for arrays.  //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class Point
{
public: //Constructor + Destructor
	Point();
	virtual ~Point();
	//--------------------------------------------------------------------------
public: //Basic attributes
	double m_fX; //The x-coordinate of the point
	double m_fY; //The y-coordinate of the point
	double m_fZ; //The z-coordinate of the point
	//--------------------------------------------------------------------------
public: //Auxiliary attributes
	bool m_bIsInFront; //The status of the point relatively to the viewer
	//--------------------------------------------------------------------------
public: //Class attributes
	static double m_fDistance; //The distance of the viewer from the viewport
	//--------------------------------------------------------------------------
};


#endif
