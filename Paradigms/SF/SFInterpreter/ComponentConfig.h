///////////////////////////////////////////////////////////////////////////
// ComponentConfig.h, component configuration parameters.
//
// Initially generated by the component wizard. Feel free to manually edit.
///////////////////////////////////////////////////////////////////////////

// Component framework type
#define BONCOMPONENT

// COM UUID-s, names and progID
#define TYPELIB_UUID "C82BDC79-7F10-4A22-B91B-2CF6C39B844E"
#define TYPELIB_NAME "MGA Interpreter TypeLibrary (SFInterpreter)"
#define COCLASS_UUID "980075B4-C664-462B-BDD4-6E875CD1EC41"
#define COCLASS_NAME "MGA Interpreter CoClass (SFInterpreter)"
#define COCLASS_PROGID "MGA.Interpreter.SFInterpreter"

#define COCLASS_UUID_EXPLODED1  0x980075b4
#define COCLASS_UUID_EXPLODED2   0xc664
#define COCLASS_UUID_EXPLODED3   0x462b
#define COCLASS_UUID_EXPLODED4   0xbd
#define COCLASS_UUID_EXPLODED5   0xd4
#define COCLASS_UUID_EXPLODED6   0x6e
#define COCLASS_UUID_EXPLODED7   0x87
#define COCLASS_UUID_EXPLODED8   0x5c
#define COCLASS_UUID_EXPLODED9   0xd1
#define COCLASS_UUID_EXPLODED10  0xec
#define COCLASS_UUID_EXPLODED11  0x41


// This name will appear in the popup window for interpreter selection.
#define COMPONENT_NAME "SFInterpreter"


// This text will appear in the toolbar icon tooltip and in the menu.
#define TOOLTIP_TEXT "SignalFlow Interpreter"

// This macro determines the component type (addon vs. interpreter):
#define GME_INTERPRETER

// The name of the paradigm(s). The GME will use this component
// for this paradigm. Separate the names of paradigms by commas.
#define PARADIGMS "SF"


// not defined: #define BON_ICON_SUPPORT

// not defined: #define BON_CUSTOM_TRANSACTIONS

#define REGISTER_SYSTEMWIDE
