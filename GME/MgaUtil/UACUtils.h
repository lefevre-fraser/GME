#pragma once

class CUACUtils
{
public:
	static bool isVistaOrLater();

	template <typename T>
	static HRESULT CreateElevatedInstance(REFCLSID classId,
                               T** object, HWND window = 0)
	{
		BIND_OPTS3 bindOptions;
		::ZeroMemory(&bindOptions, sizeof (BIND_OPTS3));
		bindOptions.cbStruct = sizeof (BIND_OPTS3);
		bindOptions.hwnd = window;
		bindOptions.dwClassContext = CLSCTX_LOCAL_SERVER;

		CStringW string;
		const int guidLength = 39;

		::StringFromGUID2(classId, string.GetBufferSetLength(guidLength),
									 guidLength);

		string.ReleaseBuffer();
		string.Insert(0, L"Elevation:Administrator!new:");

		return ::CoGetObject(string,
							 &bindOptions,
							 __uuidof(T),
							 reinterpret_cast<void**>(object));
	}

	static void SetShieldIcon(const CButton& button, bool on=true);
};
