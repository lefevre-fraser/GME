#define INTERFACEVERSION_INCLUDED

// Interfaceversion.h file

// CHECKSUM Core.idl = B6534C3E
// CHECKSUM Meta.idl = DF870113
// CHECKSUM Mga.idl = 534AEB6A
// CHECKSUM MgaUtil.idl = 39997A64
// CHECKSUM MgaDecorator.idl = E2851BB1
// CHECKSUM Gme.idl = 9D59DDB0
// CHECKSUM Parser.idl = EE6FC409


// if you ever change these version numbers manually:
//	-- increase the major version part by one (the four left digits)
//  -- set the minor part (four right digits) to 0001
//  -- keep them in sync
//  -- never decrease it
cpp_quote("#ifndef INTERFACE_VERSION")
cpp_quote("#define INTERFACE_VERSION 0x000200A3")
cpp_quote("#endif //INTERFACE_VERSION")
#define INTERFACE_VERSION 0x000200A3
