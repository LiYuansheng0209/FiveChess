#include "StdAfx.h"
#include "ChessAI.h"


const   double SCORE_WHITE[][5]   =   {   {0,  0, 0,	0,	10000000},   {1,     25,	 500,	 2500,   10000000},  {5,    100,	 2500,   50000,   	10000000} };
const   double SCORE_BLACK[][5]   =   {   {0,  0, 0,	0,	-1000000},   {-5,   -100,	-500,   -10000,	-1000000 },  {-25,  -500,	-10000,	-250000,	-1000000} };

long double    GetScore(UINT uiCol,    UINT  uiRow,  const  enumChessColor emChess[][ROWS],  BOOL   bIgnoreBlank   = FALSE)   
{    
    int iSameColor[MAXCREASE];
    int iBlankFlag[MAXCREASE]   = {0};                         

    GetSameColor(uiCol, uiRow,  emChess[uiCol][uiRow],   iSameColor,    emChess, NULL,    bIgnoreBlank,   iBlankFlag);
     
    long double dbScore    = 0;
    for(int m = 0;  m < MAXCREASE;	m++)
    {
        int i   = iBlankFlag[m];
        int j   = iSameColor[m] - 1;
        
        if(WHITE  == emChess[uiCol][uiRow])
        {
            dbScore  += SCORE_WHITE[i][j];     
        }
        else
        {
            dbScore  += SCORE_BLACK[i][j];     
        }
    }
    
    return  dbScore;
}

long double ScoreEvaluate(const  enumChessColor emChess[][ROWS],  BOOL   bIgnoreBlank   = FALSE)
{
    long double dbScoreSum   = 0;
    for(int i=0;  i<ROWS;  i++)
    {
        for(int j=0;  j<ROWS;  j++)
        {
            if(NONE !=  emChess[i][j])   
            {                   
                dbScoreSum   += GetScore(i,j, emChess,    bIgnoreBlank);
            }
        }
    }

    return  dbScoreSum;
}


long double AlphaBetaMin( long double dbAlphaMin, long double dbBetaMax, int iDepthleft ,  enumChessColor emChess[][ROWS],   POINT& ptBest) ;
long double AlphaBetaMax( long double dbAlphaMin, long double dbBetaMax, int iDepthleft ,  enumChessColor emChess[][ROWS],   POINT& ptBest) 
{
    ptBest  = CPoint(-1, -1);    
    if ( iDepthleft == 0 ) 
    {
        return ScoreEvaluate(emChess); 
    }
    CPoint  ptTmp;  

    for(int i=0;  i<ROWS;  i++)
    {
        for(int j=0;  j<ROWS;  j++)
        {
            if(NONE ==  emChess[i][j])
            {
                if(ptBest.x  == -1)   
                {
                    ptBest  = CPoint(i, j);
                }

                emChess[i][j] = WHITE ;   

                long double   dbScore = AlphaBetaMin( dbAlphaMin, dbBetaMax, iDepthleft - 1,   emChess,   ptTmp); 
                             
                emChess[i][j] = NONE;      

                if( dbScore >= dbBetaMax )      
                {
                    ptBest  = CPoint(i, j);
                    return dbBetaMax;    
                }
                if( dbScore > dbAlphaMin )
                {
                    ptBest  = CPoint(i, j);
                    dbAlphaMin = dbScore;  
                }
            }
        }
    }
    return dbAlphaMin;    //Max
}

long double AlphaBetaMin( long double dbAlphaMin, long double dbBetaMax, int iDepthleft ,  enumChessColor emChess[][ROWS],   POINT& ptBest) 
{
    ptBest  = CPoint(-1, -1);
    if ( iDepthleft == 0 ) 
    {     
        return ScoreEvaluate(emChess);         
    }

    for(int i=0;  i<ROWS;  i++)
    {
        for(int j=0;  j<ROWS;  j++)
        {
            if(NONE ==  emChess[i][j])
            {
                emChess[i][j] = BLACK ;  

                long double   dbScore = AlphaBetaMax( dbAlphaMin, dbBetaMax, iDepthleft - 1,   emChess,   ptBest);

                emChess[i][j] = NONE;   
               
                if( dbScore <= dbAlphaMin )  
                {   
                    ptBest  = CPoint(i, j);
                    return dbAlphaMin;         
                }
                if( dbScore < dbBetaMax )
                {
                    ptBest  = CPoint(i, j);
                    dbBetaMax = dbScore; 
                }
            }
        }
    }
    return dbBetaMax; // Min
}




// ------------------ AI  Function ---------------------------------
 
BOOL    AIPrimary (POINT &pt ,  enumChessColor emChess[][ROWS])
{
    AlphaBetaMax(-1e10, 1e11, 1, emChess, pt);

    if(pt.x  == -1)   
    {
        return  FALSE; 
    }
    return  TRUE;
}

BOOL    AIHigh    (POINT &pt ,  enumChessColor emChess[][ROWS])
{
    AlphaBetaMax(-1e7, 1e8, 2, emChess, pt);
    
    if(pt.x  == -1)   
    {
        return  FALSE; 
    }
    return  TRUE;
}
