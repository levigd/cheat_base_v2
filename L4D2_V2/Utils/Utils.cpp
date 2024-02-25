#include "Utils.hpp"

void CUtils::Initialise()
{
	hModule_exe		= GetModuleHandleA(NULL);
	hModule_client	= GetModuleHandleA(client_name_dll);
	hModule_server  = GetModuleHandleA(server_name_dll);

	interfaces::engine_client_interface		 = reinterpret_cast<IVEngineClient013*>(GetInterface("VEngineClient013",	 "engine.dll"));
	interfaces::client_entity_list_interface = reinterpret_cast<CClientEntityList*>(GetInterface("VClientEntityList003", "client.dll")); 
}

const HANDLE CUtils::GetHModule(int8 index)
{
	switch (index)
	{
	case MOD_EXE:
		return hModule_exe;
		break;
	case MOD_CLIENT:
		return hModule_client;
		break;
	case MOD_SERV:
		return hModule_server;
		break;
	}
}

const DWORD CUtils::GetAddr(DWORD baseAddr, std::vector<DWORD> offsets)
{
	DWORD result = baseAddr;

	for (auto i = 0; i < offsets.size(); ++i)
	{
		//ReadProcessMemory(GetCurrentProcess(), (LPCVOID)result, &result, sizeof(result), 0);
		result = *(DWORD*)(result);
		result += offsets[i];
	}

	return result;
}

void CUtils::NOP(DWORD addr, UINT size)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset((void*)addr, 0x90, size);
	VirtualProtect((LPVOID)addr, size, oldProtect, &oldProtect);
}

void CUtils::SetInt(DWORD addr, int v)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(int*)addr = v;
	VirtualProtect((LPVOID)addr, 4, oldProtect, &oldProtect);
}

void CUtils::SetUint(DWORD addr, UINT v)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(UINT*)addr = v;
	VirtualProtect((LPVOID)addr, 4, oldProtect, &oldProtect);
}

void CUtils::SetPointer(DWORD addr, void* p)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	addr = (DWORD)p;
	VirtualProtect((LPVOID)addr, 4, oldProtect, &oldProtect);
}

void CUtils::SetFloat(DWORD addr, float v)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(float*)addr = v;
	VirtualProtect((LPVOID)addr, 4, oldProtect, &oldProtect);
}

void CUtils::SetDouble(DWORD addr, double v)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)addr, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(double*)addr = v;
	VirtualProtect((LPVOID)addr, 8, oldProtect, &oldProtect);
}

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
void* const CUtils::GetInterface(const char* interfaceName, const char* moduleName)
{
	HMODULE hHandle = GetModuleHandleA(moduleName);

	if (hHandle)
	{
		FARPROC funcAddr = GetProcAddress(hHandle, "CreateInterface");

		if (funcAddr)
		{
			CreateInterfaceFn createInterface = (CreateInterfaceFn)funcAddr;
			return createInterface(interfaceName, 0);
		}

		else
			printf("Func addr error\n");
	}

	else
		printf("Not valid moduleName\n");
}


