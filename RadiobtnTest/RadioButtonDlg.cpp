
// RadioButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadioButton.h"
#include "RadioButtonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRadioButtonDlg dialog



CRadioButtonDlg::CRadioButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RADIOBUTTON_DIALOG, pParent)
	, m_radioPlus(0)
	, m_radioMinus(0)
	, m_radioMultiply(0)
	, m_radioDivide(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRadioButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_A, m_edtA);
	DDX_Control(pDX, IDC_EDT_B, m_edtB);
	DDX_Control(pDX, IDC_EDT_C, m_edtC);
	DDX_Control(pDX, IDC_BTN_EXE, m_btnExe);
	DDX_Check(pDX, IDC_RADIO_PLUS, m_radioPlus);
	DDX_Check(pDX, IDC_RADIO_MINUS, m_radioMinus);
	DDX_Check(pDX, IDC_RADIO_MUL, m_radioMultiply);
	DDX_Check(pDX, IDC_RADIO_DIVIDE, m_radioDivide);
}

BEGIN_MESSAGE_MAP(CRadioButtonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXE, &CRadioButtonDlg::OnBnClickedBtnExe)
END_MESSAGE_MAP()


// CRadioButtonDlg message handlers

BOOL CRadioButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_radioPlus = 1;
	UpdateData(FALSE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRadioButtonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRadioButtonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRadioButtonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRadioButtonDlg::OnBnClickedBtnExe()
{
	UpdateData(TRUE);
	CString strA;
	CString strB;

	m_edtA.GetWindowText(strA);
	m_edtB.GetWindowText(strB);

	// double dA = atof(strA); -->non unicode 
	double dA = _wtof(strA);
	double dB = _wtof(strB);
	double dC = 0.0;

	int mode = getOperatorMode();
	switch (mode)
	{
		case Operator::ePLUS: 
			dC = dA + dB;
			break;
		case Operator::eMINUS:
			dC = dA - dB;
			break;
		case Operator::eMULTIPLY:
			dC = dA*dB;
			break;
		case Operator::eDEVIDE:
			if (dB == 0)
			{
				MessageBox(L"B can not be zero");
			}
			else
			{
				dC = dA / dB;
			}
			break;
	}
	CString strC;
	strC.Format(_T("%f"),dC);
	m_edtC.SetWindowText(strC);
	UpdateData(FALSE);

}

int CRadioButtonDlg::getOperatorMode()
{
	if (m_radioPlus) return Operator::ePLUS;
	if (m_radioMinus) return Operator::eMINUS;
	if (m_radioMultiply) return Operator::eMULTIPLY;
	if (m_radioDivide) return Operator::eDEVIDE;
}