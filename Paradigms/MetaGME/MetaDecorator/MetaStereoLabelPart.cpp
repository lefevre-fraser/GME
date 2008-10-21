//################################################################################################
//
// Meta Stereo label part class (decorator part)
//	MetaStereoLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "MetaStereoLabelPart.h"
#include "DecoratorStd.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : MetaStereoLabelPart
//
//################################################################################################

MetaStereoLabelPart::MetaStereoLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	DecoratorSDK::StereoLabelPart(pPart, eventSink)
{
}

MetaStereoLabelPart::~MetaStereoLabelPart()
{
}

// New functions
void MetaStereoLabelPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									   HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO);
	StereoLabelPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

bool MetaStereoLabelPart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool MetaStereoLabelPart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool MetaStereoLabelPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool MetaStereoLabelPart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

void MetaStereoLabelPart::ExecuteOperation(const CString& newString)
{
	// transaction operation begin
/*	// Mustn't execute this editing, you can't just change stereotype name in case of Meta Paradigm
	// TODO: supress editing
	m_strText = newString;
	CComBSTR bstr;
	CopyTo(m_strText, bstr);
	COMTHROW(m_spMetaFCO->put_Name(bstr));*/
	// transaction operation end
}

}; // namespace MetaDecor
