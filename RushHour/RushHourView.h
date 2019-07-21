
// RushHourView.h : CRushHourView Ŭ������ �������̽�
//

#pragma once
class CRhMap;



class CRushHourView : public CView
{
protected: // serialization������ ��������ϴ�.
	CRushHourView();
	DECLARE_DYNCREATE(CRushHourView)

// Ư���Դϴ�.
public:
	CRushHourDoc* GetDocument() const;
// �۾��Դϴ�.
private:
	CRhMap *m_pMap;
	CPoint m_pt;
	CPoint m_MovingPt;
	BLOCK m_nSelectedBlock;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CRushHourView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPlayMap();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg void OnCreateMode();
	afx_msg void OnTestMap();
	afx_msg void OnSaveMap();
	afx_msg void OnOpenMap();
	afx_msg void OnClear();
};

#ifndef _DEBUG  // RushHourView.cpp�� ����� ����
inline CRushHourDoc* CRushHourView::GetDocument() const
   { return reinterpret_cast<CRushHourDoc*>(m_pDocument); }
#endif

