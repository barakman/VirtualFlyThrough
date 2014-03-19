#ifndef RENDER_MNGR_H
#define RENDER_MNGR_H


#include "..\GenericClasses\List.h"
#include "..\GraphicElements\Polygon.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  RenderMngr                                                    //
//                                                                            //
// DESCRIPTION: Render the polygons in the scene.                             //
//                                                                            //
// REMARKS:     This manager maintains the following lists:                   //
//              -For each scanline, a list of the polygons that begin at it.  //
//              -A list of the polygons that intersect the current scanline.  //
//              It processes the scene (each scanline) as follows:            //
//              -Appends the list of the polygons that begin at the           //
//               scanline to the list of the polygons that intersect it.      //
//              -Calls each polygon to render the scanline and update its     //
//               depth, and removes the polygon if it ends at the scanline.   //
//              -Any polygon that is either partly behind the viewing plane   //
//               of the viewer or situated perpendicularly to it, is skipped. //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class RenderMngr
{
public: //Must be invoked once during initialization
	RenderMngr();
	virtual ~RenderMngr();
	//--------------------------------------------------------------------------
public: //Can be invoked asynchronously at any cycle
	void SetAtLight(double fAtLight);
	void SetPtLight(double fPtLight);
	void ConnectDevice(Device* pDevice);
	void ReshapeWindow(int iMinX,int iMaxX,int iMinY,int iMaxY);
	//--------------------------------------------------------------------------
public: //Must be invoked synchronously at every cycle
	void Process(List<Polygon*>* pPolygonList);
	//--------------------------------------------------------------------------
private: //Internal operations
	void FindEachLinePolygons(List<Polygon*>* pPolygonList);
	void DrawEachLinePolygons(List<Polygon*>* pPolygonList);
	//--------------------------------------------------------------------------
private: //Rendering constants
	double m_fAtLight; //Ambient light factor
	double m_fPtLight; //Point light factor
	//--------------------------------------------------------------------------
private: //Rendering utility
	Device* m_pDevice; //A graphic device
	//--------------------------------------------------------------------------
private: //Viewport boundaries
	int m_iMinX; //The x-coordinate of the left-most part of the viewport
	int m_iMaxX; //The x-coordinate of the right-most part of the viewport
	int m_iMinY; //The y-coordinate of the top-most part of the viewport
	int m_iMaxY; //The y-coordinate of the bottom-most part of the viewport
	//--------------------------------------------------------------------------
private: //Data structures
	double*         m_aDepthBuffer;  //The current scanline's depth
	List<Polygon*>* m_aPolygonLists; //Each scanline's polygon list
	//--------------------------------------------------------------------------
};


#endif
