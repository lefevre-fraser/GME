
class CXslt
{
public:
	static void doNativeXslt( LPCTSTR stylesheet, LPCTSTR infile, LPCTSTR outfile, CString& error);
	static void doDispatchXslt( LPCTSTR stylesheet, LPCTSTR infile, LPCTSTR outfile, CString& error);
};

// CMgaXsltDriver wrapper class

class CMgaXsltDriver : public COleDispatchDriver
{
public:
	CMgaXsltDriver(){} // Calls COleDispatchDriver default constructor
	CMgaXsltDriver(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMgaXsltDriver(const CMgaXsltDriver& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:

	// IMgaXslt methods
public:
	STDMETHOD(ApplyXslt)(LPCTSTR stylesheet, LPCTSTR infile, LPCTSTR outfile, BSTR * error)
	{
		HRESULT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x60020000, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, stylesheet, infile, outfile, error);
		return result;
	}

	// IMgaXslt properties
public:

};
