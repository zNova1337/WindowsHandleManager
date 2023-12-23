#include "HandleManager.hpp"
#include "CodeTracer.hpp"

HandleManager::FileHandle::FileHandle()
{
}

HandleManager::FileHandle::FileHandle(const HANDLE& handle) : _file_handle(handle)
{
}

HandleManager::FileHandle::~FileHandle()
{
	try
	{
		const BOOL result = FindClose(_file_handle);
		ASSERT(result);
	}
	catch (...)
	{
		log_function();
	}
}

const bool HandleManager::FileHandle::is_handle_valid()
{
	return (_file_handle != INVALID_HANDLE_VALUE) && (_file_handle != 0);
}

void HandleManager::FileHandle::set_handle(const HANDLE& handle)
{
	_file_handle = handle;
}

void HandleManager::FileHandle::set_handle(HANDLE& handle)
{
	_file_handle = handle;
}

const HANDLE HandleManager::FileHandle::get_handle()
{
	return _file_handle;
}
