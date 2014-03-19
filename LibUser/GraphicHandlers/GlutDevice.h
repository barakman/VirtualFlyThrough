#ifndef GLUT_DEVICE_H
#define GLUT_DEVICE_H


#include <GL\glut.h>
#include "..\..\Library\GenericClasses\Device.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  GlutDevice                                                    //
//                                                                            //
// DESCRIPTION: Implement the interface of graphic operations that the        //
//              Virtual Fly-Through library requires for scene rendering.     //
//                                                                            //
// REMARKS:     Derives from Class Device.                                    //
//              Uses the GLUT library (by Nate Robins).                       //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class GlutDevice : public Device
{
public: //Constructor + Destructor
	GlutDevice();
	virtual ~GlutDevice();
	//--------------------------------------------------------------------------
public: //Object interface
	virtual void Clear();
	virtual void Refresh();
	//--------------------------------------------------------------------------
public: //Object interface
	virtual void SetGray(double fLevel);
	virtual void SetPixel(int iX,int iY,int iR,int iG,int iB);
	virtual void SetViewport(int iMinX,int iMaxX,int iMinY,int iMaxY);
	//--------------------------------------------------------------------------
};


#endif
