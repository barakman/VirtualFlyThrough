#ifndef DEVICE_H
#define DEVICE_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  Device                                                        //
//                                                                            //
// DESCRIPTION: Declare an abstract interface of the graphic operations       //
//              that this library requires in order to render the scene.      //
//                                                                            //
// REMARKS:     The Virtual Fly-Through library connects a graphic device     //
//              in order to render the scene.                                 //
//              The graphic device must implement the graphic operations      //
//              declared in this class.                                       //
//              Any graphic library that provides suitable operations can     //
//              be used (e.g. OpenGL, Win32).                                 //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class Device
{
protected: //Constructor + Destructor
	Device();
	virtual ~Device();
	//--------------------------------------------------------------------------
public: //Object interface
	virtual void Clear() = 0;
	virtual void Refresh() = 0;
	//--------------------------------------------------------------------------
public: //Object interface
	virtual void SetGray(double fLevel) = 0;
	virtual void SetPixel(int iX,int iY,int iR,int iG,int iB) = 0;
	virtual void SetViewport(int iMinX,int iMaxX,int iMinY,int iMaxY) = 0;
	//--------------------------------------------------------------------------
};


#endif
