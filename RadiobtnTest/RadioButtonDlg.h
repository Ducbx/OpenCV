
// RadioButtonDlg.h : header file
//

#pragma once
#include "afxwin.h"

enum Operator
{
	ePLUS = 1,
	eMINUS,
	eMULTIPLY,
	eDEVIDE
};

// CRadioButtonDlg dialog
class CRadioButtonDlg : public CDialogEx
{
// Construction
public:
	CRadioButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RADIOBUTTON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtA;
	CEdit m_edtB;
	CEdit m_edtC;
	CButton m_btnExe;
	int m_radioPlus;
	int m_radioMinus;
	int m_radioMultiply;
	int m_radioDivide;

	afx_msg void OnBnClickedBtnExe();
	int getOperatorMode();
};
