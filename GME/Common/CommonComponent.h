#ifndef COMMONCOMPONENT_H
#define COMMONCOMPONENT_H


inline HRESULT CreateMgaComponent(CComPtr<IMgaComponent> &comp, LPCOLESTR ProgID)
{
	
	comp = NULL;

	CComPtr<IUnknown> unk;
	HRESULT hr = unk.CoCreateInstance(ProgID);
	if (SUCCEEDED(hr)) {
		hr = unk.QueryInterface(&comp);
		if (FAILED(hr)) {
			CComPtr<IDispatch> disp;
			hr = unk.QueryInterface(&disp);
			if (SUCCEEDED(hr)) {
				hr = comp.CoCreateInstance(OLESTR("MgaUtil.ComponentProxy"));
				if (SUCCEEDED(hr)) {
					CComPtr<IMgaComponentProxy> proxy;
					hr = comp.QueryInterface(&proxy);
					if (SUCCEEDED(hr)) {
						hr = proxy->put_DispatchComponent(disp);
					}
				}
			}
		}
	}
	return hr;
}

inline HRESULT CreateMgaComponent(CComPtr<IMgaComponent> &comp, REFCLSID classID)
{
	
	comp = NULL;

	CComPtr<IUnknown> unk;
	HRESULT hr = unk.CoCreateInstance(classID);
	if (SUCCEEDED(hr)) {
		hr = unk.QueryInterface(&comp);
		if (FAILED(hr)) {
			CComPtr<IDispatch> disp;
			hr = unk.QueryInterface(&disp);
			if (SUCCEEDED(hr)) {
				hr = comp.CoCreateInstance(OLESTR("MgaUtil.ComponentProxy"));
				if (SUCCEEDED(hr)) {
					CComPtr<IMgaComponentProxy> proxy;
					hr = comp.QueryInterface(&proxy);
					if (SUCCEEDED(hr)) {
						hr = proxy->put_DispatchComponent(disp);
					}
				}
			}
		}
	}
	return hr;
}


#endif // COMMONCOMPONENT_H
