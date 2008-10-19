#ifndef DECORATOR_STD_H
#define DECORATOR_STD_H


#define	GME_BACKGROUND_COLOR		RGB(0xff, 0xff, 0xff)
#define	GME_BORDER_COLOR			RGB(0x00, 0x00, 0x00)
#define	GME_MODEL_COLOR				RGB(0xc0, 0xc0, 0xc0)
#define	GME_NAME_COLOR				RGB(0x00, 0x00, 0x00)
#define	GME_PORTNAME_COLOR			RGB(0x60, 0x60, 0x60)
#define	GME_CONNECTION_COLOR 		RGB(0x00, 0x00, 0x00)
#define	GME_GRID_COLOR				RGB(0xd0, 0xd0, 0xd0)
#define	GME_BLACK_COLOR				RGB(0x00, 0x00, 0x00)
#define	GME_WHITE_COLOR				RGB(0xff, 0xff, 0xff)
#define	GME_GREY_COLOR				RGB(0xc0, 0xc0, 0xc0)
#define GME_GRAYED_OUT_COLOR		RGB(0xde, 0xde, 0xde)

#define GME_GRID_SIZE				7
#define GME_PORT_SIZE				11
#define GME_PORT_OFFSET				3
#define GME_PORT_BORDER_OFFSET		10
#define GME_GRID_BORDER_OFFSET		3
#define GME_MODEL_WIDTH				113
#define GME_LEFTPORT_MARGIN			100
#define GME_MODEL_HEIGHT			70
//#define GME_3D_BORDER_SIZE			3

#define HELP_PREF					"help"
#define COLOR_PREF					"color"
#define CONN_LINE_TYPE_PREF			"lineType"
#define MODEL_BACKGROUND_COLOR_PREF	"backgroundColor"
#define MODEL_BORDER_COLOR_PREF		"borderColor"
#define PORT_NAME_COLOR_PREF		"portColor"
#define NAME_COLOR_PREF				"nameColor"
#define NAME_POS_PREF				"namePosition"
#define ICON_PREF					"icon"
#define PORTICON_PREF				"porticon"

#define	 META_DEFAULT_SHOWABSTRACT		true
#define	 META_DEFAULT_SHOWATTRIBUTES	true

#define  META_ATTRIBUTE_SEP			" : "

#define	 META_DECORATOR_MARGINX		6
#define	 META_DECORATOR_MARGINY		4
#define	 META_DECORATOR_GAPY		0
#define  META_DECORATOR_MINATTRSIZE	13
#define  META_INHERITANCE_WIDTH		24
#define	 META_INHERITANCE_HEIGHT	(0.866 * META_INHERITANCE_WIDTH)
#define	 META_INHERITANCE_RADIUS	(META_INHERITANCE_HEIGHT / 4)
#define  META_EQUIVALENCE_WIDTH		(2 * META_INHERITANCE_HEIGHT)
#define	 META_EQUIVALENCE_HEIGHT	META_INHERITANCE_WIDTH
#define	 META_CONNECTOR_RAIDUS		4

#define	 META_CLASS_BGCOLOR			RGB(0xFF,0xFF,0xFF)
#define	 META_TRANSPARENT_COLOR		RGB(0xFF,0xFF,0xFF)

typedef enum {NULLSHAPE, CLASS, CLASSPROXY, CONNECTOR, CONSTRAINT, EQUIVALENCE, INHERITANCE, INTINHERITANCE, IMPINHERITANCE, CONSTRAINTFUNC } ShapeCode;

#define  META_ABSTRACT_ATTR			"IsAbstract"

#define	 META_ATOM_KIND				"Atom"
#define	 META_ATOMPROXY_KIND		"AtomProxy"
#define	 META_MODEL_KIND			"Model"
#define	 META_MODELPROXY_KIND		"ModelProxy"
#define	 META_REFERENCE_KIND		"Reference"
#define	 META_REFERENCEPROXY_KIND	"ReferenceProxy"
#define	 META_SET_KIND				"Set"
#define	 META_SETPROXY_KIND			"SetProxy"
#define	 META_CONNECTION_KIND		"Connection"
#define	 META_CONNECTIONPROXY_KIND	"ConnectionProxy"
#define	 META_FCO_KIND				"FCO"
#define	 META_FCOPROXY_KIND			"FCOProxy"

#define	 META_FOLDER_KIND			"Folder"
#define	 META_FOLDERPROXY_KIND		"FolderProxy"

#define	 META_ASPECT_KIND			"Aspect"
#define	 META_ASPECTPROXY_KIND		"AspectProxy"

#define	 META_BOOLEANATTR_KIND		"BooleanAttribute"
#define	 META_ENUMATTR_KIND			"EnumAttribute"
#define	 META_FIELDATTR_KIND		"FieldAttribute"

#define	 META_CONSTRAINT_KIND		"Constraint"
#define	 META_CONSTRAINTFUNC_KIND	"ConstraintFunc"

#define	 META_CONNECTOR_KIND		"Connector"

#define	 META_EQUIVALENCE_KIND		"Equivalence"
#define	 META_SAMEFOLDER_KIND		"SameFolder"
#define	 META_SAMEASPECT_KIND		"SameAspect"


#define	 META_INHERITANCE_KIND		"Inheritance"
#define	 META_IMPINHERITANCE_KIND	"ImplementationInheritance"
#define	 META_INTINHERITANCE_KIND	"InterfaceInheritance"

#define  META_BOOLEANATTR_LABEL		"bool"
#define  META_ENUMATTR_LABEL		"enum"
#define  META_FIELDATTR_LABEL		"field"

#define  META_PARAM_SHOWATTRIBUTES	"showattributes"
#define  META_PARAM_SHOWABSTRACT	"showabstract"
#define  META_PARAM_VAL_TRUE		"true"
#define  META_PARAM_VAL_FALSE		"false"

#define  E_METADECORATOR_KINDNOTSUPPORTED	0x80737050
#define  E_METADECORATOR_INVALID_PARAMVALUE	0x80737051


#endif	//DECORATOR_STD_H