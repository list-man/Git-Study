// StockBar.h : Declaration of the CStockBar

#pragma once
#include "resource.h"       // main symbols



#include "IEProtectMode_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CStockBar

class ATL_NO_VTABLE CStockBar :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStockBar, &CLSID_StockBar>,
	public IDispatchImpl<IStockBar, &IID_IStockBar, &LIBID_IEProtectModeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDeskBand,
	public IObjectWithSite,
	public CWindowImpl<CStockBar>
{
public:
	CStockBar()
	{
		::MessageBox(NULL, L"ToolBar", NULL, MB_OK);
		m_dwBandId = 0;
		m_dwViewMode = 0;
	}

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STOCKBAR)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStockBar)
	COM_INTERFACE_ENTRY(IStockBar)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDeskBand)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

BEGIN_MSG_MAP(CStockBar)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
END_MSG_MAP()

public:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	// interface IObjectWithSite.
	STDMETHOD(SetSite)(IUnknown *pUnkSite);
	STDMETHOD(GetSite)(REFIID riid, void **ppvSite);
	// interface IDeskBand.
	STDMETHOD(GetWindow)(HWND *phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);
	STDMETHOD(ShowDW)(BOOL fShow);
	STDMETHOD(CloseDW)(DWORD dwReserved);
	STDMETHOD(ResizeBorderDW)(LPCRECT prcBorder, IUnknown *punkToolbarSite, BOOL fReserved);
	STDMETHOD(GetBandInfo)(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO *pdbi);
public:


protected:
	CComPtr<IUnknown>	m_spUnkSite;
	CComPtr<IDockingWindowSite>	m_spDockingWndSite;
	DWORD	m_dwBandId;
	DWORD	m_dwViewMode;
};

OBJECT_ENTRY_AUTO(__uuidof(StockBar), CStockBar)
