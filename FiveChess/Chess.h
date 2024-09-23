#pragma once
#include "ChessDraw.h"
#include "ChessAI.h"
#include "ChessCommon.h"





enum	enumWinFlag	{FIGHTING,	    WHITE_WIN,	   BLACK_WIN,	    PEACE};		// FIGHTING	 �Ծ���		WHITE_WIN	�׷�Ӯ		 BLACK_WIN	�ڷ�Ӯ		PEACE ƽ��
enum	enumAIDepth	{AI_FOOLISH,	AI_PRIMARY,    AI_MIDDLE,	    AI_HIGH};	// AI_FOOLISH ����      AI_PRIMARY ����          AI_MIDDLE �м�         AI_HIGH  �߼�
enum	enumVSMode	{PERSON_VS_PERSON,	           PERSON_VS_MACHINE,	    MACHINE_VS_MACHINE};		// ���˶�ս���˻���ս��������ս

typedef struct
{
    int      iPieceNum;              // ��¼�����Ӹ���
    CPoint   ptWhite;                // ���һ�ΰ����λ��
    CPoint   ptBlack;                // ���һ�κ����λ��
    CPoint   ptLastCurPoint;         // ���һ�ε����ӽ���λ��
}STC_REGRET;    // ��¼���һ�ε�����λ�ã����ڻ������


class CChess
{
public:
	CChess(void);
	~CChess(void);

	void	    Init(CRect	rect);
	void	    Draw(CDC*	pDC);				    // �����
	void	    SetPiecePos(CPoint	ptCurrent);		// ���õ�ǰ���ӵ�λ��

	void	    NewGame();		    // ����Ϸ
	BOOL	    Regret();			// ����
	void	    SetVSMode(enumVSMode	emVSMode);	// ���ö�սģʽ
	void	    SetAIDepth(int	emAIDepth);	        // ����AI���̶ܳ�
	enumWinFlag	GetWinFlag();		                // ��ȡ��Ӯ״��
	CRect	    GetRectBoard();	    // ��ȡ��������	

private:
	enumChessColor	m_iPositionPiece[COLUMNS][ROWS];// ���ӵ���Ϣ
	CChessDraw      m_chessdraw;			        // ��ֻ�����
	CRect			m_rcBoard;				        // ��������	
	CPoint			m_ptCurrent;			        // ���ӵ�ǰλ��
	enumWinFlag	    m_emWin;			            // ��Ӯ״��
	enumVSMode	    m_emVSMode;		                // ��սģʽ
    STC_REGRET      m_stcLastPos;                   // ��¼���һ�ε�����λ��
    BOOL            m_bTurnBlack;                   // �Ƿ��ֵ��ڷ�����
    int	            m_emAIDepth;		            // AI���̶ܳ�  

	BOOL   IsWin(UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor);				              // �ڵ�uiCol�е�uiRow�У��ж��Ƿ�������������򷵻�TRUE
    BOOL   GetBestPosByAI(UINT&	uiCol,	UINT&	uiRow,	enumChessColor   emEnemyChessColor  = BLACK);     // ��ȡ��õ�����λ�ã�������Ϊ��ɫ
};

