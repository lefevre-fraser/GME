#ifndef HELPER_H_259823495872394857
#define HELPER_H_259823495872394857

#include <list>
#include <string>

std::list<std::string> tokenizer( std::string m, char separator = '/', bool include_separator = true);

bool findExact( const std::string& m, const std::string& to_find);

std::string makeRel( std::string& nm, std::string& nm2);

std::string makeViewable( const std::string& m);

std::string makeNameViewable( const std::string& m);

CComBSTR makeLink( CComObjPtr<IMgaObject> obj, const std::string& nm_2 = "", bool use_anyway_nm_2 = false);

CComBSTR makeLink( CComObjPtr<IMgaFCO> obj, const std::string& nm_2 = "", bool use_anyway_nm_2 = false);
CComBSTR makeLink( CComObjPtr<IMgaReference> obj, const std::string& nm_2 = "", bool use_anyway_nm_2 = false);
CComBSTR makeLink( CComObjPtr<IMgaSet> obj, const std::string& nm_2 = "", bool use_anyway_nm_2 = false);


#endif // HELPER_H_259823495872394857

