//################################################################################################
//
// Mga Decorator Base
//	BoxDecorator.cpp
//
//################################################################################################

#include "BoxDecorator.h"
#include "DecoratorUtil.h"
#include "StereotypeDecorators.h"

int						CBoxDecorator::m_nOfInits = 0;
GdiplusStartupInput		CBoxDecorator::m_gdiplusStartupInput; // needed for GDI+ initialization
ULONG_PTR				CBoxDecorator::m_gdiplusToken;

//################################################################################################
//
// CLASS : CBoxDecorator
//
//################################################################################################

#define VERIFY_INITIALIZATION					\
	if ( ! m_pDecorator )							\
		return E_DECORATOR_UNINITIALIZED;

#define VERIFY_LOCATION						\
	if ( ! m_bLocationSet ) 						\
		return E_DECORATOR_LOCISNOTSET;

CBoxDecorator::CBoxDecorator()
	: m_spProject( NULL ), m_spPart( NULL ), m_spFCO( NULL ), m_pDecorator( NULL ), m_bLocationSet( false )
{
	if( m_nOfInits++ == 0)
	{
		VERIFY(GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL)==Ok);
	}
}

CBoxDecorator::~CBoxDecorator()
{
	if( --m_nOfInits == 0)
	{
		GdiplusShutdown(m_gdiplusToken);
	}
}

STDMETHODIMP CBoxDecorator::Initialize( IMgaProject *pProject, IMgaMetaPart *pPart, IMgaFCO *pFCO )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	Decorator::getFacilities().loadPathes( pProject, true );

	m_spProject = pProject;
	m_spPart = pPart;
	m_spFCO = pFCO;

	if ( m_spProject && m_spPart ) {
		objtype_enum eType;
		if ( m_spFCO )
			COMTHROW( m_spFCO->get_ObjType( &eType ) );
		else {
			CComPtr<IMgaMetaRole> spRole;
			COMTHROW( m_spPart->get_Role( &spRole ) );

			CComPtr<IMgaMetaFCO> spMetaFCO;
			COMTHROW( spRole->get_Kind( &spMetaFCO ) );

			COMTHROW( spMetaFCO->get_ObjType( &eType ) );
		}
		switch ( eType ) {
			case OBJTYPE_ATOM :
				m_pDecorator = new Decorator::AtomDecorator( m_spPart, m_spFCO );
				break;
			case OBJTYPE_SET :
				m_pDecorator = new Decorator::SetDecorator( m_spPart, m_spFCO );
				break;
			case OBJTYPE_MODEL :
				m_pDecorator = new Decorator::ModelDecorator( m_spPart, m_spFCO );
				break;
			case OBJTYPE_REFERENCE :
				m_pDecorator = new Decorator::ReferenceDecorator( m_spPart, m_spFCO );
				break;
		}
		if ( m_pDecorator ) {
			Decorator::PreferenceMap mapPrefs;
			m_pDecorator->initialize( mapPrefs );
		}

	}
	return S_OK;
}

STDMETHODIMP CBoxDecorator::Destroy()
{
	m_spProject = NULL;
	m_spPart = NULL;
	m_spFCO = NULL;
	m_bLocationSet = false;
	if ( m_pDecorator ) {
		delete m_pDecorator;
		m_pDecorator = NULL;
	}

	return S_OK;
}

STDMETHODIMP CBoxDecorator::GetMnemonic( BSTR *bstrMnemonic )
{
	*bstrMnemonic = CComBSTR("Box").Detach();

	return S_OK;
}

STDMETHODIMP CBoxDecorator::GetFeatures( feature_code *pFeatureCodes )
{
	*pFeatureCodes = F_RESIZABLE | F_HASLABEL | F_HASPORTS;

	return S_OK;
}

STDMETHODIMP CBoxDecorator::SetParam( BSTR bstrName, VARIANT vValue )
{
	return E_DECORATOR_UNKNOWN_PARAMETER;
}

STDMETHODIMP CBoxDecorator::GetParam( BSTR bstrName, VARIANT* pvValue)
{
	return E_DECORATOR_UNKNOWN_PARAMETER;
}

STDMETHODIMP CBoxDecorator::SetActive(VARIANT_BOOL vbIsActive)
{
	VERIFY_INITIALIZATION

	m_pDecorator->setActive( vbIsActive == VARIANT_TRUE );

	return S_OK;
}

STDMETHODIMP CBoxDecorator::GetPreferredSize( long* plWidth, long* plHeight )
{
	VERIFY_INITIALIZATION

	CSize cSize = m_pDecorator->getPreferredSize();
	*plWidth = cSize.cx;
	*plHeight = cSize.cy;

	return S_OK;
}


STDMETHODIMP CBoxDecorator::SetLocation( long sx, long sy, long ex, long ey )
{
	VERIFY_INITIALIZATION

	m_pDecorator->setLocation( CRect( sx, sy, ex, ey ) );
	m_bLocationSet = true;

	return S_OK;
}

STDMETHODIMP CBoxDecorator::GetLocation( long *sx, long *sy, long *ex, long *ey )
{
	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	CRect cRect = m_pDecorator->getLocation();
	*sx = cRect.left;
	*sy = cRect.top;
	*ex = cRect.right;
	*ey = cRect.bottom;

	return S_OK;
}

STDMETHODIMP CBoxDecorator::GetLabelLocation( long *sx, long *sy, long *ex, long *ey )
{
	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	CRect cRect = m_pDecorator->getLabelLocation();
	*sx = cRect.left;
	*sy = cRect.top;
	*ex = cRect.right;
	*ey = cRect.bottom;

	return S_OK;
}

STDMETHODIMP CBoxDecorator::GetPortLocation( IMgaFCO *pFCO, long *sx, long *sy, long *ex, long *ey )
{
	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	Decorator::PortDecorator* pPort = NULL;
	switch ( m_pDecorator->getType() ) {
		case OBJTYPE_MODEL :
			pPort = ( (Decorator::ModelDecorator*) m_pDecorator )->getPort( pFCO );
			break;
		case OBJTYPE_REFERENCE :
			Decorator::DecoratorBase* pReferenced = ( (Decorator::ReferenceDecorator*) m_pDecorator )->getReferenced();
			if ( pReferenced && pReferenced->getType() == OBJTYPE_MODEL )
				pPort = ( (Decorator::ModelDecorator*) pReferenced )->getPort( pFCO );
			break;
	}
	if ( pPort ) {
		CRect cRect = pPort->getBoxLocation();
		*sx = cRect.left;
		*sy = cRect.top;
		*ex = cRect.right;
		*ey = cRect.bottom;

		// if a reference has an icon specified for itself 
		// then it is not surrounded by a black rectangle.
		// if it doesn't have an icon, then the icon of the
		// referred element is used, and it is surrounded
		// that's why we shift port locations only if
		// the surrounding rectangle is there (borderwidth > 0)
		if ( m_pDecorator->getBorderWidth(false) > 0 && m_pDecorator->getType() == OBJTYPE_REFERENCE ) {	// HACK
			*sy += 2;
			*ey += 2;
			*sx += 2; // zolmol added
			*ex += 2; // zolmol added
		}
		return S_OK;
	}

	return E_DECORATOR_PORTNOTFOUND;
}

STDMETHODIMP CBoxDecorator::GetPorts( IMgaFCOs **portFCOs )
{
	VERIFY_INITIALIZATION

	CComPtr<IMgaFCOs> spFCOs;
	COMTHROW( spFCOs.CoCreateInstance( OLESTR( "Mga.MgaFCOs") ) );

	std::vector<Decorator::PortDecorator*>	vecPorts;
	switch ( m_pDecorator->getType() ) {
		case OBJTYPE_MODEL :
			vecPorts = ( (Decorator::ModelDecorator*) m_pDecorator )->getPorts();
			break;
		case OBJTYPE_REFERENCE :
			Decorator::DecoratorBase* pReferenced = ( (Decorator::ReferenceDecorator*) m_pDecorator )->getReferenced();
			if ( pReferenced && pReferenced->getType() == OBJTYPE_MODEL )
				vecPorts = ( (Decorator::ModelDecorator*) pReferenced )->getPorts();
			break;
	}

	for ( unsigned int i = 0 ; i < vecPorts.size() ; i++ )
		COMTHROW( spFCOs->Append( vecPorts[ i ]->getFCO() ) );

	*portFCOs = spFCOs.Detach();

	return S_OK;
}


STDMETHODIMP CBoxDecorator::Draw( HDC hdc )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	CDC dc;
	dc.Attach( hdc );
	m_pDecorator->draw( &dc );
	dc.Detach();

	return S_OK;
}

STDMETHODIMP CBoxDecorator::SaveState()
{
	VERIFY_INITIALIZATION

	return S_OK;
}