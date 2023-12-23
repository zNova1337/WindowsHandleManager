#include "HandleManager.hpp"

void HandleManager::log_function()
{
#ifdef ENABLE_LOG
	char buffer[4096];
	sprintf_s(buffer, "Last Error Code: %d", GetLastError());
	MessageBoxA(0, buffer, 0, 0);
#endif
}