// IEProtectMode.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "IEProtectMode_i.h"
#include "dllmain.h"


// Used to determine whether the DLL can be unloaded by OLE.
STDAPI DllCanUnloadNow(void)
{
			return _AtlModule.DllCanUnloadNow();
	}

// Returns a class factory to create an object of the requested type.
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
		return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
STDAPI DllRegisterServer(void)
{
	HKEY hKeyLocal = NULL;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Internet Explorer\\Toolbar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyLocal, NULL);
	RegSetValueEx(hKeyLocal, _T("{D468F21D-499B-4771-9878-66DF76CED414}"), 0, REG_BINARY, NULL, 0);
	RegCloseKey(hKeyLocal);
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _AtlModule.DllRegisterServer();
		return hr;
}

// DllUnregisterServer - Removes entries from the system registry.
STDAPI DllUnregisterServer(void)
{
	HKEY hKeyLocal = NULL;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Internet Explorer\\Toolbar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyLocal, NULL);
	RegDeleteValue(hKeyLocal, _T("{D468F21D-499B-4771-9878-66DF76CED414}"));
	RegCloseKey(hKeyLocal);

	HRESULT hr = _AtlModule.DllUnregisterServer();
		return hr;
}

// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{	
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


