#include "GlutDevice.h"


GlutDevice::GlutDevice()
{
}


GlutDevice::~GlutDevice()
{
}


void GlutDevice::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
}


void GlutDevice::Refresh()
{
	glEnd();
	glutSwapBuffers();
}


void GlutDevice::SetGray(double fLevel)
{
	glClearColor(fLevel,fLevel,fLevel,0.0);
}


void GlutDevice::SetPixel(int iX,int iY,int iR,int iG,int iB)
{
	glColor3ub(iR,iG,iB);
	glVertex2i(iX,iY);
}


void GlutDevice::SetViewport(int iMinX,int iMaxX,int iMinY,int iMaxY)
{
	glViewport(0,0,iMaxX-iMinX,iMaxY-iMinY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(iMinX,iMaxX,iMinY,iMaxY,-1,+1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
