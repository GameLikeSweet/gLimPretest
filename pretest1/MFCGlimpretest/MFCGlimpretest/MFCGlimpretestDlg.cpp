
// MFCGlimpretestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCGlimpretest.h"
#include "MFCGlimpretestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:wWinMainCRTStartup /SUBSYSTEM:CONSOLE")
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCGlimpretestDlg 대화 상자



CMFCGlimpretestDlg::CMFCGlimpretestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGLIMPRETEST_DIALOG, pParent)
	, radius(0)
	, border(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGlimpretestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, radius);
	DDX_Text(pDX, IDC_EDIT_BORDER, border);
}

BEGIN_MESSAGE_MAP(CMFCGlimpretestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SET_DATA, &CMFCGlimpretestDlg::OnBnClickedBtnSetData)
	ON_BN_CLICKED(IDC_RESET, &CMFCGlimpretestDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CMFCGlimpretestDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CMFCGlimpretestDlg::OnBnClickedBtnThread)
END_MESSAGE_MAP()


// CMFCGlimpretestDlg 메시지 처리기

BOOL CMFCGlimpretestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	m_pDlgImage1 = new CDlgImage;
	m_pDlgImage1->m_pParent = this;
	m_pDlgImage1->Create(IDD_CDlgImage, this);
	m_pDlgImage1->MoveWindow(0, 0, 720, 640);
	m_pDlgImage1->ShowWindow(SW_SHOW);

	m_pDlgImage1->Invalidate();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCGlimpretestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCGlimpretestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCGlimpretestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCGlimpretestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pDlgImage1) delete(m_pDlgImage1);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMFCGlimpretestDlg::OnBnClickedBtnSetData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if (m_pDlgImage1)
	{
		m_pDlgImage1->nBorder = border;
		m_pDlgImage1->nRadius = radius;
		m_pDlgImage1->Invalidate();
	}

	UpdateData(FALSE);
}


void CMFCGlimpretestDlg::OnBnClickedReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_pDlgImage1) 
	{
		m_pDlgImage1->ResetImage();
	} 

}


void CMFCGlimpretestDlg::OnBnClickedBtnRandom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_pDlgImage1)
	{
		m_pDlgImage1->ResetImage();
		m_pDlgImage1->Random();
	}
}


void CMFCGlimpretestDlg::OnBnClickedBtnThread()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.;

	std::thread t0([this]() {
		for (int i = 0; i < 10; ++i)
		{
			this->m_pDlgImage1->Random();
			this->m_pDlgImage1->UpdateCoordLabel();
			this->m_pDlgImage1->Invalidate(FALSE);
			Sleep(500);
		}
		});

	t0.detach();
}
