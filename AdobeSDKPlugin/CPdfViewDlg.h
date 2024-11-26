#pragma once
#include "afxdialogex.h"


// CPdfViewDlg dialog

class CPdfViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPdfViewDlg)

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
};
