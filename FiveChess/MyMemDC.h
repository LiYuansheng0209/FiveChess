#ifndef _MYMEMDC_H_
#define _MYMEMDC_H_


class CMyMemDC : public CDC
{
private:
	CBitmap m_bitmap;		
	CBitmap* m_oldBitmap;	
	CDC* m_pDC;			
	CRect m_rect;		
	BOOL m_bMemDC;	

public:

	CMyMemDC(CDC* pDC, const CRect* pRect = NULL) : CDC()
	{
		ASSERT(pDC != NULL);

		m_pDC = pDC;
		m_oldBitmap = NULL;
		m_bMemDC = !pDC-> IsPrinting();

		if (pRect == NULL) 
		{
			pDC-> GetClipBox(&m_rect);
		} 
		else 
		{
			m_rect = *pRect;
		}

		if (m_bMemDC) 
		{
			CreateCompatibleDC(pDC);
			pDC-> LPtoDP(&m_rect);

			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_oldBitmap = SelectObject(&m_bitmap);

			SetMapMode(pDC-> GetMapMode());
			pDC-> DPtoLP(&m_rect);
			SetWindowOrg(m_rect.left, m_rect.top);
		} 
		else 
		{
			m_bPrinting = pDC-> m_bPrinting;
			m_hDC = pDC-> m_hDC;
			m_hAttribDC = pDC-> m_hAttribDC;
		}

		FillSolidRect(m_rect, pDC-> GetBkColor());
	}


	~CMyMemDC()
	{
		if (m_bMemDC) 
		{
			m_pDC-> BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);

			SelectObject(m_oldBitmap);
		} 
		else 
		{
			m_hDC = m_hAttribDC = NULL;
		}
	}

	CMyMemDC* operator-> ()
	{
		return this;
	}

	operator CMyMemDC*()
	{
		return this;
	}
};

#endif