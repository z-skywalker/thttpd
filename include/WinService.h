#pragma once

#include <windows.h>

class WinService
{
public:
    static WinService & GetInstance() { return m_Instance; }

    DWORD SetServiceMain(LPSERVICE_MAIN_FUNCTIONA fnServMain);

    DWORD RegCtrlHandler(LPCSTR lpszServiceName, LPHANDLER_FUNCTION_EX pHandler, LPVOID pContext);

    DWORD SetCurrentState(DWORD dwState, DWORD dwWaitHint = 0);

    DWORD IncreaseCheckPoint();

    BOOL IsRunAsService() { return m_hServiceStatus != 0; }

private:
    WinService();
    ~WinService();

private:
    static WinService       m_Instance;

    SERVICE_STATUS_HANDLE   m_hServiceStatus    = 0;
    SERVICE_STATUS          m_ServiceStatus     = {0};
};
