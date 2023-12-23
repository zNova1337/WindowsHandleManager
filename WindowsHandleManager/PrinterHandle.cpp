#include "HandleManager.hpp"
#include "CodeTracer.hpp"

HandleManager::PrinterHandle::PrinterHandle()
{
}

HandleManager::PrinterHandle::PrinterHandle(const HANDLE& handle) : _printer_handle(handle)
{
}

HandleManager::PrinterHandle::~PrinterHandle()
{
	try
	{
		if (is_printer_handle_valid())
		{
			const BOOL result = ClosePrinter(_printer_handle);
			ASSERT(result);
		}
	}
	catch (...)
	{
		log_function();
	}
}

void HandleManager::PrinterHandle::set_printer_handle(const HANDLE& printer_handle)
{
	_printer_handle = printer_handle;
}

const HANDLE HandleManager::PrinterHandle::get_printer_handle()
{
	return _printer_handle;
}

const bool HandleManager::PrinterHandle::is_printer_handle_valid()
{
	return (_printer_handle != INVALID_HANDLE_VALUE) && (_printer_handle != 0);
}

const bool HandleManager::PrinterHandle::is_spool_file_handle_valid()
{
	return (_spool_file_handle != INVALID_HANDLE_VALUE) && (_spool_file_handle != 0);
}