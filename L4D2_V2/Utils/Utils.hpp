#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "../Dma.hpp"
#include "IVEngineClient.hpp"
#include "ClientEntityList.hpp"
#include "CPlayer.hpp"
#include "Client_class.hpp"

enum eModules
{
	MOD_EXE		= 0,
	MOD_SERV	= 1,
	MOD_CLIENT	= 2,
};

constexpr const char* client_name_dll = "client.dll";
constexpr const char* server_name_dll = "server.dll";

namespace interfaces
{
	inline IVEngineClient013* engine_client_interface;
	inline CClientEntityList* client_entity_list_interface;
}

typedef ClientClass* (__thiscall* t_GetClientClass)(CPlayer* this_);
class CUtils
{
	CUtils() = default;
	//~CUtils();
// Init + checks.
public:
	static void Initialise(); // Geting handles, interfaces and e.t.c
	static const HANDLE GetHModule(int8 index); // Just getmodule

//GetAddr func and e.t.c.
public:
	static inline const DWORD GetAddr(DWORD base, std::vector<DWORD> offsets); //Need check this.
	static const DWORD SignScan(std::string signature);

//Memory utils.
public:
	static inline void NOP(DWORD addr, UINT size);
	static inline void SetInt(DWORD addr, int v);
	static inline void SetUint(DWORD addr, UINT v);
	static inline void SetPointer(DWORD addr, void* p);
	static inline void SetFloat(DWORD addr, float v);
	static inline void SetDouble(DWORD addr, double v);

//Valve sdk funcs and e.t.c.
public:
	static void* const GetInterface(const char* interfaceName, const char* moduleName);
	template <int index, typename Type, typename... Arguments>
	static inline Type CallVirtual(void* instance, Arguments... arguments)
	{
		typedef Type(__thiscall* tFunction)(void* instance, Arguments... arguments);
		tFunction func = (*(tFunction**)instance)[index];
		return func(instance, arguments...);
	}
	static inline ClientClass* GetClientClass(CPlayer* entity)
	{
		DWORD* addr = (DWORD*)((char*)entity + 0x8);
		DWORD* vTable = *(DWORD**)(addr);
		DWORD* GetClientClassInTable = (DWORD*)((char*)vTable + 0x4);
		t_GetClientClass GetClientClass = (t_GetClientClass)(*(DWORD**)GetClientClassInTable);
		ClientClass* clientClass = GetClientClass(entity);
		return clientClass;
	}

//important varibles.
private:
	static inline HANDLE hModule_exe;
	static inline HANDLE hModule_server;
	static inline HANDLE hModule_client;
};