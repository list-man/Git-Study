// StockBar.cpp : Implementation of CStockBar

#include "stdafx.h"
#include "StockBar.h"


// CStockBar
LRESULT CStockBar::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (SUCCEEDED(IEIsProtectedModeProcess(&m_IeProtectedMode)) && m_IeProtectedMode)
		::MessageBox(m_hWnd, L"IE is running in protect mode now!", NULL, MB_OK);

	m_btn0.Create(m_hWnd, CRect(10, 10, 100, 40), _T("Open Mutex1"), WS_CHILD|WS_VISIBLE, 0, IDC_BTN0);
	m_btn1.Create(m_hWnd, CRect(10, 60, 100, 100), _T("Open Mutex2"), WS_CHILD|WS_VISIBLE, 0, IDC_BTN1);

	m_SendMsgbtn0.Create(m_hWnd, CRect(140, 10, 240, 40), _T("Send Message1"), WS_CHILD|WS_VISIBLE, 0, IDC_SENDMSGBTN0);
	m_SendMsgbtn1.Create(m_hWnd, CRect(140, 60, 240, 100), _T("Send Message2"), WS_CHILD|WS_VISIBLE, 0, IDC_SENDMSGBTN1);

	m_RunExbtn0.Create(m_hWnd, CRect(10, 130, 100, 170), _T("Run Exe0"), WS_CHILD|WS_VISIBLE, 0, IDC_RUNEXEBTN0);
	m_RunExbtn1.Create(m_hWnd, CRect(10, 190, 100, 230), _T("Run Exe1"), WS_CHILD|WS_VISIBLE, 0, IDC_RUNEXEBTN1);

	m_SaveLogbtn0.Create(m_hWnd, CRect(140, 130, 230, 170), _T("Save Log0"), WS_CHILD|WS_VISIBLE, 0, IDC_SAVELOGBTN0);
	m_SaveLogbtn1.Create(m_hWnd, CRect(140, 190, 230, 230), _T("Save Log1"), WS_CHILD|WS_VISIBLE, 0, IDC_SAVELOGBTN1);
	return 0;
}

LRESULT CStockBar::OnOpenMutex1(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	::MessageBox(m_hWnd, _T("OpenMutex1"), NULL, MB_OK);
	return 0;
}

LRESULT CStockBar::OnOpenMutex2(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

LRESULT CStockBar::OnSendMsg1(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

LRESULT CStockBar::OnSendMsg2(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

LRESULT CStockBar::OnRunExe1(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

LRESULT CStockBar::OnRunExe2(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

LRESULT CStockBar::OnSaveLog1(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

LRESULT CStockBar::OnSaveLog2(WORD nId, WORD nMsg, HWND hWnd, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CStockBar::SetSite(IUnknown *pUnkSite)
{
	__super::SetSite(pUnkSite);

	if (!m_hWnd)
	{
		CComQIPtr<IOleWindow> spOleWnd = pUnkSite;
		if (spOleWnd)
		{
			HWND hDockingWnd = NULL;
			spOleWnd->GetWindow(&hDockingWnd);
			if (hDockingWnd)
			{
				Create(hDockingWnd, CRect(0, 0, 100, 110), NULL, WS_CHILD|WS_VISIBLE);
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CStockBar::GetSite(REFIID riid, void **ppvSite)
{
	CheckPointer(ppvSite, E_INVALIDARG);

	if (!m_spUnkSite)
	{
		return E_FAIL;
	}
	else
	{
		m_spUnkSite->QueryInterface(riid, ppvSite);
	}

	return *ppvSite ? S_OK:E_NOTIMPL;
}

STDMETHODIMP CStockBar::GetWindow(HWND *phwnd)
{
	CheckPointer(phwnd, E_INVALIDARG);

	*phwnd = m_hWnd;
	return S_OK;
}

STDMETHODIMP CStockBar::ContextSensitiveHelp(BOOL fEnterMode)
{
	return S_OK;
}

STDMETHODIMP CStockBar::ShowDW(BOOL fShow)
{
	ShowWindow(fShow ? SW_SHOWNORMAL:SW_HIDE);
	if (!fShow && m_spDockingWndSite)
	{
		return m_spDockingWndSite->SetBorderSpaceDW(NULL, NULL);
	}

	return S_OK;
}

STDMETHODIMP CStockBar::CloseDW(DWORD dwReserved)
{
	if (m_hWnd)
		DestroyWindow();

	// save any persistent information.

	return S_OK;
}

STDMETHODIMP CStockBar::ResizeBorderDW(LPCRECT prcBorder, IUnknown *punkToolbarSite, BOOL fReserved)
{
	m_spDockingWndSite.Release();
	if (punkToolbarSite)
		punkToolbarSite->QueryInterface(__uuidof(IDockingWindowSite), (void**)&m_spDockingWndSite);

	if (m_spDockingWndSite)
	{
		return m_spDockingWndSite->SetBorderSpaceDW(static_cast<IDockingWindow*>(this), prcBorder);
	}

	return S_OK;
}

STDMETHODIMP CStockBar::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO *pdbi)
{
	m_dwBandId = dwBandID;
	m_dwViewMode = dwViewMode;

	if (pdbi)
	{
		if (pdbi->dwMask & DBIM_MINSIZE)
		{
			pdbi->ptMinSize.x = 100;
			pdbi->ptMinSize.y = 100;
		}
		
		if (pdbi->dwMask & DBIM_MAXSIZE)
		{
			pdbi->ptMaxSize.x= 1024;
			pdbi->ptMaxSize.y = 500;
		}

		if (pdbi->dwModeFlags & DBIMF_VARIABLEHEIGHT && pdbi->dwMask & DBIM_INTEGRAL)
		{
			pdbi->ptIntegral.y = 5;
		}

		if (pdbi->dwMask & DBIM_ACTUAL)
		{
			pdbi->ptActual.x = 200;
			pdbi->ptActual.y = 40;
		}

		if (pdbi->dwMask & DBIM_TITLE)
		{
			wcscpy_s(pdbi->wszTitle, L"My browser Tool bar");
		}

		if (pdbi->dwMask & DBIM_MODEFLAGS)
		{
			pdbi->dwModeFlags = DBIMF_NORMAL | DBIMF_BKCOLOR;
		}

		if (pdbi->dwModeFlags & DBIM_BKCOLOR)
		{
			if (pdbi->dwModeFlags & DBIMF_BKCOLOR)
				pdbi->crBkgnd = RGB(255, 0, 0);
		}
	}

	return S_OK;
}
