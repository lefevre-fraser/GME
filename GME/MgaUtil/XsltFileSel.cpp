#include "stdafx.h"

#include "XsltFileSel.h"
#include "XsltDial.h"

STDMETHODIMP CXsltFileSel::StartXslt( BSTR def_in_f_name, BSTR* out) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CWaitCursor w;
	CXSLTDial dlg;
	CopyTo( def_in_f_name, dlg.m_inputXmlFileName);
	CComBstrObj error;

	if ( dlg.DoModal() == IDOK)
	{
		w.Restore();

		try
		{
			CComPtr<IMgaXslt> xslt;
			COMTHROW( xslt.CoCreateInstance(L"Mga.MgaXslt") );
			ASSERT( xslt != NULL );
			
			COMTHROW( 
				xslt->ApplyXslt( 
								PutInBstr( dlg.m_stylesheetFileName), 
								PutInBstr( dlg.m_inputXmlFileName),
								PutInBstr( dlg.m_outputXmlFileName),
								PutOut( error) )
					);
			
			CopyTo( dlg.m_outputXmlFileName, out);
			AfxMessageBox( "XSLT script applied. " + dlg.m_outputXmlFileName + " generated.", MB_ICONINFORMATION);
			return S_OK;
		}
		catch(hresult_exception &e)
		{
			CString msg;
			switch ( e.hr) {
			case E_XSLT_XERCES_INIT: 
				msg = "Xslt: Xerces initialization failed.";
				AfxMessageBox( msg, MB_ICONSTOP);
				break;
			case E_XSLT_COMPILE_ERROR:
				CopyTo( error, msg);
				msg = "Xslt: Stylesheet compilation failed. " + msg;
				AfxMessageBox( msg, MB_ICONSTOP);
				break;
			case E_XSLT_TRANSF_ERROR:
				CopyTo( error, msg);
				msg = "Xslt: Transformation failed. " + msg;
				AfxMessageBox( msg, MB_ICONSTOP);
				break;
			case E_XSLT_ERROR:
			default:
				msg = "Xslt error.";
				AfxMessageBox( msg, MB_ICONSTOP);
			};

			return e.hr;
		}
	}
	return E_XSLTFILESEL_USER_ABORTED;
}

