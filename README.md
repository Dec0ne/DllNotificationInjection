# DllNotificationInjection

![image](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![image](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

## Main Contributors

[![Dec0ne](https://img.shields.io/badge/Dec0ne-FF1B2D?style=for-the-badge&logo=Dec0ne&logoColor=white)](https://github.com/Dec0ne)

## Description

DllNotificationInection is a POC of a new “threadless” process injection technique that works by utilizing the concept of DLL Notification Callbacks in local and remote processes.

An accompanying blog post with more details is available here:

https://shorsec.io/blog/dll-notification-injection/


## How It Works?

DllNotificationInection works by creating a new **LDR_DLL_NOTIFICATION_ENTRY** in the remote process. It inserts it manually into the remote **LdrpDllNotificationList** by patching of the **List.Flink** of the list head and the **List.Blink** of the first entry (now second) of the list.

Our new **LDR_DLL_NOTIFICATION_ENTRY** will point to a custom trampoline shellcode (built with [@C5pider](https://twitter.com/C5pider)'s [ShellcodeTemplate](https://github.com/Cracked5pider/ShellcodeTemplate) project) that will restore our changes and execute a malicious shellcode in a new thread using **TpWorkCallback**.

After manually registering our new entry in the remote process we just need to wait for the remote process to trigger our DLL Notification Callback by loading or unloading some DLL. This obviously doesn't happen in every process regularly so prior work finding suitable candidates for this injection technique is needed. From my brief searching, it seems that **RuntimeBroker.exe** and **explorer.exe** are suitable candidates for this, although I encourage you to find others as well.


## OPSEC Notes

This is a POC. In order for this to be OPSEC safe and evade AV/EDR products, some modifications are needed. For example, I used **RWX** when allocating memory for the shellcodes - don't be lazy (like me) and change those. One also might want to replace **OpenProcess**, **ReadProcessMemory** and **WriteProcessMemory** with some lower level APIs and use **Indirect Syscalls** or (shameless plug) **HWSyscalls**. Maybe encrypt the shellcodes or even go the extra mile and modify the trampoline shellcode to suit your needs, or at least change the default hash values in [@C5pider](https://twitter.com/C5pider)'s [ShellcodeTemplate](https://github.com/Cracked5pider/ShellcodeTemplate) project which was utilized to create the trampoline shellcode.

## Demo



https://github.com/ShorSec/DllNotificationInjection/assets/54464773/96a72dd9-80de-4cb8-ac4a-54dddfecf822



## Acknowledgments

- [@C5pider](https://twitter.com/C5pider) for his [ShellcodeTemplate](https://github.com/Cracked5pider/ShellcodeTemplate) project which which was used to create the trampoline shellcode. Also, for [Havoc C2](https://github.com/HavocFramework/Havoc) that was used in the POC Demo Video.
- [Yxel](https://github.com/janoglezcampos) and [@Idov31](https://twitter.com/Idov31) for the binary pattern matching code we used from [Cronos](https://github.com/Idov31/Cronos/blob/master/src/Utils.c).
- [@modexpblog](https://twitter.com/modexpblog) for the [various structures definitions](https://modexp.wordpress.com/2020/08/06/windows-data-structures-and-callbacks-part-1/#dll) related to DLL Notification Callbacks which were used in this POC.
- [@NinjaParanoid](https://twitter.com/NinjaParanoid) for his [blog post](https://0xdarkvortex.dev/proxying-dll-loads-for-hiding-etwti-stack-tracing/) on TpWorkCallbacks which were used in this POC.
- [@onlymalware](https://twitter.com/onlymalware) for his [UnregisterAllLdrRegisterDllNotification POC](https://github.com/rad9800/misc/blob/main/bypasses/UnregisterAllLdrRegisterDllNotification.c), it gave me some inspiration and helped me understand some of the inner workings of the LdrpDllNotificationList.
- [Sektor7](https://institute.sektor7.net/) for the calc shellcode used in this POC. They are awesome regardless and I highly recommend their courses!
- [@x86matthew](https://twitter.com/x86matthew) and [@Kharosx0](https://twitter.com/Kharosx0) for their comments ([1](https://twitter.com/x86matthew/status/1691245975455608832?s=20), [2](https://twitter.com/Kharosx0/status/1691313315203764224?s=20)) regarding the GetNtdllBase() function.
