#include "WinService.h"

WinService WinService::m_Instance;

WinService::WinService()
{
    m_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
}

WinService::~WinService()
{
}

DWORD WinService::SetServiceMain(LPSERVICE_MAIN_FUNCTIONA fnServMain)
{
    SERVICE_TABLE_ENTRYA serviceTable[] = {
        { (LPSTR)"", fnServMain }, { nullptr, nullptr }
    };

    if (StartServiceCtrlDispatcherA(serviceTable)) return ERROR_SUCCESS;

    return GetLastError();
}

DWORD WinService::RegCtrlHandler(LPCSTR lpszServiceName, LPHANDLER_FUNCTION_EX pHandler, LPVOID pContext)
{
    m_hServiceStatus = RegisterServiceCtrlHandlerExA(lpszServiceName, pHandler, pContext);

    if (m_hServiceStatus) return ERROR_SUCCESS;

    return GetLastError();
}

DWORD WinService::SetCurrentState(DWORD dwState, DWORD dwWaitHint)
{
    m_ServiceStatus.dwCurrentState = dwState;
    m_ServiceStatus.dwWaitHint = dwWaitHint;
    m_ServiceStatus.dwCheckPoint = 0;

    if (dwState == SERVICE_START_PENDING)
        m_ServiceStatus.dwControlsAccepted = 0;
    else
        m_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;

    if (SetServiceStatus(m_hServiceStatus, &m_ServiceStatus)) return ERROR_SUCCESS;

    return GetLastError();
}

DWORD WinService::IncreaseCheckPoint()
{
    m_ServiceStatus.dwCheckPoint += 1;

    if (SetServiceStatus(m_hServiceStatus, &m_ServiceStatus)) return ERROR_SUCCESS;

    return GetLastError();
}
