//################################################################################################
//
// Mga Decorator Base
//	BoxDecorator.h
//
//################################################################################################

#ifndef __BOXDECORATOR_H_
#define __BOXDECORATOR_H_

#pragma warning( disable : 4786 )

#include "StdAfx.h"
#include "MgaDecoratorLib.h"
#include "mga.h"
#include "resource.h"

namespace Decorator
{
	class DecoratorBase;
};

//################################################################################################
//
// CLASS : CBoxDecorator
//
//################################################################################################

class ATL_NO_VTABLE CBoxDecorator :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMgaDecorator,
	public CComCoClass<CBoxDecorator, &CLSID_BoxDecorator>
{
	private :
		CComPtr<IMgaProject> 		m_spProject;
		CComPtr<IMgaMetaPart> 		m_spPart;
		CComPtr<IMgaFCO> 			m_spFCO;

		Decorator::DecoratorBase*	m_pDecorator;
		bool						m_bLocationSet;

	public:
		CBoxDecorator();
		~CBoxDecorator();

		DECLARE_REGISTRY_RESOURCEID( IDR_BOXDECORATOR )
		DECLARE_PROTECT_FINAL_CONSTRUCT()

		BEGIN_COM_MAP( CBoxDecorator )
			COM_INTERFACE_ENTRY( IMgaDecorator )
		END_COM_MAP()

	// =============== IBoxDecorator
	public:
		STDMETHOD( Initialize )			( /*[in]*/ IMgaProject *pProject, /*[in]*/ IMgaMetaPart *pPart, /*[in]*/ IMgaFCO *pFCO );
		STDMETHOD( Destroy )			();
		STDMETHOD( GetMnemonic )		( /*[out]*/ BSTR *bstrMnemonic );
		STDMETHOD( GetFeatures )		( /*[out]*/ feature_code *pFeatureCodes );
		STDMETHOD( SetParam )			( /*[in]*/ BSTR bstrName, /*[in]*/ VARIANT vValue );
		STDMETHOD( GetParam )			( /*[in]*/ BSTR bstrName, /*[out]*/ VARIANT* pvValue );
		STDMETHOD( SetActive )			( /*[in]*/ VARIANT_BOOL bIsActive );
		STDMETHOD( GetPreferredSize )	( /*[out]*/ long* plWidth, /*[out]*/ long* plHeight );
		STDMETHOD( SetLocation )		( /*[in]*/ long sx, /*[in]*/ long sy, /*[in]*/ long ex, /*[in]*/ long ey );
		STDMETHOD( GetLocation )		( /*[out]*/ long *sx, /*[out]*/ long *sy, /*[out]*/ long *ex, /*[out]*/ long *ey );
		STDMETHOD( GetLabelLocation )	( /*[out]*/ long *sx, /*[out]*/ long *sy, /*[out]*/ long *ex, /*[out]*/ long *ey );
		STDMETHOD( GetPortLocation )	( /*[in]*/ IMgaFCO *fco, /*[out]*/ long *sx, /*[out]*/ long *sy, /*[out]*/ long *ex, /*[out]*/ long *ey );
		STDMETHOD( GetPorts )			( /*[out, retval]*/ IMgaFCOs **portFCOs );
		STDMETHOD( Draw )				( /*[in]*/ HDC hdc );
		STDMETHOD( SaveState )			();
};

#endif //__BOXDECORATOR_H_
