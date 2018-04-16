// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBRARYASM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBRARYASM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBRARYASM_EXPORTS
#define LIBRARYASM_API __declspec(dllexport)
#else
#define LIBRARYASM_API __declspec(dllimport)
#endif
//
//// This class is exported from the LibraryAsm.dll
//class LIBRARYASM_API CLibraryAsm {
//public:
//	CLibraryAsm(void);
//	// TODO: add your methods here.
//};
//
//extern LIBRARYASM_API int nLibraryAsm;
//
//LIBRARYASM_API int fnLibraryAsm(void);
