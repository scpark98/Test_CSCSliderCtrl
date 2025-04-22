
// Test_CSCSliderCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_CSCSliderCtrl.h"
#include "Test_CSCSliderCtrlDlg.h"
#include "afxdialogex.h"

#include "../../Common/Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTestCSCSliderCtrlDlg 대화 상자



CTestCSCSliderCtrlDlg::CTestCSCSliderCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_CSCSLIDERCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCSCSliderCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_CHECK_HIDE_THUMB, m_check_hide_thumb);
	DDX_Control(pDX, IDC_CHECK_DISABLE, m_check_disable);
	DDX_Control(pDX, IDC_CHECK_FORCED_GRAY, m_check_forced_gray);
}

BEGIN_MESSAGE_MAP(CTestCSCSliderCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_CHECK_HIDE_THUMB, &CTestCSCSliderCtrlDlg::OnBnClickedCheckHideThumb)
	ON_BN_CLICKED(IDC_CHECK_DISABLE, &CTestCSCSliderCtrlDlg::OnBnClickedCheckDisable)
	ON_REGISTERED_MESSAGE(Message_CSCSliderCtrl, &CTestCSCSliderCtrlDlg::on_message_CSCSliderCtrl)
	ON_BN_CLICKED(IDC_CHECK_FORCED_GRAY, &CTestCSCSliderCtrlDlg::OnBnClickedCheckForcedGray)
END_MESSAGE_MAP()


// CTestCSCSliderCtrlDlg 메시지 처리기

BOOL CTestCSCSliderCtrlDlg::OnInitDialog()
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
	m_resize.Create(this);
	m_resize.Add(IDC_PROGRESS, 0, 0, 100, 0);
	m_resize.Add(IDC_SLIDER, 0, 0, 100, 100);
	m_resize.Add(IDOK, 100, 100, 0, 0);
	m_resize.Add(IDCANCEL, 100, 100, 0, 0);

	DWORD is_auto_setup = 0;
	get_registry_int(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\LinkMeMineSE\\LMMAgent"), _T("is auto setup"), &is_auto_setup);


	m_slider.set_range(50, 100);
	m_slider.SetPos(75);
	m_slider.set_style(CSCSliderCtrl::style_thumb_round);
	m_slider.set_tic_freq(10, true);
	//m_slider.set_track_height(3);
	m_slider.set_text_style(CSCSliderCtrl::text_style_percentage);
	m_slider.set_font_size(6);
	m_slider.set_color_theme(CSCColorTheme::color_theme_linkmemine);
	m_slider.set_thumb_color(gRGB(64, 73, 88));
	m_slider.set_text_color(gRGB(64, 73, 88));
	//m_slider.set_back_color(RGB(64, 73, 88));
	//m_slider.set_track_color(RGB(103, 117, 139), RGB(41, 47, 55));
	//m_slider.set_track_height(5);
	m_slider.set_use_slide();

	//m_progress.set_style()

	m_progress.use_slider();
	m_progress.SetRange(0, 1000);
	m_progress.SetPos(50);
	m_progress.set_back_color(RGB(255, 0, 0));
	m_progress.set_back_track_color(RGB(0, 0, 255));

	RestoreWindowPosition(&theApp, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestCSCSliderCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestCSCSliderCtrlDlg::OnPaint()
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
HCURSOR CTestCSCSliderCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestCSCSliderCtrlDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}

void CTestCSCSliderCtrlDlg::OnBnClickedCheckHideThumb()
{
	m_slider.hide_thumb(m_check_hide_thumb.GetCheck() == BST_CHECKED);
}

void CTestCSCSliderCtrlDlg::OnBnClickedCheckDisable()
{
	m_slider.EnableWindow(m_check_disable.GetCheck() != BST_CHECKED);
}

LRESULT CTestCSCSliderCtrlDlg::on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam)
{
	m_check_hide_thumb.SetCheck(BST_UNCHECKED);
	m_slider.hide_thumb(false);
	return 0;
}

void CTestCSCSliderCtrlDlg::OnBnClickedCheckForcedGray()
{
	m_slider.set_forced_gray(m_check_forced_gray.GetCheck() == BST_CHECKED);
}
