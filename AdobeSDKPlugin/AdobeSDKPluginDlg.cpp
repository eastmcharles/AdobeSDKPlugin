
// AdobeSDKPluginDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "AdobeSDKPlugin.h"
#include "AdobeSDKPluginDlg.h"
#include "afxdialogex.h"

#include "nlohmann/json.hpp" // Adjust the path as necessary
using json = nlohmann::json; // Create an alias for convenience

#define PROFILE_SECTION L"PARAMS"
#define PROFILE_APIKEY_ENTRY L"APIKEY"
#define API_HOST_DOMAIN _T("api.smartcite.povio.dev")
#define CASES_LIST_URL_PATH L"/api/cases"

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
}

BEGIN_MESSAGE_MAP(CAdobeSDKPluginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CAdobeSDKPluginDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CAdobeSDKPluginDlg::OnBnClickedButtonOpen)
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
	CFile file;
	file.Open(L"tmp.pdf", CFile::modeWrite | CFile::modeCreate);

	auto res = GetResponseData(L"sc-dev-file-storage.s3.us-east-1.amazonaws.com", L"/uploads/DOCUMENT/29f79cd8-0d00-4def-ad54-86121c47016e?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAU6GD2TB7GVT7ZKY3%2F20241126%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20241126T215141Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI3%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJHMEUCIQDCzBSl6m97a1uWnATYQNAJU5%2BEN%2FqeUBEszFJccwbTJgIgenmA33WhmyHyWH4zQtl7tBNg8mB2J0FF1XdHdABRMNoq4wMINhAAGgwzMzk3MTMxMDM5OTgiDBk2vive%2FaBo0w327SrAA3L7cOu5RKmTEcLT7KXG7BlaQv9%2BLGbQ5V%2B0hxY8%2FudhKgB0CenR9uBbBJ4oQ6AtstvAMfwZo5RZvVip4T3g7H9%2FfnM5vDocXfjOX9dMTyuTDHbrXthQEaFrAuO3WFtX2R0MFpWzyYlBOwY1Pf4YAQDL6RtwIFr5TodT0ZzmmRHVugXaMeHvLc3Oekq1u3l5BsmchJtUw6NRQlcoY05Qsex1IojXGBQsvXGRIqXujdeitDNlyMH8oibnhBoZoWOnG1w5HKarC7Dga01ODB%2BzIh%2BP5U6%2BGYwqrl3Tv6BSeBlVA0cmwJFVkmaGhe39X0vNX6hXKNPTtUYfnfnhBePRLKoqrPaZZXOvGfMNe2sKfKwODMD9d2xf0Ydq0GUBfUTBzzb%2Fjx1BdR4iBpZ%2B8gd63ZlZjLVj5aG9UL4ZjJZklrKHPXnxZJm0T%2FiBpLAa50hyNid1yGII%2F8dQLvXkEtrTHriXpTnCgIiUZRH9TerV8zgQAmBSWje%2B6bYM7WdYDQESMSuwpfulTAMepnxMyvwJKyl6WH%2FKsm0DpOFt5suIH%2FHGOy%2FWz0OYyDjrgRS5ka2mgft5yZ6%2FTY%2FTFvZFA5FCYNIwp%2BWYugY6pQE82uiWbiwPUnvFQt6JP65C3HRNLSkR6PCS1voLg8IEQG8HXWf8GKtMet9vluj2Sc4vI4W92V%2FJNKcogOtDzFgQC%2FyXWIaVuPYkeHzr3ExRVGT8GnSXHsttJDv4%2B8ec%2BEjaAx2x5XiartveO123DxvE%2BaGo0cZ1AcyjiWu5A2%2BViVwjPyYEKl676cTt764d3L3AxEudOaVcejZmAl5avi6dtwwpRfQ%3D&X-Amz-Signature=2bd7967e222fc8ba75d788ee11eae8717117173894762bc5847943091d53f459&X-Amz-SignedHeaders=host&x-id=GetObject", L"", &file);
	
	file.Close();

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

		theApp.WriteProfileStringW(PROFILE_SECTION, PROFILE_APIKEY_ENTRY, m_apikey);
		
		BeginWaitCursor();
		std::string jsonResponse = GetResponseData(API_HOST_DOMAIN, CASES_LIST_URL_PATH, m_apikey);
		EndWaitCursor();

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
					m_caseIdList.Add(id);
					m_caseTitleList.Add(title);
				}
			}
		}
		catch (const json::parse_error& e) {
			AfxMessageBox(CString("JSON Parse Error: ") + CString(e.what()));
		}
		catch (const json::exception& e) {
			AfxMessageBox(CString("JSON Exception: ") + CString(e.what()));
		}
	}
}


void CAdobeSDKPluginDlg::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//if (m_caseComboBox.GetCurSel() == -1) {
	//	MessageBox(L"Please select case!", NULL, MB_OK | MB_ICONERROR);
	//}
	//else {
	//	int sel = m_caseComboBox.GetCurSel();
	//	CString id = m_caseIdList[sel];
	//	CString title = m_caseTitleList[sel];

	//	BeginWaitCursor();
	//	std::string jsonResponse = GetResponseData(API_HOST_DOMAIN, CString(CASES_LIST_URL_PATH) + L"/" + id + L"/documents", m_apikey);
	//	EndWaitCursor();

	//	try {
	//		auto json = json::parse(jsonResponse);
	//		if (json.contains("message")) {
	//			MessageBox(CString(json["message"].get<std::string>().c_str()), NULL, MB_OK | MB_ICONERROR);
	//		}
	//		else {
	//			// Analyze the response
	//			int totalItems = json["totalItems"];
	//			MessageBox(CString("Total Documents: ") + std::to_string(totalItems).c_str());

	//			for (const auto& item : json["items"])
	//			{
	//				CString mediaUrl(item["mediaUrl"].get<std::string>().c_str());
	//				CString title(item["title"].get<std::string>().c_str());
	//				MessageBox(mediaUrl, title);
	//			}
	//			m_caseComboBox.SetCurSel(0);
	//		}
	//	}
	//	catch (const json::parse_error& e) {
	//		AfxMessageBox(CString("JSON Parse Error: ") + CString(e.what()));
	//	}
	//	catch (const json::exception& e) {
	//		AfxMessageBox(CString("JSON Exception: ") + CString(e.what()));
	//	}
	//}
}

