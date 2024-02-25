#include "Client_class.hpp"
#include "Utils.hpp"

ClientClass* BaseClientDLL::GetAllClasses(void)
{
	return CUtils::CallVirtual<5, ClientClass*>(this);
}
