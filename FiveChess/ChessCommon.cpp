#include "StdAfx.h"
#include "ChessCommon.h"


void     SameColorAdder(UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor,    BOOL    bResetCount ,int &iColorCount,   BOOL&    bOver,   
                        const enumChessColor emChess[][ROWS],  int* piBlankCount )
{

    if(PtInBroad(uiCol, uiRow)) 
    {
        if(emChessColor	== emChess[uiCol][uiRow])
        {
            iColorCount++;
        }
        else   
        {
            if(bResetCount)
            {
                iColorCount = 0;
            }
            else
            {
                bOver   = TRUE;
            }
              
            if(piBlankCount)
            {
                if(0 == emChess[uiCol][uiRow])
                {
                    if((0 == (*piBlankCount))  ||  bOver)
                    {
                        (*piBlankCount)++;
                    }
                }
                else if(! bOver)
                {
                    (*piBlankCount)=0;
                }
            }
        }
    }  
}

void     GetSameColor(UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor,    int   *  iSameColor,  
                      const enumChessColor emChess[][ROWS] ,    int*    piCreaseDirect,  BOOL   bIgnoreBlank ,    int*    piBlankFlag)
{    	     
    int	iColTemp,	iRowTemp,	iCrease;
    BOOL    bBreak  =FALSE;

    memset(iSameColor,	 0,	 sizeof(iSameColor) * MAXCREASE);
    if(piCreaseDirect)
    {
        memset(piCreaseDirect,0, sizeof(piCreaseDirect) * MAXCREASE);
    }
    if(piBlankFlag)
    {
        memset(piBlankFlag,	  0, sizeof(piBlankFlag)    * MAXCREASE);
    }

    for(int iDirect = 0;    iDirect < 4;    iDirect++,  bBreak  =FALSE)
    {          
        int iBlankCount = 0;

        for(iCrease = -MAXCREASE;	! bBreak  &&  (iCrease <= MAXCREASE);	iCrease++)
        {
            if(bIgnoreBlank    &&  ! iCrease)
            {
                continue;
            }
            switch(iDirect)
            {
            case    0:   
                iColTemp     = uiCol + iCrease;
                iRowTemp   = uiRow;
                break;
            case    1:	
                iColTemp     = uiCol;
                iRowTemp   = uiRow + iCrease;
                break;
            case    2:	
                iColTemp     = uiCol + iCrease;
                iRowTemp   = uiRow + iCrease;
                break;
            case    3:  
                iColTemp     = uiCol + iCrease;
                iRowTemp   = uiRow - iCrease;
                break;
            default:
                break;
            }    
            if(PtInBroad(iColTemp, iRowTemp)) 
            {           
                SameColorAdder(iColTemp, iRowTemp,   emChessColor,   iCrease <= 0,   iSameColor[iDirect], bBreak,    emChess, &iBlankCount);     
            }
            else    if(iCrease > 0)
            {
                iCrease+=1;
                break;
            }
        }
      
        if(piCreaseDirect)
        {
            piCreaseDirect [iDirect] = iCrease   - 2;
        }

        if(piBlankFlag)
        {
            piBlankFlag[iDirect]     = iBlankCount;
        }
    }
}

BOOL    PtInBroad(UINT	uiCol,	UINT	uiRow)
{
    if((uiCol >= 0)	&&	(uiCol < COLUMNS)	&&	(uiRow >= 0)	&&	(uiRow < ROWS))	
    {
        return	TRUE;
    }
    return	FALSE;
}