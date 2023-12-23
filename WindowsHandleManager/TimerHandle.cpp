#include "HandleManager.hpp"
#include "CodeTracer.hpp"

HandleManager::TimerHandle::TimerHandle()
{
}

HandleManager::TimerHandle::TimerHandle(const HANDLE handle) : _timer_handle(handle)
{
}

HandleManager::TimerHandle::~TimerHandle()
{
	try
	{
		if (is_event_handle_valid())
		{
			const BOOL event_close_result = CloseHandle(_event_handle);
			ASSERT(event_close_result);
		}

		if (is_new_timer_handle_valid() && is_timer_handle_valid())
		{
			const BOOL delete_result = DeleteTimerQueueTimer(_timer_handle, _new_timer_handle, _event_handle);
			ASSERT(delete_result);
		}

		if (is_timer_handle_valid())
		{
			const BOOL timer_delete_result = DeleteTimerQueue(_timer_handle);
			ASSERT(timer_delete_result);
		}
	}
	catch (...)
	{
		log_function();
	}
}

const HANDLE HandleManager::TimerHandle::get_new_timer_handle()
{
	return _new_timer_handle;
}

const HANDLE HandleManager::TimerHandle::get_event_handle()
{
	return _event_handle;
}

const bool HandleManager::TimerHandle::is_timer_handle_valid()
{
	return (_timer_handle != INVALID_HANDLE_VALUE) && (_timer_handle != 0);
}

const bool HandleManager::TimerHandle::is_new_timer_handle_valid()
{
	return (_new_timer_handle!= INVALID_HANDLE_VALUE) && (_new_timer_handle != 0);
}

const bool HandleManager::TimerHandle::is_event_handle_valid()
{
	return (_event_handle != INVALID_HANDLE_VALUE) && (_event_handle != 0);
}

const HANDLE HandleManager::TimerHandle::get_timer_handle()
{
	return _timer_handle;
}

const HANDLE* HandleManager::TimerHandle::get_new_timer_handle_ptr()
{
	return GenericType <HANDLE>(_new_timer_handle).get_data_pointer();
}

const HANDLE* HandleManager::TimerHandle::get_timer_handle_ptr()
{
	return GenericType <HANDLE>(_timer_handle).get_data_pointer();
}

const HANDLE* HandleManager::TimerHandle::get_event_handle_ptr()
{
	return GenericType <HANDLE>(_event_handle).get_data_pointer();
}

void HandleManager::TimerHandle::set_event_handle(const HANDLE& event_handle)
{
	_event_handle = event_handle;
}

void HandleManager::TimerHandle::set_timer_handle(const HANDLE& timer_handle)
{
	_timer_handle = timer_handle;
}

void HandleManager::TimerHandle::set_new_timer_handle(const HANDLE& new_timer_handle)
{
	_new_timer_handle = new_timer_handle;
}

void HandleManager::TimerHandle::set_event_handle(HANDLE& event_handle)
{
	_event_handle = event_handle;
}

void HandleManager::TimerHandle::set_timer_handle(HANDLE& timer_handle)
{
	_timer_handle = timer_handle;
}

void HandleManager::TimerHandle::set_new_timer_handle(HANDLE& new_timer_handle)
{
	_new_timer_handle = new_timer_handle;
}


