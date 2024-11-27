#pragma once
#include "afxdialogex.h"
#include "CDocumentItem.h"

// CLoadingDlg dialog

class CLoadingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CLoadingDlg();
	static int DownloadFiles(CWnd *pWndParent, CString caseTitle, CString caseId, CArray<CDocumentItem>& arrDocumentItem);
	static UINT DownloadThread(LPVOID param);
	void DownloadFiles(CString caseId, CArray<CDocumentItem>& arrDocumentItem);
	CString m_caseId, m_caseTitle;
	CArray<CDocumentItem>* m_pArrDocumentItem;
	CWinThread* pThread;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOADING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_progressCtrl;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
