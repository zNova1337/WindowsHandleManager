#include "HandleManager.hpp"

#include <memory>
#include <iostream>

constexpr PVOID TIMER_NO_PARAMETER = nullptr;

void WINAPI TimerCallback(PVOID context, BOOLEAN first)
{
	MessageBoxA(0, "HELLO", 0, 0);
	auto timer_mgr = *reinterpret_cast<HandleManager::TimerHandle**>(context);
	SetEvent(timer_mgr->get_event_handle());
}

DWORD get_process_id_by_name(const wchar_t* proc_name)
{
	DWORD pid = 0;
	const auto process_snapshot = std::make_unique<HandleManager::DefaultHandle>(CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0));
	if (!process_snapshot->is_handle_valid())
	{
		std::cout << "Fail to Createsnapshot of process" << std::endl;
		return 0;
	}

	PROCESSENTRY32W pe32{};
	pe32.dwSize = sizeof(PROCESSENTRY32W);
	const BOOL pe32_first = Process32FirstW(process_snapshot->get_handle(), &pe32);
	if (!pe32_first)
	{
		std::cout << "Process32First failed with error code: " << GetLastError() << std::endl;
		return 0;
	}


	do
	{
		if (!wcscmp(pe32.szExeFile, proc_name))
		{
			pid = pe32.th32ProcessID;
			break;
		}

	} while (Process32NextW(process_snapshot->get_handle(), &pe32));

	return pid;
}

void process_handle_example(const wchar_t* proc_name)
{
	auto pid = get_process_id_by_name(proc_name);
	if (!pid)
	{
		std::wcout << L"Failed to get_pid of process (" << proc_name << L")\n";
		return;
	}

	std::wcout << L"Process: " << proc_name << std::endl;
	std::cout << "PID: " << pid << std::hex << "(" << pid << ")" << std::endl;
	auto process_handle = std::make_unique<HandleManager::DefaultHandle>(OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid));
	if (!process_handle->is_handle_valid())
		return;

	std::cout << "HANDLE: " << process_handle->get_handle() << std::hex << "(" << process_handle->get_handle() << ")" << std::endl;
}

void timer_handle_example()
{
	auto timer_handle = std::make_unique<HandleManager::TimerHandle>(CreateTimerQueue());
	if (!timer_handle->is_timer_handle_valid())
	{
		MessageBoxA(0, "INVALID TIMER HANDLE", 0, 0);
		return;
	}

	timer_handle->set_event_handle(CreateEventW(NULL, TRUE, FALSE, NULL));
	if (!timer_handle->is_event_handle_valid())
	{
		MessageBoxA(0, "INVALID EVENT HANDLE", 0, 0);
		return;
	}

	if (!CreateTimerQueueTimer(const_cast<HANDLE*>(timer_handle->get_new_timer_handle_ptr()), timer_handle->get_timer_handle(), TimerCallback, &timer_handle, 5000, NULL, 0))
		MessageBoxA(0, "Failed", 0, 0);

	if (WaitForSingleObject(timer_handle->get_event_handle(), INFINITE) != WAIT_OBJECT_0)
	{
		std::cout << "WaitForSingleObject failed" << std::endl;
	}
}

void file_handle_example()
{
	WIN32_FIND_DATAW file_data;
	auto file_handle = std::make_unique<HandleManager::FileHandle>(FindFirstFileW(L"C:\\*", &file_data));
	if (!file_handle->is_handle_valid())
	{
		std::cout << "FindFirstFileW failed with error code: " << GetLastError() << std::endl;
		return;
	}
	std::cout << "Target path: C:\\" << std::endl;
	do
	{
		std::wcout << L"File name: " << file_data.cFileName << std::endl;
	} while (FindNextFileW(file_handle->get_handle(), &file_data));
}

void printer_handle_example(const LPWSTR printer_name, const LPWSTR port_name, const LPWSTR driver_name, const LPWSTR location, const LPWSTR print_processor = const_cast<const LPWSTR>(L"winprint"))
{
	PRINTER_INFO_2W printer_info{};

	printer_info.pPrinterName = printer_name;
	printer_info.pPortName = port_name;
	printer_info.pDriverName = driver_name;
	printer_info.pPrintProcessor = print_processor;
	printer_info.pLocation = location;
	printer_info.Attributes = PRINTER_ATTRIBUTE_NETWORK | PRINTER_ATTRIBUTE_LOCAL;

	auto printer_handle = std::make_unique<HandleManager::PrinterHandle>(AddPrinterW(NULL, 2, reinterpret_cast<LPBYTE>(&printer_info)));
	if (!printer_handle->is_printer_handle_valid())
	{
		std::cout << "AddPrinterW failed with error code: " << GetLastError() << std::endl;
		return;
	}

	//do the rest here
}

int main(void)
{
	process_handle_example(L"The_Conjuring_House-Win64-Shipping.exe");

	timer_handle_example();

	file_handle_example();
	return EXIT_SUCCESS;
}