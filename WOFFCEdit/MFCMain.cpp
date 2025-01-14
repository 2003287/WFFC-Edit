#include "MFCMain.h"
#include "resource.h"
#include "Testing.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ARC_BALL_CAM, &MFCMain::CameraButton2)
	ON_COMMAND(MOV_CAM, &MFCMain::CameraButton1)
    ON_BN_CLICKED(ID_MODESWITCh, &MFCMain::ModeSwitch)
    ON_BN_CLICKED(ID_InspecOpen, &MFCMain::OpenInspector)
    ON_BN_CLICKED(ID_ZOOM, &MFCMain::Zoom)
    ON_BN_CLICKED(ID_DELOBJECT, &MFCMain::DeleteObject)
    ON_BN_CLICKED(ID_COPY, &MFCMain::CopyObject)
    ON_BN_CLICKED(ID_BUTTONPASTE, &MFCMain::PasteObject)
	//ON_COMMAND(ID_MODESWITCh, &MFCMain::ModeSwitch)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
	
	
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);	
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::ToolBarButton1()
{
	
	m_ToolSystem.onActionSave();
}

void MFCMain::CameraButton1()
{
	m_ToolSystem.Camera_Update((1));
}

void MFCMain::CameraButton2()
{
	m_ToolSystem.Camera_Update((2));
}

void MFCMain::ModeSwitch()
{
	m_ToolSystem.GameModeSwitch();
	
}

void MFCMain::OpenInspector()
{
	if(m_ToolSystem.m_selectedObject != -1)
	{
		m_Inspector.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject, &m_ToolSystem.m_toolInputCommands);
		m_Inspector.Create(IDD_DIALOG2);	//Start up modeless
		m_Inspector.ShowWindow(SW_SHOW);	//show modeless
		//m_Inspector.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
		m_ToolSystem.GameModeSet(2);

	}
	
	//m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::Zoom()
{
	if (m_ToolSystem.m_selectedObject != -1)
	{
		m_ToolSystem.m_toolInputCommands.Zoom = true;
	}
}

void MFCMain::DeleteObject()
{
	if (m_ToolSystem.m_selectedObject != -1)
	{
		m_ToolSystem.m_toolInputCommands.delObject = true;
	}
}

void MFCMain::CopyObject()
{
	if (m_ToolSystem.m_selectedObject != -1)
	{
		m_ToolSystem.m_toolInputCommands.copyNum = true;
	}
}

void MFCMain::PasteObject()
{

	if (m_ToolSystem.m_toolInputCommands.copyFirst)
	{
		m_ToolSystem.m_toolInputCommands.paste = true;
	}

}




MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
