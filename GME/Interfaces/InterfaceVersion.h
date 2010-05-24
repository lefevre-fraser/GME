#define INTERFACEVERSION_INCLUDED

// Interfaceversion.h file

// CHECKSUM Core.idl = B6534C3E
// CHECKSUM Meta.idl = DF870113
// CHECKSUM Mga.idl = 71217380
// CHECKSUM MgaUtil.idl = 8FA82FC3
// CHECKSUM MgaDecorator.idl = FBD111E7
// CHECKSUM Gme.idl = B603BECA
// CHECKSUM Parser.idl = 1EAAB0F2


// if you ever change these version numbers manually:
//	-- increase the major version part by one (the four left digits)
//  -- set the minor part (four right digits) to 0001
//  -- keep them in sync
//  -- never decrease it
cpp_quote("#ifndef INTERFACE_VERSION")
cpp_quote("#define INTERFACE_VERSION 0x000200E8")
cpp_quote("#endif //INTERFACE_VERSION")
#define INTERFACE_VERSION 0x000200E8
