#ifndef POLYGON_H
#define POLYGON_H


#include "Point.h"
#include "IndexList.h"
#include "InterList.h"
#include "..\GenericClasses\Device.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  Polygon                                                       //
//                                                                            //
// DESCRIPTION: A polygon in the 3-dimensional space.                         //
//                                                                            //
// REMARKS:     The polygon is used for scanline rendering:                   //
//              -Each of the pixels between each pair of adjacent             //
//               intersections (with the polygon edges) is rendered.          //
//              -If the pixel has already been rendered by a polygon          //
//               which is closer at that position, then it is skipped.        //
//              -The brightness of each pixel is a function of its color,     //
//               its position, and the ambient-light / point-light ratio.     //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class Polygon
{
public: //Constructor + Destructor
	Polygon(int iColor,int iNumOfPoints);
	virtual ~Polygon();
	//--------------------------------------------------------------------------
public: //Initial interface
	void Add(Point* pPoint,int iIndex);
	//--------------------------------------------------------------------------
public: //Periodical interface
	bool Reset(int& iY);
	bool ScanLn(int iY);
	void FillLn(int iY,int iMinX,int iMaxX,double* aDepthBuffer,
	            double fAtLight,double fPtLight,Device* pDevice);
	//--------------------------------------------------------------------------
private: //Internal operations
	void CalculateParameters();
	//--------------------------------------------------------------------------
private: //Basic attributes
	int m_iColorR;      //The red value of the polygon's color
	int m_iColorG;      //The green value of the polygon's color
	int m_iColorB;      //The blue value of the polygon's color
	int m_iNumOfPoints; //The number of vertices in the polygon
	//--------------------------------------------------------------------------
private: //Data structures
	Point**    m_aPoints;    //An array of the polygon's vertices
	IndexList* m_pIndexList; //A list of local-minimum vertex indices
	InterList* m_pInterList; //A list of edge-scanline intersections
	//--------------------------------------------------------------------------
private: //Equation parameters
	double m_fCoeffA;      //Coefficient A in the equation of the polygon
	double m_fCoeffB;      //Coefficient B in the equation of the polygon
	double m_fCoeffC;      //Coefficient C in the equation of the polygon
	double m_fCoeffD;      //Coefficient D in the equation of the polygon
	double m_fSlopeZ;      //The slope of the polygon in the z-axis direction
	double m_fNormalLight; //Cartesian product: <Normal Vector , Light Vector>
	//--------------------------------------------------------------------------
};


#endif
