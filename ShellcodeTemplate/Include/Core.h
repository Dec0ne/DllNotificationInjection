#include <windows.h>
#include <Macros.h>

UINT_PTR GetRIP( VOID );

NTSTATUS NTAPI TpAllocWork(PTP_WORK* ptpWrk, PTP_WORK_CALLBACK pfnwkCallback, PVOID OptionalArg, PTP_CALLBACK_ENVIRON CallbackEnvironment);
VOID NTAPI TpPostWork(PTP_WORK);
VOID NTAPI TpReleaseWork(PTP_WORK);

typedef struct {

    struct {
        WIN32_FUNC( TpAllocWork );
        WIN32_FUNC( TpPostWork );
        WIN32_FUNC( TpReleaseWork );
        WIN32_FUNC( WaitForSingleObject );
    } Win32; 

    struct {
        // Basics
        HMODULE     Kernel32;
        HMODULE     Ntdll;
    } Modules;

} INSTANCE, *PINSTANCE;