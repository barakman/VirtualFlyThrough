#include "GluiMenu.h"


GluiMenu* GluiMenu::m_pGluiMenu = NULL;


GluiMenu::GluiMenu()
{
	m_pContainer=GLUI_Master.create_glui("Menu");
}


GluiMenu::~GluiMenu()
{
	GLUI_Master.close_all();
}


GluiMenu* GluiMenu::New()
{
	if (m_pGluiMenu==NULL)
		m_pGluiMenu=new GluiMenu;

	return m_pGluiMenu;
}


void GluiMenu::Delete()
{
	if (m_pGluiMenu!=NULL)
		delete m_pGluiMenu;

	m_pGluiMenu=NULL;
}


void GluiMenu::Init(int iWindowId)
{
	m_pContainer->set_main_gfx_window(iWindowId);
	FillUpContainer();

	m_bIsOn=true;
	m_eCommand=REFRESH;
}


void GluiMenu::Show()
{
	if (m_bIsOn==false)
	{
		m_bIsOn=true;
		m_pContainer->show();
	}
}


void GluiMenu::Hide()
{
	if (m_bIsOn==true)
	{
		m_bIsOn=false;
		m_pContainer->hide();
	}
}


COMMAND GluiMenu::SwitchCommand()
{
	if (m_bIsOn==true)
		return HALT;

	else if (m_eCommand==CLEAR)
	{
		m_eCommand=REFRESH;
		return CLEAR;
	}

	else if (m_eCommand==UPDATE)
	{
		m_eCommand=REFRESH;
		return UPDATE;
	}

	else if (m_eCommand==REFRESH)
	{
		m_eCommand=CONTINUE;
		return REFRESH;
	}

	else
		return CONTINUE;
}


char* GluiMenu::GetFile() const
{
	return m_cDirectory.GetFileName(m_pFilesListbox->get_int_val());
}


double GluiMenu::GetAtLight() const
{
	return (double)m_pAtLightSpinner->get_int_val()/100.0;
}


double GluiMenu::GetPtLight() const
{
	return (double)m_pPtLightSpinner->get_int_val()/100.0;
}


double GluiMenu::GetMnThrst() const
{
	return (double)m_pMnThrstSpinner->get_float_val();
}


double GluiMenu::GetRnAngle() const
{
	return (double)m_pRnAngleSpinner->get_float_val();
}


double GluiMenu::GetMnDecrease() const
{
	return (double)m_pMnDecreaseSpinner->get_int_val()/100.0;
}


double GluiMenu::GetRnDecrease() const
{
	return (double)m_pRnDecreaseSpinner->get_int_val()/100.0;
}


void GluiMenu::FillUpContainer()
{
	GLUI_Panel* pPanel1=m_pContainer->add_panel("Scene");
	m_pClearButton=m_pContainer->add_button_to_panel(pPanel1,"Clear All",0,ClearAll);
	m_pAddToButton=m_pContainer->add_button_to_panel(pPanel1,"Open File",0,OpenFile);
	m_pFilesListbox=m_pContainer->add_listbox_to_panel(pPanel1,"Files List:",NULL,0);
	InsertDirectory();

	m_pContainer->add_column();

	GLUI_Panel* pPanel2=m_pContainer->add_panel("Reflection");
	m_pAtLightSpinner=m_pContainer->add_spinner_to_panel(pPanel2,"Ambient Light %:",GLUI_SPINNER_INT,NULL,0,SetAtLight);
	m_pAtLightSpinner->set_int_limits(0,100);
	m_pAtLightSpinner->set_int_val(50);
	m_pContainer->add_separator_to_panel(pPanel2);
	m_pContainer->add_separator_to_panel(pPanel2);
	m_pPtLightSpinner=m_pContainer->add_spinner_to_panel(pPanel2,"Point Light %:  ",GLUI_SPINNER_INT,NULL,0,SetPtLight);
	m_pPtLightSpinner->set_int_limits(0,100);
	m_pPtLightSpinner->set_int_val(50);

	m_pContainer->add_column();

	GLUI_Panel* pPanel3=m_pContainer->add_panel("Acceleration");
	m_pMnThrstSpinner=m_pContainer->add_spinner_to_panel(pPanel3,"Motion Thrust: ",GLUI_SPINNER_FLOAT,NULL,0,SetMnThrst);
	m_pMnThrstSpinner->set_float_limits(0.1,10.0);
	m_pMnThrstSpinner->set_float_val(1.0);
	m_pContainer->add_separator_to_panel(pPanel3);
	m_pContainer->add_separator_to_panel(pPanel3);
	m_pRnAngleSpinner=m_pContainer->add_spinner_to_panel(pPanel3,"Rotation Angle:",GLUI_SPINNER_FLOAT,NULL,0,SetRnAngle);
	m_pRnAngleSpinner->set_float_limits(0.1,90.0);
	m_pRnAngleSpinner->set_float_val(1.0);

	m_pContainer->add_column();

	GLUI_Panel* pPanel4=m_pContainer->add_panel("Deceleration");
	m_pMnDecreaseSpinner=m_pContainer->add_spinner_to_panel(pPanel4,"Motion Decrease %:  ",GLUI_SPINNER_INT,NULL,0,SetMnDecrease);
	m_pMnDecreaseSpinner->set_int_limits(0,100);
	m_pMnDecreaseSpinner->set_int_val(1);
	m_pContainer->add_separator_to_panel(pPanel4);
	m_pContainer->add_separator_to_panel(pPanel4);
	m_pRnDecreaseSpinner=m_pContainer->add_spinner_to_panel(pPanel4,"Rotation Decrease %:",GLUI_SPINNER_INT,NULL,0,SetRnDecrease);
	m_pRnDecreaseSpinner->set_int_limits(0,100);
	m_pRnDecreaseSpinner->set_int_val(1);
}


void GluiMenu::InsertDirectory()
{
	for (int i=0; i<m_cDirectory.GetNumOfFiles(); i++)
	{
		#define ITEM_SIZE 16
		char aItem[ITEM_SIZE];

		int j;
		char* aFileName=m_cDirectory.GetFileName(i);
		for (j=0; j<ITEM_SIZE-2 && aFileName[j]!=0; j++)
			aItem[j]=aFileName[j];

		if (m_cDirectory.FileIsSubDir(i)==true)
			aItem[j++]='\\';
		aItem[j]=0;

		m_pFilesListbox->add_item(i,aItem);
	}
}


bool GluiMenu::ChangeDirectory()
{
	int iFileNum=m_pFilesListbox->get_int_val();
	if (m_cDirectory.FileIsSubDir(iFileNum)==false)
		return false;

	for (int i=0; i<m_cDirectory.GetNumOfFiles(); i++)
		m_pFilesListbox->delete_item(i);
	m_pFilesListbox->set_w(0);

	m_cDirectory.ChangeTo(iFileNum);
	InsertDirectory();
	return true;
}


void GluiMenu::ClearAll(int iId)
{
	m_pGluiMenu->m_bIsOn=false;
	m_pGluiMenu->m_pContainer->hide();
	m_pGluiMenu->m_eCommand=CLEAR;
}


void GluiMenu::OpenFile(int iId)
{
	if (m_pGluiMenu->ChangeDirectory()==true)
		return;

	m_pGluiMenu->m_bIsOn=false;
	m_pGluiMenu->m_pContainer->hide();
	m_pGluiMenu->m_eCommand=UPDATE;
}


void GluiMenu::SetAtLight(int iId)
{
	int iAtLight=m_pGluiMenu->m_pAtLightSpinner->get_int_val();
	m_pGluiMenu->m_pPtLightSpinner->set_int_val(100-iAtLight);

	m_pGluiMenu->m_pAtLightSpinner->first_callback=true;
	m_pGluiMenu->m_eCommand=REFRESH;
}


void GluiMenu::SetPtLight(int iId)
{
	int iPtLight=m_pGluiMenu->m_pPtLightSpinner->get_int_val();
	m_pGluiMenu->m_pAtLightSpinner->set_int_val(100-iPtLight);

	m_pGluiMenu->m_pPtLightSpinner->first_callback=true;
	m_pGluiMenu->m_eCommand=REFRESH;
}


void GluiMenu::SetMnThrst(int iId)
{
	m_pGluiMenu->m_pMnThrstSpinner->first_callback=true;
	m_pGluiMenu->m_eCommand=REFRESH;
}


void GluiMenu::SetRnAngle(int iId)
{
	m_pGluiMenu->m_pRnAngleSpinner->first_callback=true;
	m_pGluiMenu->m_eCommand=REFRESH;
}


void GluiMenu::SetMnDecrease(int iId)
{
	m_pGluiMenu->m_pMnDecreaseSpinner->first_callback=true;
	m_pGluiMenu->m_eCommand=REFRESH;
}


void GluiMenu::SetRnDecrease(int iId)
{
	m_pGluiMenu->m_pRnDecreaseSpinner->first_callback=true;
	m_pGluiMenu->m_eCommand=REFRESH;
}
