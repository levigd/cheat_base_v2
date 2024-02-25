#include "ClientEntityList.hpp"
#include "Utils.hpp"

int* CClientEntityList::GetClientEntity(int entnum)
{
	return CUtils::CallVirtual<3, int*, int>(this, entnum);
}

IClientEntity* CClientEntityList::GetClientEntityFromHandle(int hEnt)
{
	return CUtils::CallVirtual<7, IClientEntity*, int>(this, hEnt);
}

int CClientEntityList::GetHighestEntityIndex(void)
{
	return CUtils::CallVirtual<8, int>(this);
}