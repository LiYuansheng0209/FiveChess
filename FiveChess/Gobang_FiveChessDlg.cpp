#include "stdafx.h"
#include "Gobang_FiveChess.h"
#include "Gobang_FiveChessDlg.h"
#include "afxdialogex.h"

#include "DialogMore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


BEGIN_EASYSIZE_MAP(CGobang_FiveChessDlg)
	EASYSIZE(IDC_BUTTON_GAME_START,	ES_KEEPSIZE,	ES_BORDER,
        ES_BORDER,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BUTTON_REGRET,	ES_KEEPSIZE,	ES_BORDER,
        ES_BORDER,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BUTTON_MORE,	ES_KEEPSIZE,	ES_BORDER,
        ES_BORDER,ES_KEEPSIZE,0)

END_EASYSIZE_MAP



CGobang_FiveChessDlg::CGobang_FiveChessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGobang_FiveChessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}
   
CGobang_FiveChessDlg::~CGobang_FiveChessDlg()
{   
}

void CGobang_FiveChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGobang_FiveChessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_GAME_START, &CGobang_FiveChessDlg::OnBnClickedButtonGameStart)
	ON_BN_CLICKED(IDC_BUTTON_REGRET, &CGobang_FiveChessDlg::OnBnClickedButtonRegret)
	ON_BN_CLICKED(IDC_BUTTON_MORE, &CGobang_FiveChessDlg::OnBnClickedButtonMore)
    ON_WM_SIZE()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



BOOL CGobang_FiveChessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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


	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);		

	// TODO: 在此添加额外的初始化代码
	CRect   rcClient;

	GetClientRect(&rcClient);
	m_chess.Init(rcClient);

    INIT_EASYSIZE;
	return TRUE; 
}

void CGobang_FiveChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGobang_FiveChessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

        CRect   rcBtnStart, rcBtnRegret, rcBtnMore;
        CRgn    rgnChildWnd,    rgnBtnStart,    rgnBtnRegret,    rgnBtnMore;			
		CDC*	pDC	= GetDC();	

        GetDlgItem(IDC_BUTTON_GAME_START)->GetWindowRect(rcBtnStart);
        GetDlgItem(IDC_BUTTON_REGRET)->GetWindowRect(rcBtnRegret);
        GetDlgItem(IDC_BUTTON_MORE)->GetWindowRect(rcBtnMore);
        ScreenToClient(rcBtnStart);
        ScreenToClient(rcBtnRegret);
        ScreenToClient(rcBtnMore);

        rgnBtnStart.CreateRectRgnIndirect(rcBtnStart);
        rgnBtnRegret.CreateRectRgnIndirect(rcBtnRegret);   
        rgnBtnMore.CreateRectRgnIndirect(rcBtnMore);   
        rgnChildWnd.CreateRectRgn(0, 0, 0, 0);
        rgnChildWnd.CombineRgn(&rgnBtnStart, &rgnBtnRegret, RGN_OR);
        rgnChildWnd.CombineRgn(&rgnChildWnd, &rgnBtnMore, RGN_OR);
        pDC->SelectClipRgn(&rgnChildWnd, RGN_DIFF);

		m_chess.Draw(pDC);

        pDC->SelectClipRgn(NULL);
        rgnBtnStart.DeleteObject();
        rgnBtnRegret.DeleteObject();
        rgnBtnMore.DeleteObject();
        rgnChildWnd.DeleteObject();
		ReleaseDC(pDC);
	}
}

HCURSOR CGobang_FiveChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGobang_FiveChessDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_chess.SetPiecePos(point);
	Invalidate();

    switch(m_chess.GetWinFlag())
    {
    case    WHITE_WIN:
        AfxMessageBox(_T("白旗赢"));
        break;
    case    BLACK_WIN:
        AfxMessageBox(_T("黑旗赢"));
        break;
    case    PEACE:
        AfxMessageBox(_T("平局"));
        break;
    default:
        break;
    }

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CGobang_FiveChessDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CGobang_FiveChessDlg::OnBnClickedButtonGameStart()
{
    m_chess.NewGame();
    Invalidate();
}


void CGobang_FiveChessDlg::OnBnClickedButtonRegret()
{
    if(! m_chess.Regret())
    {
        AfxMessageBox(_T("你已使用完悔棋次数"));
    }
    Invalidate();
}


void CGobang_FiveChessDlg::OnBnClickedButtonMore()
{
    CDialogMore* dlgMore    = new   CDialogMore;

	dlgMore->Create(IDD_DIALOG_MORE);   	
    dlgMore->ShowWindow(SW_SHOW);  

    dlgMore->SetChess(&m_chess);

}


void CGobang_FiveChessDlg::OnSize(UINT nType, int cx, int cy)
{       
    CDialogEx::OnSize(nType, cx, cy);   

    CRect	rcClient;
	GetClientRect(&rcClient);

	m_chess.Init(rcClient);

    UPDATE_EASYSIZE;
    Invalidate();
}


void CGobang_FiveChessDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect   rcBoard = m_chess.GetRectBoard();
    if(rcBoard.PtInRect(point))
    {
        HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS); 
        SetCursor(hCursor);	
    }

    CDialogEx::OnMouseMove(nFlags, point);
}
