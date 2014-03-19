#include "MainInterface.h"


#include "GraphicHandlers\GluiMenu.h"
#include "GraphicHandlers\GlutDevice.h"
#include "..\Library\VirtualFlyThrough.h"


double Point::m_fDistance = 500.0;


static GluiMenu*          g_pGluiMenu;
static GlutDevice*        g_pGlutDevice;
static VirtualFlyThrough* g_pVirtualFlyThrough;


void main()
{
	int iWidth=glutGet(GLUT_SCREEN_WIDTH);
	int iHeight=glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(iWidth,iHeight);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	int iWindowId=glutCreateWindow(WINDOW_TITLE);

	CreateSimulation();
	atexit(DestroySimulation);
	AdjustSimulation(iWindowId);

	GLUI_Master.set_glutIdleFunc(OnIdle);
	GLUI_Master.set_glutDisplayFunc(OnDisplay);
	GLUI_Master.set_glutReshapeFunc(OnReshape);
	GLUI_Master.set_glutSpecialFunc(OnSpecial);
	GLUI_Master.set_glutKeyboardFunc(OnKeyboard);
	GLUI_Master.set_glutMouseFunc(OnMouse);

	glutMainLoop();
}


void CreateSimulation()
{
	g_pGluiMenu=GluiMenu::New();
	g_pGlutDevice=new GlutDevice;
	g_pVirtualFlyThrough=new VirtualFlyThrough;
}


void DestroySimulation()
{
	GluiMenu::Delete();
	delete g_pGlutDevice;
	delete g_pVirtualFlyThrough;
}


void AdjustSimulation(int iWindowId)
{
	g_pGluiMenu->Init(iWindowId);
	g_pVirtualFlyThrough->ConnectDevice(g_pGlutDevice);
}


void OnIdle()
{
	switch (g_pGluiMenu->SwitchCommand())
	{
	case HALT:
		break;
	case CLEAR:
		g_pVirtualFlyThrough->ClearScene();
		break;
	case UPDATE:
		g_pVirtualFlyThrough->AddToScene(g_pGluiMenu->GetFile());
		break;
	case REFRESH:
		g_pVirtualFlyThrough->SetAtLight(g_pGluiMenu->GetAtLight());
		g_pVirtualFlyThrough->SetPtLight(g_pGluiMenu->GetPtLight());
		g_pVirtualFlyThrough->SetMnThrst(g_pGluiMenu->GetMnThrst());
		g_pVirtualFlyThrough->SetRnAngle(g_pGluiMenu->GetRnAngle());
		g_pVirtualFlyThrough->SetMnDecrease(g_pGluiMenu->GetMnDecrease());
		g_pVirtualFlyThrough->SetRnDecrease(g_pGluiMenu->GetRnDecrease());
		break;
	case CONTINUE:
		glutPostRedisplay();
		break;
	}
}


void OnDisplay()
{
	g_pVirtualFlyThrough->Process();
}


void OnReshape(int iWidth,int iHeight)
{
	g_pVirtualFlyThrough->ReshapeWindow(-iWidth/2,+iWidth/2,-iHeight/2,+iHeight/2);
}


void OnSpecial(int iKey,int iX,int iY)
{
	switch (iKey)
	{
	case GLUT_KEY_LEFT:
		g_pVirtualFlyThrough->Move(X_AXIS,NEGATIVE_DIRECTION);
		break;
	case GLUT_KEY_RIGHT:
		g_pVirtualFlyThrough->Move(X_AXIS,POSITIVE_DIRECTION);
		break;
	case GLUT_KEY_DOWN:
		g_pVirtualFlyThrough->Move(Y_AXIS,NEGATIVE_DIRECTION);
		break;
	case GLUT_KEY_UP:
		g_pVirtualFlyThrough->Move(Y_AXIS,POSITIVE_DIRECTION);
		break;
	case GLUT_KEY_END:
		g_pVirtualFlyThrough->Move(Z_AXIS,NEGATIVE_DIRECTION);
		break;
	case GLUT_KEY_HOME:
		g_pVirtualFlyThrough->Move(Z_AXIS,POSITIVE_DIRECTION);
		break;
	case GLUT_KEY_INSERT:
		g_pVirtualFlyThrough->SetMnDecrease(1.0);
		g_pVirtualFlyThrough->Process();
		g_pVirtualFlyThrough->SetMnDecrease(g_pGluiMenu->GetMnDecrease());
		break;
	}
}


void OnKeyboard(unsigned char iKey,int iX,int iY)
{
	switch (iKey)
	{
	case 'x':
		g_pVirtualFlyThrough->Turn(X_AXIS,NEGATIVE_DIRECTION);
		break;
	case 'w':
		g_pVirtualFlyThrough->Turn(X_AXIS,POSITIVE_DIRECTION);
		break;
	case 'd':
		g_pVirtualFlyThrough->Turn(Y_AXIS,NEGATIVE_DIRECTION);
		break;
	case 'a':
		g_pVirtualFlyThrough->Turn(Y_AXIS,POSITIVE_DIRECTION);
		break;
	case 'z':
		g_pVirtualFlyThrough->Turn(Z_AXIS,NEGATIVE_DIRECTION);
		break;
	case 'c':
		g_pVirtualFlyThrough->Turn(Z_AXIS,POSITIVE_DIRECTION);
		break;
	case ' ':
		g_pVirtualFlyThrough->SetRnDecrease(1.0);
		g_pVirtualFlyThrough->Process();
		g_pVirtualFlyThrough->SetRnDecrease(g_pGluiMenu->GetRnDecrease());
		break;
	}
}


void OnMouse(int iButton,int iState,int iX,int iY)
{
	switch (iButton)
	{
	case GLUT_LEFT_BUTTON:
	case GLUT_MIDDLE_BUTTON:
		g_pGluiMenu->Hide();
		break;
	case GLUT_RIGHT_BUTTON:
		switch (iState)
		{
		case GLUT_DOWN:
			g_pGluiMenu->Hide();
			break;
		case GLUT_UP:
			g_pGluiMenu->Show();
			break;
		}
		break;
	}
}
