
#include "stdafx.h"

#include "RecentConnStrList.h"

/////////////////////////////////////////////////////////////////////////////
// CRecentConnStrList

CRecentConnStrList::CRecentConnStrList(UINT nStart, LPCTSTR lpszSection,
	LPCTSTR lpszEntryFormat, int nSize, int nMaxDispLen)
{
	ASSERT(nSize != 0);
	m_arrNames = new CString[nSize];
	m_nSize = nSize;

	m_nStart = nStart;
	m_strSectionName = lpszSection;
	m_strEntryFormat = lpszEntryFormat;
	m_nMaxDisplayLength = nMaxDispLen;
}

CRecentConnStrList::~CRecentConnStrList()
{
	delete[] m_arrNames;
}

// Operations
void CRecentConnStrList::Add(LPCTSTR lpszConnName)
{
	ASSERT(m_arrNames != NULL);
	ASSERT(lpszConnName != NULL);
	ASSERT(AfxIsValidString(lpszConnName));

	// update the MRU list, if an existing MRU string matches conn name
	for (int iMRU = 0; iMRU < m_nSize-1; iMRU++)
	{
		if (lstrcmp(m_arrNames[iMRU], lpszConnName) == 0)
			break;      // iMRU will point to matching entry
	}
	// move MRU strings before this one down
	for (; iMRU > 0; iMRU--)
	{
		ASSERT(iMRU > 0);
		ASSERT(iMRU < m_nSize);
		m_arrNames[iMRU] = m_arrNames[iMRU-1];
	}
	// place this one at the beginning
	m_arrNames[0] = lpszConnName;
}

void CRecentConnStrList::Remove(int nIndex)
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < m_nSize);

	m_arrNames[nIndex].Empty();
	for (int iMRU = nIndex; iMRU < m_nSize-1; iMRU++)
		m_arrNames[iMRU] = m_arrNames[iMRU+1];

	ASSERT(iMRU < m_nSize);
	m_arrNames[iMRU].Empty();
}

BOOL CRecentConnStrList::GetDisplayName(CString& strName, int nIndex) const
{
	ASSERT(m_arrNames != NULL);
	ASSERT(nIndex < m_nSize);
	if (m_arrNames[nIndex].IsEmpty())
		return FALSE;

	strName = m_arrNames[nIndex];
	return TRUE;
}

void CRecentConnStrList::UpdateMenu(CCmdUI* pCmdUI,bool enable)
{
	ASSERT(m_arrNames != NULL);

	CMenu* pMenu = pCmdUI->m_pMenu;
	if (m_strOriginal.IsEmpty() && pMenu != NULL)
		pMenu->GetMenuString(pCmdUI->m_nID, m_strOriginal, MF_BYCOMMAND);

	if (m_arrNames[0].IsEmpty())
	{
		// no MRU files
		if (!m_strOriginal.IsEmpty())
			pCmdUI->SetText(m_strOriginal);
		pCmdUI->Enable(FALSE);
		return;
	}

	if (pCmdUI->m_pMenu == NULL)
		return;

	for (int iMRU = 0; iMRU < m_nSize; iMRU++)
		pCmdUI->m_pMenu->DeleteMenu(pCmdUI->m_nID + iMRU, MF_BYCOMMAND);

	CString strName;
	CString strTemp;
	for (iMRU = 0; iMRU < m_nSize; iMRU++)
	{
		if (!GetDisplayName(strName, iMRU))
			break;

		// double up any '&' characters so they are not underlined
		LPCTSTR lpszSrc = strName;
		LPTSTR lpszDest = strTemp.GetBuffer(strName.GetLength()*2);
		while (*lpszSrc != 0)
		{
			if (*lpszSrc == '&')
				*lpszDest++ = '&';
			if (_istlead(*lpszSrc))
				*lpszDest++ = *lpszSrc++;
			*lpszDest++ = *lpszSrc++;
		}
		*lpszDest = 0;
		strTemp.ReleaseBuffer();

		// insert mnemonic + the file name
		TCHAR buf[10];
		wsprintf(buf, _T("&%d "), (iMRU+1+m_nStart) % 10);
		pCmdUI->m_pMenu->InsertMenu(pCmdUI->m_nIndex,
			MF_STRING | MF_BYPOSITION, pCmdUI->m_nID,
			CString(buf) + strTemp);
		if( !enable ) pCmdUI->Enable(FALSE);
		pCmdUI->m_nIndex++;
		pCmdUI->m_nID++;
	}

	// update end menu count
	pCmdUI->m_nIndex--; // point to last menu added
	pCmdUI->m_nIndexMax = pCmdUI->m_pMenu->GetMenuItemCount();

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled
}

void CRecentConnStrList::WriteList()
{
	ASSERT(m_arrNames != NULL);
	ASSERT(!m_strSectionName.IsEmpty());
	ASSERT(!m_strEntryFormat.IsEmpty());
	LPTSTR pszEntry = new TCHAR[m_strEntryFormat.GetLength()+5];
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString(m_strSectionName, NULL, NULL);
	for (int iMRU = 0; iMRU < m_nSize; iMRU++)
	{
		wsprintf(pszEntry, m_strEntryFormat, iMRU + 1);
		if (!m_arrNames[iMRU].IsEmpty())
		{
			pApp->WriteProfileString(m_strSectionName, pszEntry,
				m_arrNames[iMRU]);
		}
	}
	delete[] pszEntry;
}

void CRecentConnStrList::ReadList()
{
	ASSERT(m_arrNames != NULL);
	ASSERT(!m_strSectionName.IsEmpty());
	ASSERT(!m_strEntryFormat.IsEmpty());
	LPTSTR pszEntry = new TCHAR[m_strEntryFormat.GetLength()+5];
	CWinApp* pApp = AfxGetApp();
	for (int iMRU = 0; iMRU < m_nSize; iMRU++)
	{
		wsprintf(pszEntry, m_strEntryFormat, iMRU + 1);
		m_arrNames[iMRU] = pApp->GetProfileString(
			m_strSectionName, pszEntry, NULL);// '&afxChNil' previously
	}
	delete[] pszEntry;
}

