#include <Windows.h>
#include <stdio.h>
#include "inpout32.h"

// Base address of the relocated parallel port.
short int RelocatedAddress = (short)0x378;

// Initialisation callback.
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	FILE* fp = NULL;
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			if (fopen_s(&fp, "io.ini", "r") == 0) {
				fscanf_s(fp, "%hi", &RelocatedAddress);
				fclose(fp);
			}
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}


// Modifies port accesses in the legacy LPT1 parallel port range (0x378..0x37F).
short int FixPortAddress(short int portAddress) {
	if (portAddress >= 0x378 && portAddress <= 0x37F) {
		return portAddress - 0x378 + RelocatedAddress;
	} else {
		return portAddress;
	}
}

// Reimplimented versions of the functions in io.dll modified to use the address-fixing function above.
extern "C" __declspec(dllexport) void PortOut(short int Port, char Data) {
	Out32(FixPortAddress(Port), Data);
}
extern "C" __declspec(dllexport) char PortIn(short int Port) {
	return (char)Inp32(FixPortAddress(Port));
}
extern "C" __declspec(dllexport) short int IsDriverInstalled() {
	return -1;
}