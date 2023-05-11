// Inspector.cpp : implementation file
//

#include "stdafx.h"
#include "Testing.h"

// Inspector dialog

IMPLEMENT_DYNAMIC(Inspector, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(Inspector, CDialogEx)
					//ok button
	//ON_COMMAND(IDOK, &Inspector::End)
	ON_BN_CLICKED(IDOK, &Inspector::OnBnClickedOk)
	
	ON_BN_CLICKED(IDOK2, &Inspector::OnBnClickedOk2)
	ON_EN_KILLFOCUS(IDC_EDIT_Y, &Inspector::OnEnChangeEditY)
	//_EN_CHANGE(IDC_EDIT_Y, &Inspector::OnEnChangeEditY)
END_MESSAGE_MAP()


Inspector::Inspector(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_sceneGraph = SceneGraph;
}

Inspector::Inspector(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
	x_pos = 0;
	y_pos = 0;
	z_pos = 0;
	x_rot =0;
	y_rot = 0;
	z_rot = 0;
	x_sca = 0;
	y_sca = 0;
	z_sca = 0;
	Selected = false; current = 0;
}

Inspector::~Inspector()
{
}

///pass through pointers to the data in the tool we want to manipulate
void Inspector::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection,InputCommands* m_inp)
{
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;
	m_input = m_inp;
	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	current = *selection;

	if(current != -1)
	{
		x_pos = SceneGraph->at(*selection).posX;
		y_pos = SceneGraph->at(*selection).posY;
		z_pos = SceneGraph->at(*selection).posZ;
		x_rot= SceneGraph->at(*selection).rotX;
		y_rot =SceneGraph->at(*selection).rotY;
		z_rot =SceneGraph->at(*selection).rotZ;
		x_sca =SceneGraph->at(*selection).scaX;
		y_sca =SceneGraph->at(*selection).scaY;
		z_sca =SceneGraph->at(*selection).scaZ;
	}
		
	
	
}


void Inspector::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Text(pDX, IDC_EDIT_X, x_pos);
	DDX_Text(pDX, IDC_EDIT_Y, y_pos);
	DDX_Text(pDX, IDC_EDIT_Z, z_pos);

	DDX_Text(pDX, IDC_EDIT_ROT_X, x_rot);
	DDX_Text(pDX, IDC_EDIT_ROT_Y, y_rot);
	DDX_Text(pDX, IDC_EDIT_ROT_Z, z_rot);

	DDX_Text(pDX, IDC_EDIT_SCA_X, x_sca	);
	DDX_Text(pDX, IDC_EDIT_SCA_Y, y_sca);
	DDX_Text(pDX, IDC_EDIT_SCA_Z, z_sca);


	//stop scale becoming zero
	DDV_MinMaxFloat(pDX, x_sca, 0.2, 10.0);
	DDV_MinMaxFloat(pDX, y_sca, 0.2, 10.0);
	DDV_MinMaxFloat(pDX, z_sca, 0.2, 10.0);

	
}




BOOL Inspector::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//uncomment for modal only
/*	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (size_t i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.
		std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
		m_listBox.AddString(listBoxEntry.c_str());
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void Inspector::PostNcDestroy()
{
	DestroyWindow();
}




// Inspector message handlers callback   - We only need this if the dailogue is being setup-with createDialogue().  We are doing
//it manually so its better to use the messagemap
/*INT_PTR CALLBACK SelectProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		//	EndDialog(hwndDlg, wParam);
			DestroyWindow(hwndDlg);
			return TRUE;


		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
			break;
		}
	}

	return INT_PTR();
}*/

void Inspector::End()
{
	DestroyWindow();
}


void Inspector::CheckValues()
{
	if(x_sca <0.2 || x_sca >100)
	{
		if(x_sca <0.2)
		{
			x_sca = 0.2;
		}
		if(x_sca > 100)
		{
			x_sca = 100;
		}
		CString ts;
		ts.Format(_T("%f"), x_sca);
		SetDlgItemText(IDC_EDIT_SCA_X, ts);
	}
	if (y_sca < 0.2 || y_sca >10)
	{
		if (y_sca < 0.2)
		{
			y_sca = 0.2;
		}
		if (y_sca > 10)
		{
			y_sca = 10;
		}
		CString ts;
		ts.Format(_T("%f"), y_sca);
		SetDlgItemText(IDC_EDIT_SCA_Y, ts);
	}
	if (z_sca < 0.2 || z_sca >10)
	{
		if (z_sca < 0.2)
		{
			z_sca = 0.2;
		}
		if (z_sca > 10)
		{
			z_sca = 10;
		}
		CString ts;
		ts.Format(_T("%f"), z_sca);
		SetDlgItemText(IDC_EDIT_SCA_Z, ts);
	}
}

void Inspector::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();

	if(current != *m_currentSelection)
	{
		DestroyWindow();
	}
	else
	{
		UpdateData(true);  // snapshot ALL controls data
		
		UpdateData(false);

		CheckValues();
		if(!m_input->inspector)
		{
			//update the positions 
			m_sceneGraph->at(current).posX = x_pos;
			m_sceneGraph->at(current).posY = y_pos;
			m_sceneGraph->at(current).posZ = z_pos;

			//update the rotation varibles
			m_sceneGraph->at(current).rotX = x_rot;
			m_sceneGraph->at(current).rotY = y_rot;
			m_sceneGraph->at(current).rotZ = z_rot;

			//update the scale varibles
			m_sceneGraph->at(current).scaX = x_sca;
			m_sceneGraph->at(current).scaY = y_sca;
			m_sceneGraph->at(current).scaZ = z_sca;


			m_input->inspector = true;
		}

	}
	
}


INT_PTR CALLBACK SelectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);

void Inspector::OnBnClickedOk2()
{
	DestroyWindow();
	// TODO: Add your control notification handler code here
}





void Inspector::OnEnChangeEditY()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString text;
	//text.Format(_T("%f"), y_pos); // This will preserve your float format
	GetDlgItemText(IDC_EDIT_Y, text);
	y_pos = _ttof(text);
	// TODO:  Add your control notification handler code here
}
