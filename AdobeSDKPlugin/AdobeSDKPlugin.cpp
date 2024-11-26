
// AdobeSDKPlugin.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "AdobeSDKPlugin.h"
#include "AdobeSDKPluginDlg.h"

#include <afxinet.h> // For CInternetSession and CHttpFile
#include <afxwin.h>  // For CString
#include <winhttp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdobeSDKPluginApp

BEGIN_MESSAGE_MAP(CAdobeSDKPluginApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAdobeSDKPluginApp construction

CAdobeSDKPluginApp::CAdobeSDKPluginApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAdobeSDKPluginApp object

CAdobeSDKPluginApp theApp;


// CAdobeSDKPluginApp initialization

BOOL CAdobeSDKPluginApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager* pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("AdobeSDKPluginAPp"));

	CAdobeSDKPluginDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

std::string GetResponseData(CString hostDomain, CString urlPath, CString apikey, CFile* pTargetFile) {
	CInternetSession session(_T("AdobeSDKPluginSession"));
	CHttpConnection* pServer = session.GetHttpConnection(hostDomain);
	CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, urlPath);
	CString header = L"X-Api-Key: " + apikey;
	pFile->AddRequestHeaders(header);
	pFile->SendRequest();
	DWORD bytesRead = 0;
	char buffer[4096];
	CStringA responseData;

	// Read the response
	while ((bytesRead = pFile->Read(buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytesRead] = '\0'; // Null-terminate the buffer
		responseData.Append(buffer, bytesRead);
		pTargetFile->Write(buffer, bytesRead);
	}

	std::string jsonResponse = responseData;

	if (pFile) {
		pFile->Close();
		delete pFile;
	}

	if (pServer) {
		pServer->Close();
		delete pServer;
	}

	return jsonResponse;
}