// CPdfViewDlg.cpp : implementation file
//

#include "pch.h"
#include "AdobeSDKPlugin.h"
#include "afxdialogex.h"
#include "CPdfViewDlg.h"


// CPdfViewDlg dialog

IMPLEMENT_DYNAMIC(CPdfViewDlg, CDialogEx)

CPdfViewDlg::CPdfViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PDFVIEW, pParent)
{

}

CPdfViewDlg::~CPdfViewDlg()
{
}

void CPdfViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPdfViewDlg, CDialogEx)
END_MESSAGE_MAP()


// CPdfViewDlg message handlers
