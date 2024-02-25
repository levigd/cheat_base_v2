#include "IVEngineClient.hpp"
#include "Utils.hpp"

int IVEngineClient013::GetLocalPlayer(void)
{
	return CUtils::CallVirtual<12, int>(this);
}
