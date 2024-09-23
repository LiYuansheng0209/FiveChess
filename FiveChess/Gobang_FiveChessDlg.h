#pragma once
#include "Chess.h"

// CGobang_FiveChessDlg �Ի���
class CGobang_FiveChessDlg : public CDialogEx
{
    DECLARE_EASYSIZE
// ����
public:
	CGobang_FiveChessDlg(CWnd* pParent = NULL);	// ��׼���캯��
    CGobang_FiveChessDlg::~CGobang_FiveChessDlg();

// �Ի�������
	enum { IDD = IDD_GOBANG_FIVECHESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CChess		m_chess;	// ����
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonGameStart();
	afx_msg void OnBnClickedButtonRegret();
	afx_msg void OnBnClickedButtonMore();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
