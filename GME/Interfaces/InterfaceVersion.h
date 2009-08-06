#define INTERFACEVERSION_INCLUDED

// Interfaceversion.h file

// CHECKSUM Core.idl = B6534C3E
// CHECKSUM Meta.idl = DF870113
// CHECKSUM Mga.idl = 534AEB6A
// CHECKSUM MgaUtil.idl = B850E056
// CHECKSUM MgaDecorator.idl = 14706DCC
// CHECKSUM Gme.idl = B603BECA
// CHECKSUM Parser.idl = 1EAAB0F2


// if you ever change these version numbers manually:
//	-- increase the major version part by one (the four left digits)
//  -- set the minor part (four right digits) to 0001
//  -- keep them in sync
//  -- never decrease it
cpp_quote("#ifndef INTERFACE_VERSION")
cpp_quote("#define INTERFACE_VERSION 0x000200E6")
cpp_quote("#endif //INTERFACE_VERSION")
#define INTERFACE_VERSION 0x000200E6
