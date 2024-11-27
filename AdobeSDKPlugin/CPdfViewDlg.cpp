// CPdfViewDlg.cpp : implementation file
//

#include "pch.h"
#include "AdobeSDKPlugin.h"
#include "afxdialogex.h"
#include "CPdfViewDlg.h"
#include "AdobeSDKPluginDlg.h"
#include "CLoadingDlg.h"

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
	DDX_Control(pDX, IDC_COMBO_CASELIST, m_cbCaseList);
	DDX_Control(pDX, IDC_LIST_DOCLIST, m_lbDocList);
	DDX_Control(pDX, IDC_PDF_VIEW, m_pdfView);
}


BEGIN_MESSAGE_MAP(CPdfViewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CPdfViewDlg::OnBnClickedButtonLoad)
	ON_LBN_DBLCLK(IDC_LIST_DOCLIST, &CPdfViewDlg::OnLbnDblclkListDoclist)
END_MESSAGE_MAP()


// CPdfViewDlg message handlers


BOOL CPdfViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	DeleteCasesDirectory();
	CAdobeSDKPluginDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse != IDOK) {
		CDialog::OnCancel();
	}
	else {
		theApp.m_apikey = dlg.m_apikey;
		for (int i = 0;i < theApp.m_caseTitleList.GetCount();i++) {
			m_cbCaseList.AddString(theApp.m_caseTitleList[i]);
		}
		m_cbCaseList.SetCurSel(0);
	}

	m_pdfView.setShowToolbar(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CPdfViewDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
	if (m_cbCaseList.GetCurSel() == -1) {
		MessageBox(L"Please select case!", NULL, MB_OK | MB_ICONERROR);
	}
	else {
		int sel = m_cbCaseList.GetCurSel();
		CString id = theApp.m_caseIdList[sel];
		CString title = theApp.m_caseTitleList[sel];

		m_lbDocList.ResetContent();
		if (CLoadingDlg::DownloadFiles(this, title, id, m_arrDocumentItem) == IDOK) {
			for (int i = 0;i < m_arrDocumentItem.GetCount();i++) {
				m_lbDocList.AddString(m_arrDocumentItem[i].m_title);
			}
			m_selectedCaseTitle = title;
			m_lbDocList.SetCurSel(0);
			OpenPdfFile(0);
		}
	}
}


void CPdfViewDlg::OnLbnDblclkListDoclist()
{
	// TODO: Add your control notification handler code here
	int sel = m_lbDocList.GetCurSel();
	if (sel >= 0 && sel < m_arrDocumentItem.GetCount()) {
		OpenPdfFile(sel);
	}
	else {
		MessageBox(L"Please double click the title", NULL, MB_ICONERROR);
	}
}

void CPdfViewDlg::OpenPdfFile(int sel) {
	SetWindowText(m_selectedCaseTitle + L" - " + m_arrDocumentItem[sel].m_title);
	m_pdfView.LoadFile(m_arrDocumentItem[sel].m_filePath);
}