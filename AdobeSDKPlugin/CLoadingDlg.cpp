// CLoadingDlg.cpp : implementation file
//

#include "pch.h"
#include "AdobeSDKPlugin.h"
#include "afxdialogex.h"
#include "CLoadingDlg.h"



// CLoadingDlg dialog

IMPLEMENT_DYNAMIC(CLoadingDlg, CDialogEx)

CLoadingDlg::CLoadingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOADING, pParent)
{

}

CLoadingDlg::~CLoadingDlg()
{
}

void CLoadingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressCtrl);
}

int CLoadingDlg::DownloadFiles(CWnd* pWndParent, CString caseTitle, CString caseId, CArray<CDocumentItem>& arrDocumentItem) {
	CLoadingDlg dlg;
	dlg.Create(IDD_DIALOG_LOADING, pWndParent);
	dlg.m_caseId = caseId;
	dlg.m_pArrDocumentItem = &arrDocumentItem;
	dlg.m_caseTitle = caseTitle;
	dlg.SetWindowTextW(L"Loading " + caseTitle + L"...");
	dlg.ShowWindow(SW_SHOW);
	dlg.pThread = AfxBeginThread(DownloadThread, &dlg);
	int nRes = dlg.RunModalLoop();
	return nRes;
}

void CLoadingDlg::DownloadFiles(CString caseId, CArray<CDocumentItem>& arrDocumentItem) {

}

#include <afx.h>  // Include for CString
#include <string>

void SplitUrl(const CString& url, CString& domain, CString& path)
{
	// Find the position of "://", which separates the protocol from the domain
	int pos = url.Find(L"://");
	if (pos != -1)
	{
		// Extract the domain, which is between "://" and the first "/"
		CString remainingUrl = url.Mid(pos + 3);  // Skip "://"

		// Find the first '/' after the protocol
		int pathStartPos = remainingUrl.Find(L"/");
		if (pathStartPos != -1)
		{
			// Extract the domain from the start to the first '/'
			domain = remainingUrl.Left(pathStartPos);

			// Extract the path starting from the first '/'
			path = remainingUrl.Mid(pathStartPos);
		}
		else
		{
			// If no '/' is found, the entire remaining string is the domain, and there's no path
			domain = remainingUrl;
			path.Empty();
		}
	}
	else
	{
		// If no "://" is found, treat the entire string as the domain and path (assuming malformed URL)
		domain.Empty();
		path = url;
	}
}


UINT CLoadingDlg::DownloadThread(LPVOID param) {
	CLoadingDlg* pDlg = (CLoadingDlg*)param;

	std::string jsonResponse = GetResponseData(API_HOST_DOMAIN, CString(CASES_LIST_URL_PATH) + L"/" + pDlg->m_caseId + L"/documents", theApp.m_apikey);

	try {
		pDlg->m_pArrDocumentItem->RemoveAll();
		auto json = json::parse(jsonResponse);
		if (json.contains("message")) {
			pDlg->MessageBox(CString(json["message"].get<std::string>().c_str()), NULL, MB_OK | MB_ICONERROR);
			pDlg->EndDialog(IDCANCEL);
		}
		else {
			// Analyze the response
			int totalItems = json["totalItems"];
			TRACE(L"Total Documents: %s\n", CString(std::to_string(totalItems).c_str()));
			int index = 0;
			CString caseDirPath = GetCaseDirectoryPath(pDlg->m_caseTitle);
			for (const auto& item : json["items"])
			{
				CString mediaUrl(item["mediaUrl"].get<std::string>().c_str());
				CString title(item["title"].get<std::string>().c_str());
				CString filePath = caseDirPath + L"\\" + title;
				CString domain, path;
				SplitUrl(mediaUrl, domain, path);
				CFile file(filePath, CFile::modeWrite | CFile::modeCreate);
				GetResponseData(domain, path, NULL, &file);
				file.Close();
				TRACE(L"Document(%d): %s %s %s %s\n", index, title, filePath, domain, path);
				pDlg->m_pArrDocumentItem->Add(CDocumentItem(title, mediaUrl, filePath));
				index++;
				int progressValue = index * 100 / totalItems;
				pDlg->m_progressCtrl.SetPos(progressValue);
				pDlg->SetDlgItemInt(IDC_STATIC_PROGRESS, progressValue);
			}
			pDlg->EndDialog(IDOK);
		}
	}
	catch (const json::parse_error& e) {
		AfxMessageBox(CString("JSON Parse Error: ") + CString(e.what()));
	}
	catch (const json::exception& e) {
		AfxMessageBox(CString("JSON Exception: ") + CString(e.what()));
	}

	return 0;
}

BEGIN_MESSAGE_MAP(CLoadingDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CLoadingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CLoadingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoadingDlg message handlers


BOOL CLoadingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_progressCtrl.SetRange(0, 100);
	m_progressCtrl.SetPos(0);
	SetDlgItemInt(IDC_STATIC_STATUS, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoadingDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	pThread->SuspendThread();
	CDialogEx::OnCancel();
}


void CLoadingDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
