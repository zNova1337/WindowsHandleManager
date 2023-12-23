#include "HandleManager.hpp"
#include "CodeTracer.hpp"

HandleManager::DefaultHandle::DefaultHandle()
{
}

HandleManager::DefaultHandle::DefaultHandle(const HANDLE& handle) : _m_handle(handle)
{
}

HandleManager::DefaultHandle::~DefaultHandle()
{
	try
	{
		const BOOL result = CloseHandle(_m_handle);
		ASSERT(result);
	}
	catch (...)
	{
		log_function();
	}
}

const bool HandleManager::DefaultHandle::is_handle_valid()
{
	return (_m_handle != INVALID_HANDLE_VALUE) && (_m_handle != 0);
}

void HandleManager::DefaultHandle::set_handle(const HANDLE& handle)
{
	_m_handle = handle;
}

void HandleManager::DefaultHandle::set_handle(HANDLE& handle)
{
	_m_handle = handle;
}

const HANDLE HandleManager::DefaultHandle::get_handle()
{
	return _m_handle;
}
