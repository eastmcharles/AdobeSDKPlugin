#pragma once
#include "afxdialogex.h"
#include "CDocumentItem.h"
#include "CPDF_VIEW.h"

// CPdfViewDlg dialog

class CPdfViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPdfViewDlg)
	CArray<CDocumentItem> m_arrDocumentItem;
public:
	CPdfViewDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPdfViewDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PDFVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cbCaseList;
	CListBox m_lbDocList;
	CString m_selectedCaseTitle;
	afx_msg void OnBnClickedButtonLoad();
	CPDF_VIEW m_pdfView;
	afx_msg void OnLbnDblclkListDoclist();
	void OpenPdfFile(int sel);
};
