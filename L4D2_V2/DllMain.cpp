#include "DllMain.hpp"

static DWORD WINAPI MyThread(HINSTANCE hInstDll)
{
	bool bAllocConsole = AllocConsole();
	FILE* fConsole = nullptr;

	if (bAllocConsole)
		fConsole = freopen("CONOUT$", "w", stdout);

	CUtils::Initialise();

	printf("hModule L4D2.exe     \t -> 0x%p <- \n", CUtils::GetHModule(MOD_EXE));
	printf("hModule Server.dll   \t -> 0x%p <- \n", CUtils::GetHModule(MOD_SERV));
	printf("hModule Client.dll   \t -> 0x%p <- \n", CUtils::GetHModule(MOD_CLIENT));

	printf("VEngineClient013     \t -> 0x%p <- \n", interfaces::engine_client_interface);
	printf("VClientEntityList003 \t -> 0x%p <- \n", interfaces::client_entity_list_interface);
	
	CPlayer* g_player = (CPlayer*)(interfaces::client_entity_list_interface->GetClientEntity(interfaces::engine_client_interface->GetLocalPlayer()));
	printf("LocalPlayer \t \t -> 0x%p <-\n", g_player);

	for (auto i = 0; i < interfaces::client_entity_list_interface->GetHighestEntityIndex(); ++i)
	{
		if (auto entity = (CPlayer*)interfaces::client_entity_list_interface->GetClientEntity(i))
		{
			auto clientClass = CUtils::GetClientClass(entity);
			printf("%s\n", clientClass->m_pNetworkName);
		}
	}

	while (!GetAsyncKeyState(VK_DELETE))
	{


		Sleep(1);
	}

	if (bAllocConsole)
	{
		if (fConsole)
			fclose(fConsole);
		FreeConsole();
	}

	FreeLibraryAndExitThread(hInstDll, 0);

	return 1;
}

static BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		auto thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyThread, hInstDll, 0, 0);
		if (thread)
			CloseHandle(thread);
		break;
	}

	return true;
}