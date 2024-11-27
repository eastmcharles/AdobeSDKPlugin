#pragma once
class CDocumentItem
{
public:
	CString m_title, m_mediaUrl, m_filePath;
	CDocumentItem(CString title = L"", CString mediaUrl = L"", CString filePath = L"") :m_title(title), m_mediaUrl(mediaUrl), m_filePath(filePath) {}
};

