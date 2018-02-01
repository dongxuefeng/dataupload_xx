#include "Windows.h" 
#include <stdio.h>
#include "c_windows_service.h"


SERVICE_STATUS m_ServiceStatus;
SERVICE_STATUS_HANDLE m_ServiceStatusHandle;
BOOL bRunning = true;
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
void WINAPI ServiceCtrlHandler(DWORD Opcode);
BOOL InstallService();
BOOL DeleteService();
#define _service_name "ehl.hikdata.upload"

int main(int argc, char * argv[])
{
	if (argc>1)
	{
		if (strcmp(argv[1], "-r") == 0)
		{
			DoTask();
		}
		if (strcmp(argv[1], "-i") == 0)
		{
			if (InstallService())
				printf("\n Service Installed Sucessfully\n");
			else
				printf("\n Service has been installed\n");
		}
		else if (strcmp(argv[1], "-d") == 0)
		{
			if (DeleteService())
				printf("\n Service UnInstalled Sucessfully\n");
			else
				printf("\nInstalled Easin Central Service Not Found\n");
		}
		else
		{
			printf("\nUnknown Switch Usage\nFor Install use Servicetest -i\nFor UnInstall use Servicetest -d\n");
		}
	}
	else
	{
		SERVICE_TABLE_ENTRY DispatchTable[] = { { _service_name, ServiceMain }, { NULL, NULL } };
		StartServiceCtrlDispatcher(DispatchTable);
	}
	return 0;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)

{
	//     DWORD status;  

	//     DWORD specificError;  

	m_ServiceStatus.dwServiceType = SERVICE_WIN32;
	m_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	m_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	m_ServiceStatus.dwWin32ExitCode = 0;
	m_ServiceStatus.dwServiceSpecificExitCode = 0;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;
	m_ServiceStatusHandle = RegisterServiceCtrlHandler(_service_name, ServiceCtrlHandler);

	if (m_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)
	{
		return;
	}

	m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;

	if (!SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus))
	{
	}

	bRunning = true;
	while (bRunning)
	{
		Sleep(3000);
		//Place Your Code for processing here....   
		DoTask();
	}
	return;
}

void WINAPI ServiceCtrlHandler(DWORD Opcode)
{

	switch (Opcode)
	{
	case SERVICE_CONTROL_PAUSE:
		m_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP:
		m_ServiceStatus.dwWin32ExitCode = 0;
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		m_ServiceStatus.dwCheckPoint = 0;
		m_ServiceStatus.dwWaitHint = 0;
		SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
		bRunning = false;
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	}
	return;

}

BOOL InstallService()
{

	char strDir[1024];
	SC_HANDLE schSCManager, schService;
	GetCurrentDirectory(1024, strDir);
	lstrcat(strDir, "\\ehl.ftpdata.proc.exe");

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL)
		return false;

	LPCTSTR lpszBinaryPathName = strDir;
	schService = CreateService((struct SC_HANDLE__ *)schSCManager, _service_name, _service_name,// service name to display  
		SERVICE_ALL_ACCESS,          // desired access  
		SERVICE_WIN32_OWN_PROCESS, // service type  
		SERVICE_AUTO_START,        // start type  
		SERVICE_ERROR_NORMAL,        // error control type  
		lpszBinaryPathName,          // service's binary  
		NULL,                        // no load ordering group  
		NULL,                        // no tag identifier  
		NULL,                        // no dependencies  
		NULL,                        // LocalSystem account  
		NULL);                       // no password  

	if (schService == NULL)
		return false;
	SERVICE_DESCRIPTION   sdBuf;
	sdBuf.lpDescription = "GT即时同步软件后台服务";
	ChangeServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, &sdBuf);
	CloseServiceHandle((struct SC_HANDLE__ *)schService);
	return true;
}

BOOL DeleteService()
{

	HANDLE schSCManager;
	SC_HANDLE hService;
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL)
		return false;

	hService = OpenService((struct SC_HANDLE__ *)schSCManager, _service_name, SERVICE_ALL_ACCESS);
	if (hService == NULL)
		return false;

	if (DeleteService(hService) == 0)
		return false;

	if (CloseServiceHandle(hService) == 0)
		return false;
	else
		return true;
};