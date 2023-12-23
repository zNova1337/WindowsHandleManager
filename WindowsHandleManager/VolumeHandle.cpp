#include "HandleManager.hpp"
#include "CodeTracer.hpp"

HandleManager::VolumeHandle::VolumeHandle()
{
}

HandleManager::VolumeHandle::VolumeHandle(const HANDLE& handle) : _volume_handle(handle)
{
}

HandleManager::VolumeHandle::~VolumeHandle()
{
	try
	{
		const BOOL result = FindVolumeClose(_volume_handle);
		ASSERT(result);
	}
	catch (...)
	{
		log_function();
	}
}

const bool HandleManager::VolumeHandle::is_handle_valid()
{
	return (_volume_handle != INVALID_HANDLE_VALUE) && (_volume_handle != 0);
}

void HandleManager::VolumeHandle::set_handle(const HANDLE& handle)
{
	_volume_handle = handle;
}

void HandleManager::VolumeHandle::set_handle(HANDLE& handle)
{
	_volume_handle = handle;
}

const HANDLE HandleManager::VolumeHandle::get_handle()
{
	return _volume_handle;
}
