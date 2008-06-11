//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLTypeExGMEEC.h
//
//###############################################################################################################################################

#ifndef OCLTypeExGMEEC_h
#define OCLTypeExGMEEC_h

#include "OCLCommonEx.h"
#include "OCLTypeExBasic.h"

namespace OclGmeEC
{

//##############################################################################################################################################
//
//	T Y P E   O F   ocl::String
//
//##############################################################################################################################################

	class TStringEx_MethodFactory
		: public OclBasic::TString_MethodFactory
	{
		public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   ocl::Collection
//
//##############################################################################################################################################

	class TCollectionEx_MethodFactory
		: public OclBasic::TCollection_MethodFactory
	{
		public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Object
//
//##############################################################################################################################################

	class TObject_AttributeFactory
		: public OclImplementation::AttributeFactory
	{
		 public :
			 virtual void GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures );
	};


	class TObject_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Folder
//
//##############################################################################################################################################

	class TFolder_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::FCO
//
//##############################################################################################################################################

	class TFCO_AttributeFactory
		: public OclImplementation::AttributeFactory
	{
		 public :
			 virtual void GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures );
	};


	class TFCO_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Model
//
//##############################################################################################################################################

	class TModel_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Atom
//
//##############################################################################################################################################

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Connection
//
//##############################################################################################################################################

	class TConnection_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Reference
//
//##############################################################################################################################################

	class TReference_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Set
//
//##############################################################################################################################################

	class TSet_MethodFactory
		: public OclImplementation::MethodFactory
	{
		public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::Project
//
//##############################################################################################################################################

	class TProject_AttributeFactory
		: public OclImplementation::AttributeFactory
	{
		 public :
			 virtual void GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures );
	};

	class TProject_MethodFactory
		: public OclImplementation::MethodFactory
	{
		 public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   gme::ConnectionPoint
//
//##############################################################################################################################################

	class TConnectionPoint_AttributeFactory
		: public OclImplementation::AttributeFactory
	{
		 public :
			 virtual void GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures );
	};


	class TConnectionPoint_MethodFactory
		: public OclImplementation::MethodFactory
	{
		public :
			virtual void GetFeatures( const OclSignature::Method& signature, OclMeta::MethodVector& vecFeatures );
	};

//##############################################################################################################################################
//
//	T Y P E   O F   D E R I V E D   O F   gme::FCO
//
//##############################################################################################################################################

	class TFCODerived_AttributeFactory
		: public OclImplementation::AttributeFactory
	{
		private :
			CComPtr<IMgaFCO> m_spFCO;

		public :
							TFCODerived_AttributeFactory( CComPtr<IMgaFCO> spFCO );

			 virtual	void 	GetFeatures( const OclSignature::Attribute& signature, OclMeta::AttributeVector& vecFeatures );
		private :
					void	GetAttributeObjects( const std::string& strName, CComPtr<IMgaFCO> spFCO, OclMeta::AttributeVector& vecFeatures, OclCommonEx::FCOVector& vecExamined  );
	};

//##############################################################################################################################################
//
//	G L O B A L   F A C T O R I E S
//
//##############################################################################################################################################

	class TypeFactory
		: public OclImplementation::TypeFactory
	{
		 private :
		 	CComPtr<IMgaProject>	m_spProject;

		 public :
		 					TypeFactory( CComPtr<IMgaProject> spProject );

							virtual  void 	GetTypes( const std::string& strName, const std::string& strNSpace, std::vector<OclMeta::Type*>& vecTypes, std::string& nameRes );
		private :
					void 	GetStereotypes( const std::string& strName, std::vector<OclMeta::Type*>& vecTypes );
					void 	GetDynamicTypes( const std::string& strName, std::vector<OclMeta::Type*>& vecTypes, std::string& strNameResult );
	};

}; // namespace OclGmeEC

#endif // OCLTypeExGMEEC_h