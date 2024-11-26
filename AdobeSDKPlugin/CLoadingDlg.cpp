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
}


BEGIN_MESSAGE_MAP(CLoadingDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoadingDlg message handlers
