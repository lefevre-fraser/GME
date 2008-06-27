#pragma once
#include "stdafx.h"
#include <string>
#include "ComponentLib.h"
#include "GMECOM.h"
#include "Console.h"

//interface IMgaFCO;
//interface IMgaFolder;
//interface IMgaProject;

namespace Util
{
	CComBSTR	Copy( const std::string& str )
	{
		return ( str.empty() ) ? CComBSTR() : CComBSTR( str.c_str() );
	}

	std::string	Copy( const CComBSTR& bstr )
	{
		CString str( bstr );
		std::string strResult( str.GetBuffer( str.GetLength() ) );
		str.ReleaseBuffer();
		return strResult;
	}

	std::string CopyV( const CComVariant& v)
	{
		if (v.vt != (VT_UI1 | VT_ARRAY) || 
			v.parray == NULL || 
			v.parray->cbElements != 1 ||
			v.parray->cDims != 1 ||
			v.parray->rgsabound[0].cElements != sizeof(GUID)) 
		{
			ASSERT( 0);
			return "";
		}

		GUID guid;
		unsigned char *start = (unsigned char*)&guid;
		unsigned char *end = (unsigned char*)(&guid+1);
		const unsigned char *q = NULL;

		COMTHROW( SafeArrayAccessData(v.parray, (void**)&q) );

		if (q == NULL ) {
			ASSERT( 0);
			return "";
		}

		memcpy( start, q, (end - start) * sizeof(unsigned char) );
		COMTHROW( SafeArrayUnaccessData(v.parray) );

		wchar_t *guidstr = NULL;
		COMTHROW(StringFromCLSID(guid,&guidstr));

		std::string result = Util::Copy( guidstr );

		CoTaskMemFree(guidstr); 

		return result;
	}


	std::string gvbp( IMgaRegNode* p_rn, const std::string& p_path)
	{
		ASSERT( p_path.substr( 0, 1) != "/");
		try
		{
			CComBSTR rv;
			CComPtr<IMgaRegNode> subn;
			COMTHROW( p_rn->get_SubNodeByName( Util::Copy( p_path), &subn));
			
			COMTHROW( subn->get_Value( &rv));
			return Util::Copy( rv);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with gvbp() with path " + p_path, MSG_ERROR);
			throw;
		}
		
	}

	void svbp( IMgaRegNode* p_rn, const std::string& p_path, const std::string& p_value)
	{
		ASSERT( p_path.substr( 0, 1) != "/");
		try
		{
			CComPtr<IMgaRegNode> subn;
			COMTHROW( p_rn->get_SubNodeByName( Util::Copy( p_path), &subn));
		
			COMTHROW( subn->put_Value( Util::Copy( p_value)));
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with svbp() with path " + p_path, MSG_ERROR);
			throw;
		}

	}

	std::string getReg( IMgaFolder* ptr, const std::string& p_path)
	{
		ASSERT( p_path.substr( 0, 1) != "/");
		try {
			CComBSTR val;
			COMTHROW( ptr->get_RegistryValue( Copy( p_path), &val));

			return Copy( val);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with getReg() with path " + p_path, MSG_ERROR);
			throw;
		}
	}

	std::string getReg( IMgaFCO* ptr, const std::string& p_path)
	{
		ASSERT( p_path.substr( 0, 1) != "/");
		try {
			CComBSTR val;
			COMTHROW( ptr->get_RegistryValue( Copy( p_path), &val));

			return Copy( val);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with getReg() with path " + p_path, MSG_ERROR);
			throw;
		}
	}

	void setReg( IMgaFCO* ptr, const std::string& p_path, const std::string& p_value)
	{
		ASSERT( p_path.substr( 0, 1) != "/");
		try {
			COMTHROW( ptr->put_RegistryValue( Copy( p_path), Copy( p_value)));
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with getReg() with path " + p_path, MSG_ERROR);
			throw;
		}
	}

	bool islibobj( IMgaObject* p_ptr)
	{
		try 
		{
			VARIANT_BOOL vb = VARIANT_FALSE;
			if( p_ptr) COMTHROW( p_ptr->get_IsLibObject( &vb));
			return vb == VARIANT_TRUE; // element's parent is in a library?
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with isliboj()", MSG_ERROR);
			throw;
		}
	}

	bool isproxy( IMgaFCO* p_ptr)
	{
		try
		{
			CComPtr<IMgaMetaFCO> meta;
			if( p_ptr) COMTHROW( p_ptr->get_Meta( &meta));

			CComBSTR b_kind;
			if( meta) COMTHROW( meta->get_Name( &b_kind));

			std::string kind = Util::Copy( b_kind);
			return kind.find( "Proxy") != std::string::npos;
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with isproxy()", MSG_ERROR);
			throw;
		}
	}

	std::string name( IMgaObject* ptr)
	{
		try
		{
			CComBSTR nm;
			if( ptr) COMTHROW( ptr->get_Name( &nm));
			return Util::Copy( nm);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with name()", MSG_ERROR);
			throw;
		}
	}

	std::string name( IMgaFCO* ptr)
	{
		try
		{
			CComBSTR nm;
			if( ptr) COMTHROW( ptr->get_Name( &nm));
			return Util::Copy( nm);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with name()", MSG_ERROR);
			throw;
		}
	}

	std::string kind( IMgaObject* p_ptr)
	{
		try
		{
			CComPtr<IMgaMetaBase> meta;
			if( p_ptr) COMTHROW( p_ptr->get_MetaBase( &meta));

			CComBSTR b_kind;
			if( meta) COMTHROW( meta->get_Name( &b_kind));

			return Util::Copy( b_kind);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with kind()", MSG_ERROR);
			throw;
		}
	}

	std::string getStrAttr( IMgaFCO* p_ptr, const std::string& p_attrName)
	{
		try
		{
			CComBSTR val;
			COMTHROW( p_ptr->get_StrAttrByName( Copy( p_attrName), &val));

			return Util::Copy( val);
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with getStrAttr with attr " + p_attrName + " on " + Util::name( p_ptr), MSG_ERROR);
			throw;
		}
	}

	bool getBoolAttr( IMgaFCO* p_ptr, const std::string& p_attrName)
	{
		try
		{
			VARIANT_BOOL vb;
			COMTHROW( p_ptr->get_BoolAttrByName( Copy( p_attrName), &vb));

			return vb == VARIANT_TRUE;
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with getBoolAttr with attr " + p_attrName + " on " + Util::name( p_ptr), MSG_ERROR);
			throw;
		}
	}

	long getLongAttr( IMgaFCO* p_ptr, const std::string& p_attrName)
	{
		try
		{
			long val;
			COMTHROW( p_ptr->get_IntAttrByName( Copy( p_attrName), &val));

			return val;
		} 
		catch(...) 
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with getLongAttr with attr " + p_attrName + " on " + Util::name( p_ptr), MSG_ERROR);
			throw;
		}

	}

	IMgaAttribute* getAttrib( IMgaFCO* p_fco, const std::string& p_attrName)
	{
		CComBSTR                   attr_name       = Util::Copy( p_attrName);
		CComPtr<IMgaAttribute>     found_attr      = 0;
		CComPtr<IMgaMetaAttribute> found_meta_attr = 0;

		// property Status of definition: 0: here, -1: in meta, >=1: inherited, -2: undefined")] 
		CComPtr<IMgaAttributes> attrs;
		COMTHROW( p_fco->get_Attributes( &attrs));
		long c = 0;
		if( attrs) COMTHROW( attrs->get_Count( &c));
		for( long i = 1; i <= c; ++i)
		{
			CComPtr<IMgaAttribute> item;
			COMTHROW( attrs->get_Item( i, &item));
			CComPtr<IMgaMetaAttribute> meta_attr;
			if( item) COMTHROW( item->get_Meta( &meta_attr));

			CComBSTR nm;
			if( meta_attr) COMTHROW( meta_attr->get_Name( &nm));

			if( attr_name == nm)
			{
				found_attr      = item;
				found_meta_attr = meta_attr;
				break;
			}

		}

		return found_attr;
	}

	bool isAttrStatHere( IMgaFCO* p_fco, const std::string& p_attrName)
	{
		try
		{
			CComBSTR                   attr_name       = Util::Copy( p_attrName);
			CComPtr<IMgaAttribute>     found_attr      = 0;
			CComPtr<IMgaMetaAttribute> found_meta_attr = 0;

			// property Status of definition: 0: here, -1: in meta, >=1: inherited, -2: undefined")] 
			CComPtr<IMgaAttributes> attrs;
			COMTHROW( p_fco->get_Attributes( &attrs));
			long c = 0;
			if( attrs) COMTHROW( attrs->get_Count( &c));
			for( long i = 1; i <= c; ++i)
			{
				CComPtr<IMgaAttribute> item;
				COMTHROW( attrs->get_Item( i, &item));
				CComPtr<IMgaMetaAttribute> meta_attr;
				if( item) COMTHROW( item->get_Meta( &meta_attr));

				CComBSTR nm;
				if( meta_attr) COMTHROW( meta_attr->get_Name( &nm));

				if( attr_name == nm)
				{
					found_attr      = item;
					found_meta_attr = meta_attr;
					break;
				}

			}


			ASSERT( found_attr);
			if( !found_attr)
				return false;

			long stat = -2;
			COMTHROW( found_attr->get_Status( &stat));

			return stat >= 0;
		}
		catch(...) 
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed in isAttrStatHere with attribute " + p_attrName + " on " + Util::name( p_fco), MSG_ERROR);
			throw;
		}
	}

	std::string composePath( IMgaObject * ptr, bool p_upUntilFolders) // should produce an output like: SF/OutputSignal
	{
		CComPtr<IMgaObject> cur = ptr;
		try
		{
			std::string path;
			while( cur)
			{
				if( !path.empty()) 
					path.insert( 0, 1,'/');

				std::string nm = Util::name( cur);
				path.insert( 0, nm.c_str());

				CComPtr<IMgaObject> parent;
				objtype_enum ot;
				COMTHROW( cur->GetParent( &parent, &ot));
				cur = parent;
				if( p_upUntilFolders && ot == OBJTYPE_FOLDER)
					cur = 0;
			}

			return path;
		}
		catch(...)
		{
			ASSERT( 0);
			Console::ssendMsg( "Failed with composePath()", MSG_ERROR);
			throw;
		}
	}
}
