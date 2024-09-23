#pragma once
#include "afxwin.h"
#include "Chess.h"


// CDialogMore 对话框

class CDialogMore : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMore)

public:
	CDialogMore(CWnd* pParent = NULL);
	virtual ~CDialogMore();

// 对话框数据
	enum { IDD = IDD_DIALOG_MORE };

private:
    CChess*  m_pChess;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    CComboBox m_comboxAI;
    CComboBox m_comboxVSMode;
    virtual BOOL OnInitDialog();
    void    SetChess(CChess  *pChess);
};
