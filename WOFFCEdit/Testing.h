#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include "InputCommands.h"

#include <vector>

// SelectDialogue dialog

class Inspector : public CDialogEx
{
	DECLARE_DYNAMIC(Inspector)

public:
	Inspector(CWnd* pParent, std::vector<SceneObject>* SceneGraph);   // modal // takes in out scenegraph in the constructor
	Inspector(CWnd* pParent = NULL);
	virtual ~Inspector();
	void SetObjectData(std::vector<SceneObject>* SceneGraph, int* Selection,InputCommands* m_input);	//passing in pointers to the data the class will operate on.

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();
	void CheckValues();

	std::vector<SceneObject>* m_sceneGraph;
	int* m_currentSelection;
	InputCommands* m_input;

	int current;
	float x_pos;
	float y_pos;
	float z_pos;
	float x_rot;
	float y_rot;
	float z_rot;
	float x_sca;
	float y_sca;
	float z_sca;
	bool Selected;
	DECLARE_MESSAGE_MAP()
public:
	// Control variable for more efficient access of the listbox
	CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedOk2();
	
	afx_msg void OnEnChangeEditY();
};


INT_PTR CALLBACK SelectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);