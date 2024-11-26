
// AdobeSDKPluginDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "AdobeSDKPlugin.h"
#include "AdobeSDKPluginDlg.h"
#include "afxdialogex.h"

#include <afxinet.h> // For CInternetSession and CHttpFile
#include <afxwin.h>  // For CString
#include <iostream>  // For std::cout
#include <string>    // For std::string
#include "nlohmann/json.hpp" // Adjust the path as necessary
#include <winhttp.h>

using json = nlohmann::json; // Create an alias for convenience

#define PROFILE_SECTION L"PARAMS"
#define PROFILE_APIKEY_ENTRY L"APIKEY"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdobeSDKPluginDlg dialog



CAdobeSDKPluginDlg::CAdobeSDKPluginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADOBESDKPLUGIN_DIALOG, pParent)
	, m_apikey(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdobeSDKPluginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_API_KEY, m_apikey);
	DDX_Control(pDX, IDC_COMBO_CASELIST, m_caseComboBox);
}

BEGIN_MESSAGE_MAP(CAdobeSDKPluginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CAdobeSDKPluginDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CAdobeSDKPluginDlg message handlers

BOOL CAdobeSDKPluginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_apikey = theApp.GetProfileStringW(PROFILE_SECTION, PROFILE_APIKEY_ENTRY);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAdobeSDKPluginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAdobeSDKPluginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAdobeSDKPluginDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_apikey.IsEmpty()) MessageBox(L"Please input api key", NULL, MB_OK | MB_ICONERROR);
	else {
		m_caseComboBox.ResetContent(); m_caseIdList.RemoveAll(); m_caseTitleList.RemoveAll();
		CInternetSession session(_T("AdobeSDKPluginSession"));
		CHttpConnection* pServer = session.GetHttpConnection(_T("api.smartcite.povio.dev"));
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
			_T("/api/cases"));
		CString header = L"X-Api-Key: " + m_apikey;
		theApp.WriteProfileStringW(PROFILE_SECTION, PROFILE_APIKEY_ENTRY, m_apikey);
		pFile->AddRequestHeaders(header);
		pFile->SendRequest();
		// Send the request
		DWORD bytesRead = 0;
		char buffer[4096];
		CStringA responseData;

		// Read the response
		while ((bytesRead = pFile->Read(buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytesRead] = '\0'; // Null-terminate the buffer
			responseData.Append(buffer, bytesRead);
		}

		std::string jsonResponse = responseData;

		try {
			auto json = json::parse(jsonResponse);
			if (json.contains("message")) {
				MessageBox(CString(json["message"].get<std::string>().c_str()), NULL, MB_OK | MB_ICONERROR);
			}
			else {
				// Analyze the response
				int totalItems = json["totalItems"];
				MessageBox(CString("Total Cases: ") + std::to_string(totalItems).c_str());

				for (const auto& item : json["items"])
				{
					CString id(item["id"].get<std::string>().c_str());
					CString title(item["title"].get<std::string>().c_str());
					m_caseIdList.AddTail(id);
					m_caseTitleList.AddTail(title);
					m_caseComboBox.AddString(title);
				}
				m_caseComboBox.SetCurSel(0);
			}
		}
		catch (const json::parse_error& e) {
			AfxMessageBox(CString("JSON Parse Error: ") + CString(e.what()));
		}
		catch (const json::exception& e) {
			AfxMessageBox(CString("JSON Exception: ") + CString(e.what()));
		}

		if (pFile) {
			pFile->Close();
			delete pFile;
		}

		if (pServer) {
			pServer->Close();
			delete pServer;
		}
	}
}
