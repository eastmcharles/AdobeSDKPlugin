
// AdobeSDKPlugin.h : main header file for the PROJECT_NAME application
//

#pragma once
#include <string>    // For std::string
#include <iostream>
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

// Overrides
public:
	virtual BOOL InitInstance();
	
// Implementation

	DECLARE_MESSAGE_MAP()
};
std::string GetResponseData(CString hostDomain, CString urlPath, CString apikey, CFile* pTargetFile = NULL);
extern CAdobeSDKPluginApp theApp;
