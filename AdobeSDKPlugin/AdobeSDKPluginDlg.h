
// AdobeSDKPluginDlg.h : header file
//

#pragma once


// CAdobeSDKPluginDlg dialog
class CAdobeSDKPluginDlg : public CDialogEx
{
// Construction
public:
	CAdobeSDKPluginDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADOBESDKPLUGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();
	CString m_apikey;
	CComboBox m_caseComboBox;
	CStringList m_caseIdList;
	CStringList m_caseTitleList;
};
