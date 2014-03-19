#ifndef VIRTUAL_FLY_THROUGH_H
#define VIRTUAL_FLY_THROUGH_H


#include "GraphicManagers\RenderMngr.h"
#include "GraphicManagers\TranslateMngr.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  VirtualFlyThrough                                             //
//                                                                            //
// DESCRIPTION: The interface of the Virtual Fly-Through library.             //
//                                                                            //
// REMARKS:     The scene's management is divided as follows:                 //
//              -Rendering, which is applied over the polygons.               //
//              -Translation, which is applied over the polyhedrons.          //
//              When adding a file to the scene:                              //
//              -Each new polyhedron is initialized with points               //
//               whose coordinates are listed in the file itself.             //
//              -Each new polygon is initialized with pointers to             //
//               some of the points of the polyhedron it belongs to.          //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class VirtualFlyThrough
{
public: //Must be invoked once during initialization
	VirtualFlyThrough();
	virtual ~VirtualFlyThrough();
	//--------------------------------------------------------------------------
public: //Can be invoked asynchronously at any cycle
	void AddToScene(const char* aFile);
	void ClearScene();
	//--------------------------------------------------------------------------
public: //Can be invoked asynchronously at any cycle
	void SetAtLight(double fAtLight);
	void SetPtLight(double fPtLight);
	void SetMnThrst(double fMnThrst);
	void SetRnAngle(double fRnAngle);
	void SetMnDecrease(double fMnDecrease);
	void SetRnDecrease(double fRnDecrease);
	//--------------------------------------------------------------------------
public: //Can be invoked asynchronously at any cycle
	void ConnectDevice(Device* pDevice);
	void Move(AXIS eAxis,DIRECTION eDirection);
	void Turn(AXIS eAxis,DIRECTION eDirection);
	void ReshapeWindow(int iMinX,int iMaxX,int iMinY,int iMaxY);
	//--------------------------------------------------------------------------
public: //Must be invoked synchronously at every cycle
	void Process();
	//--------------------------------------------------------------------------
private: //Graphic managers
	RenderMngr*    m_pRenderMngr;    //Scene rendering manager
	TranslateMngr* m_pTranslateMngr; //Scene translation manager
	//--------------------------------------------------------------------------
private: //Graphic elements
	List<Polygon*>*    m_pPolygonList;    //A list of the scene's polygons
	List<Polyhedron*>* m_pPolyhedronList; //A list of the scene's polyhedrons
	//--------------------------------------------------------------------------
};


#endif
