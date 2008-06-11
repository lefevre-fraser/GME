// RegExp.h

#ifndef __REGEXP_H__
#define __REGEXP_H__

//class CString; //commented for VC7
class regexp;

class CRegExp
{
public:
	enum { NSUBEXP = 10 };

	CRegExp();
	CRegExp( LPCTSTR exp, BOOL iCase = 0 );
	CRegExp( const CRegExp &r );
	~CRegExp();
	const CRegExp & operator=( const CRegExp & r );

	bool Match( const TCHAR * s );
	int SubStrings() const;
	
	const CString operator[]( unsigned int i ) const;
	int SubStart( unsigned int i ) const;
	int SubLength( unsigned int i ) const;

	CString GetReplaceString( LPCTSTR source ) const;

	CString GetErrorString() const;
	bool CompiledOK() const;

#if defined( _RE_DEBUG )
	void Dump();
#endif
private:
	const TCHAR * string;	/* used to return substring offsets only */
	mutable CString m_szError;
	regexp * rc;

	void ClearErrorString() const;
	int safeIndex( unsigned int i ) const;

};

#endif

