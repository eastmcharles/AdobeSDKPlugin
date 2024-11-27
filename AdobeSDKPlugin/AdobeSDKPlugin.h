
// AdobeSDKPlugin.h : main header file for the PROJECT_NAME application
//

#pragma once
#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAdobeSDKPluginApp:
// See AdobeSDKPlugin.cpp for the implementation of this class
//

class CAdobeSDKPluginApp : public CWinApp
{
public:
	CAdobeSDKPluginApp();
	CStringArray m_caseIdList;
	CStringArray m_caseTitleList;
	CString m_apikey;
// Overrides
public:
	virtual BOOL InitInstance();
	
// Implementation

	DECLARE_MESSAGE_MAP()
};
std::string GetResponseData(CString hostDomain, CString urlPath, CString apikey, CFile* pTargetFile = NULL);
CString GetCasesDirectoryPath();
CString GetCaseDirectoryPath(const CString& caseName);
CString GenerateRandomSuffix();
bool DeleteCasesDirectory();

extern CAdobeSDKPluginApp theApp;
