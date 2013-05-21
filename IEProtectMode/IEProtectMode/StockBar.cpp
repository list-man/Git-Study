// StockBar.cpp : Implementation of CStockBar

#include "stdafx.h"
#include "StockBar.h"


// CStockBar
LRESULT CStockBar::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CStockBar::SetSite(IUnknown *pUnkSite)
{
	m_spUnkSite.Release();
	if (pUnkSite)
		pUnkSite->QueryInterface(&m_spUnkSite);

	if (!m_hWnd)
	{
		CComQIPtr<IDockingWindowSite> spDkwndSite = pUnkSite;
		if (spDkwndSite)
		{
			HWND hDockingWnd = NULL;
			spDkwndSite->GetWindow(&hDockingWnd);
			if (hDockingWnd)
			{
				Create(hDockingWnd, CRect(0, 0, 100, 20), NULL, WS_CHILD|WS_VISIBLE);
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
	if (!fShow && m_spUnkSite)
	{
		CComQIPtr<IDockingWindowSite> spDkWndSite = m_spUnkSite;
		if (spDkWndSite)
		{
			return spDkWndSite->SetBorderSpaceDW(NULL, NULL);
		}
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
		m_spDockingWndSite->SetBorderSpaceDW(static_cast<IDockingWindow*>(this), prcBorder);
	}
	return E_NOTIMPL;
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
			pdbi->ptMinSize.y = 10;
		}
		
		if (pdbi->dwMask & DBIM_MAXSIZE)
		{
			pdbi->ptMaxSize.x= 1024;
			pdbi->ptMaxSize.y = 50;
		}

		if (pdbi->dwMask & DBIM_INTEGRAL)
		{
			pdbi->ptMinSize.y = 5;
		}

		if (pdbi->dwMask & DBIM_ACTUAL)
		{
			pdbi->ptActual.x = 200;
			pdbi->ptActual.y = 20;
		}

		if (pdbi->dwMask & DBIM_TITLE)
		{
			wcscpy(pdbi->wszTitle, L"My browser Tool bar");
		}

		if (pdbi->dwMask & DBIM_MODEFLAGS);
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
