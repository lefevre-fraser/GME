// Preference.h: interface for the CPreference class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREFERENCE_H__5A93281C_8818_4B0A_A6BC_DE727350321B__INCLUDED_)
#define AFX_PREFERENCE_H__5A93281C_8818_4B0A_A6BC_DE727350321B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemData.h"


#define PREF_CONNECTION		0x01
#define PREF_ATOM			0x02
#define PREF_MODEL			0x04
#define PREF_PROXY			0x08
#define PREF_SET			0x10


typedef char*(*TableRowType)[5];

class CPreference
{
	static char* m_szConnectionPreferenceTable[][5];
	static char* m_szAtomPreferenceTable[][5];
	static char* m_szModelPreferenceTable[][5];
	static char* m_szProxyPreferenceTable[][5];
	static char* m_szSetPreferenceTable[][5];

public:
	void WriteItemToMga(CListItem ListItem,const CMgaFCOPtrList& MgaFCOPtrList, bool bIsForKind);
//	CString m_strName;
	void CreateListItem(CArray<CListItem,CListItem&>&  ListItems, 
						TableRowType, const CString& strValue, 
						bool bSameValueForAll, bool bIsDefault,
						bool bIsMultiple,const CComPtr<IMgaFCO>&ccpMgaFCO, POSITION nKey);
	void GetDefaultValue(CString strCurrPath,objtype_enum oeType, CString& strDefValue);
	int FindRegPathInSetTable(const CString& strPath);
	int FindRegPathInProxyTable(const CString& strPath);
	int FindRegPathInModelTable(const CString& strPath);
	int FindRegPathInAtomTable(const CString& strPath);
	int FindRegPathInConnectionTable(const CString& strPath);
	void SetupPreferences(BYTE cFlags);
	static char* m_szLineStyleList[];
	static char* m_szLineTypeList[];
	static char* m_szBooleanList[];
	
	CArray<CListItem,CListItem&> m_ListItemArray;
	void CreateList( const CMgaFCOPtrList& MgaFCOPtrList);
	void Write2Mga(const CString& strValue,const CComPtr<IMgaFCO>& ccpMgaFCO,const CListItem& ListItem, const CString& strRegPath, bool bIsForKind);
	
	CStringList m_strRegPathList;
	CPreference();
	virtual ~CPreference();

private:
	// Helper array length variables
	int nConnTableLength;
	int nAtomTableLength; 
	int nModelTableLength;
	int nProxyTableLength;
	int nSetTableLength;

	// Helper for System Backround Color
	char m_szSysBckGrnd[9];

	// Helper variable for placing auto router switch settings in case of model preferences
	bool isAutRouterPrefsCategoryAdded;

	int GetRegistryValue(CComPtr<IMgaFCO>&ccpMgaFCO,CString strPath, CString &strRegValue);
	TableRowType GetTableRow(CString strCurrPath, objtype_enum oeType);
	
	void SetCategories( const CString& strPath, bool bIsAfter);
	void ListValue2MgaValue(const CListItem& ListItem, CString& strValue);
};




#endif // !defined(AFX_PREFERENCE_H__5A93281C_8818_4B0A_A6BC_DE727350321B__INCLUDED_)

