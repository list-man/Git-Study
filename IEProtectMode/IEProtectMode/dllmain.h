// dllmain.h : Declaration of module class.

class CIEProtectModeModule : public ATL::CAtlDllModuleT< CIEProtectModeModule >
{
public :
	DECLARE_LIBID(LIBID_IEProtectModeLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_IEPROTECTMODE, "{0D21FDB0-3ABF-45B0-B901-75684D5051D2}")
};

extern class CIEProtectModeModule _AtlModule;
