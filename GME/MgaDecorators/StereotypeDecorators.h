//################################################################################################
//
// Mga Decorator Base
//	StereotypeDecorators.h
//
//################################################################################################

#ifndef StereotypeDecorator_h
#define StereotypeDecorator_h

#pragma warning( disable : 4786 )

#include "StdAfx.h"
#include "mga.h"
#include <vector>
#include <map>
#include "PreferenceVariant.h"

namespace Decorator
{
//################################################################################################
//
//	CLASS : DecoratorBase
//
//################################################################################################

	class DecoratorBase
	{
		protected :
			CComPtr<IMgaFCO>			m_spFCO;
			CComPtr<IMgaMetaPart>		m_spPart;
			objtype_enum				m_eType;
			BitmapBase*					m_pBitmap;
			TileVector*					m_pTileVector;
			CRect						m_Rect;
			CString						m_strName;
			std::vector<CString>		m_vecName;
			ELocation					m_eNameLocation;
			bool						m_bNameEnabled;
			long						m_iNameWrapCount;
			COLORREF					m_crName;
			bool						m_bHasViolation;
			bool						m_bActive;
			int							m_iFontKey;
			int							m_iMaxTextLength;
			long						m_lBorderWidth;
			bool						m_bReferenced;
			COLORREF					m_crOverlay;
			bool						m_bOverlay;
			COLORREF					m_crBorder;

		protected :
			DecoratorBase( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO );
		public :
			virtual void initialize( PreferenceMap& mapPreferences );
			virtual ~DecoratorBase() {};

			void					setLocation( const CRect& cRect );
			CRect					getLocation() const;
			virtual void 			setActive( bool bActive );
			void					setReferenced();
			CComPtr<IMgaFCO>		getFCO() const;
			objtype_enum			getType() const;
			virtual CSize			getPreferredSize() const;
			virtual void			setBoxLocation( const CRect& cRect );
			virtual CRect			getBoxLocation( bool bWithBorder = false ) const;
			virtual CPoint			getLabelPosition() const;
			virtual CRect			getLabelLocation() const;
			ECoordRefPoint			getAlignment() const;
			long					getBorderWidth( bool bActive = true ) const;

			void 					draw( CDC* pDC ) const;

			virtual void			drawBorder( CDC* pDC ) const;
			virtual void			drawBackground( CDC* pDC ) const;
			virtual void			drawLabel( CDC* pDC ) const;
			virtual void			drawIcons( CDC* pDC ) const;
	};

//################################################################################################
//
//	CLASS : PortDecorator
//
//################################################################################################

	class PortDecorator
		: public DecoratorBase
	{
		private :
			CPoint		m_ptInner;
			bool		m_bInsideContainer;
			ELocation	m_eAdjust;

		public :
			PortDecorator( CComPtr<IMgaFCO> spFCO, const CPoint& ptInner );
			virtual void initialize( PreferenceMap& mapPreferences );

			CPoint				getInnerPosition() const;
			virtual CSize		getPreferredSize() const;
			virtual void		drawBackground( CDC* pDC ) const;
			virtual CPoint		getLabelPosition() const;
			virtual long		getLongest() const;
	};

//################################################################################################
//
//	CLASS : TypeableDecorator
//
//################################################################################################

	class TypeableDecorator
		: public DecoratorBase
	{
		protected :
			bool		m_bTypeIconEnabled;
			bool		m_bTypeNameEnabled;
			CString		m_strTypeName;
			int			m_iTypeInfo;

		protected :
			TypeableDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO );
		public :
			virtual void initialize( PreferenceMap& mapPreferences );
			virtual ~TypeableDecorator() {};

			virtual CPoint		getLabelPosition() const;
			virtual CRect		getLabelLocation() const;

			virtual void		drawLabel( CDC* pDC ) const;
			virtual void		drawIcons( CDC* pDC ) const;
	};

//################################################################################################
//
//	CLASS : AtomDecorator
//
//################################################################################################

	class AtomDecorator
		: public TypeableDecorator
	{
		public :
			AtomDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO );
			virtual void	initialize( PreferenceMap& mapPreferences );
			virtual void	drawBackground( CDC* pDC ) const;
	};

//################################################################################################
//
//	CLASS : SetDecorator
//
//################################################################################################

	class SetDecorator
		: public TypeableDecorator
	{
		public :
			SetDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO );

			virtual void	initialize( PreferenceMap& mapPreferences );
			virtual void	drawBackground( CDC* pDC ) const;
	};

//################################################################################################
//
//	CLASS : ModelDecorator
//
//################################################################################################

	class ModelDecorator
		: public TypeableDecorator
	{
		private :
			std::vector<PortDecorator*>		m_vecLeftPorts;
			std::vector<PortDecorator*>		m_vecRightPorts;
			CComPtr<IMgaMetaAspect>			m_spAspect;
			long							m_iMaxPortTextLength;
			COLORREF						m_crPortText;
			bool							m_bPrtLabInside;
			long							m_iLongestPortTextLength;

		public :
			ModelDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO );
			virtual void initialize( PreferenceMap& mapPreferences );
			~ModelDecorator();

			virtual CSize				getPreferredSize() const;
			virtual void				setBoxLocation( const CRect& cRect );
			virtual void 				setActive( bool bActive );
			std::vector<PortDecorator*>	getPorts() const;
			PortDecorator*				getPort( CComPtr<IMgaFCO> ) const;

			virtual void				drawBackground( CDC* pDC ) const;

		private :
			void 						loadPorts();
			void 						orderPorts( std::vector<PortDecorator*>& vecPorts );

	};

//################################################################################################
//
//	CLASS : ReferenceDecorator
//
//################################################################################################

	class ReferenceDecorator
		: public TypeableDecorator
	{
		private :
			DecoratorBase*		m_pReferenced;
			bool 				m_bIconRequired;

		public :
			ReferenceDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO );
			virtual void initialize( PreferenceMap& mapPreferences );
			~ReferenceDecorator();

			virtual CSize			getPreferredSize() const;
			virtual void			setBoxLocation( const CRect& cRect );
			virtual void 			setActive( bool bActive );
			DecoratorBase*			getReferenced() const;

			virtual void			drawBackground( CDC* pDC ) const;
			virtual void			drawIcons( CDC* pDC ) const;
	};

}; // namespace Decorator

#endif // StereotypeDecorator_h