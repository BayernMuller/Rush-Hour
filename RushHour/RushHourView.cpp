
// RushHourView.cpp : CRushHourView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RushHour.h"
#endif

#include "RushHourDoc.h"
#include "RushHourView.h"
#include "RhMap.h"
#include "UserMap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRushHourView

IMPLEMENT_DYNCREATE(CRushHourView, CView)

BEGIN_MESSAGE_MAP(CRushHourView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_32773, &CRushHourView::OnCreateMode)
	ON_COMMAND(ID_32774, &CRushHourView::OnTestMap)
	ON_COMMAND(ID_32775, &CRushHourView::OnSaveMap)
	ON_COMMAND(ID_32776, &CRushHourView::OnOpenMap)
	ON_COMMAND(ID_32777, &CRushHourView::OnClear)
END_MESSAGE_MAP()

// CRushHourView ����/�Ҹ�

CRushHourView::CRushHourView() : m_pMap(nullptr), m_nSelectedBlock(NULL_BLOCK), m_MovingPt(-500,-500)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}



CRushHourView::~CRushHourView()
{
	delete m_pMap;
}

BOOL CRushHourView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

// CRushHourView �׸���


void CRushHourView::OnDraw(CDC* pDC)
{
	CRushHourDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.	
	CDC MemDC;
	CRect rect;
	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap *pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);
	if (m_pMap != nullptr)
	{
		m_pMap->DrawMap(&MemDC);
		m_pMap->DrawCar(&MemDC);
		m_pMap->DrawSelected(&MemDC);
		CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
		if (pUM != nullptr)
		{
			pUM->DrawBlock(&MemDC);
			if (m_nSelectedBlock != NULL_BLOCK)
			{
				pUM->DrawDragingBlock(&MemDC, m_MovingPt, m_nSelectedBlock);
			}
		}
	}
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();	
}


// CRushHourView �μ�

BOOL CRushHourView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CRushHourView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CRushHourView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CRushHourView ����

#ifdef _DEBUG
void CRushHourView::AssertValid() const
{
	CView::AssertValid();
}

void CRushHourView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRushHourDoc* CRushHourView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRushHourDoc)));
	return (CRushHourDoc*)m_pDocument;
}
#endif //_DEBUG




// CRushHourView �޽��� ó����


void CRushHourView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_pMap = new CRhMap(this);
}


void CRushHourView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (pUM != nullptr)
	{
		m_nSelectedBlock = pUM->SelectBlock(point);
	}
	if (m_pMap != nullptr)
	{
		m_pMap->OnClick(point);
	}	
	m_pt = point;
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}

void CRushHourView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (pUM != nullptr && m_nSelectedBlock != NULL_BLOCK && nFlags & VK_LBUTTON)
	{
		m_MovingPt = point;
		Invalidate(FALSE);
		return;
	}
	if (nFlags & VK_LBUTTON && m_pMap->GetSelectedCar() != nullptr)
	{
		m_pMap->CheckDirection(m_pt, point);
		Invalidate(FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CRushHourView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}

void CRushHourView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (m_nSelectedBlock != NULL_BLOCK && pUM != nullptr)
	{		
		pUM->OnPutBlock(point, m_nSelectedBlock);
		m_nSelectedBlock = NULL_BLOCK;
		m_MovingPt = CPoint(-1000, -1000);
		Invalidate(FALSE);
	}	
	CView::OnLButtonUp(nFlags, point);
}


void CRushHourView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nChar == VK_DELETE)
	{
		CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
		if (pUM)
			pUM->RemoveBlock();
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRushHourView::OnCreateMode()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (pUM)
	{
		delete m_pMap;
		m_pMap = new CRhMap(this);
		return;
	}
	delete m_pMap;
	m_pMap = new CUserMap(this);
	Invalidate(FALSE);
}

void CRushHourView::OnTestMap()
{
	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (pUM)
	{
		pUM->SwitchTestMode();
		Invalidate(FALSE);
	}
}

void CRushHourView::OnSaveMap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (pUM)
	{
		if (pUM->CanSave())
		{
			CString str(_T("Rush Hour Map (*.map)|*.map|��� ���� (*.*)|*.*|"));
			CFileDialog SaveDlg(FALSE, _T("map"), _T("*.map"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, str, NULL);
			if (SaveDlg.DoModal() == IDOK)
			{
				CString strPathName = SaveDlg.GetPathName();
				CFile file;
				file.Open(strPathName, CFile::modeCreate | CFile::modeWrite);
				CArchive ar(&file, CArchive::store);
				m_pMap->Serialize(ar);
				ar.Close();
				file.Close();
				Invalidate(FALSE);
			}
		}		
		else
		{
			AfxMessageBox(_T("�� �׽�Ʈ�� �Ϸ��Ͻʽÿ�."));
		}
	}
}

void CRushHourView::OnOpenMap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	CString str(_T("Rush Hour Map (*.map)|*.map|��� ���� (*.*)|*.*|"));
	CFileDialog OpenDlg(TRUE, _T("map"), _T("*.map"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, str, NULL);
	if (OpenDlg.DoModal() == IDOK)
	{
		CString strPathName = OpenDlg.GetPathName();
		CFile file;
		file.Open(strPathName, CFile::modeRead);
		CArchive ar(&file, CArchive::load);		
		m_pMap->Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate(FALSE);
	}
}

void CRushHourView::OnClear()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CUserMap *pUM = dynamic_cast<CUserMap*>(m_pMap);
	if (pUM)
	{
		AfxMessageBox(_T("â�۸�忡�� ���Ұ�"));
		return;
	}
	m_pMap->OnClear();
	Invalidate(FALSE);
}
