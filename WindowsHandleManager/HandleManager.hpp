#pragma once
#include "GenericType.hpp"

#include <TlHelp32.h>

namespace HandleManager
{
	void log_function();

	class DefaultHandle final
	{
	public:
		explicit DefaultHandle();
		explicit DefaultHandle(const HANDLE&);
		~DefaultHandle();

		DefaultHandle(const DefaultHandle&&) = delete;
		DefaultHandle(DefaultHandle&) = delete;
		
		const bool is_handle_valid();

		void set_handle(const HANDLE&);
		void set_handle(HANDLE&);
		const HANDLE get_handle();
	private:
		HANDLE _m_handle = INVALID_HANDLE_VALUE;
	};

	class FileHandle final
	{
	public:
		explicit FileHandle();
		explicit FileHandle(const HANDLE&);
		~FileHandle();
		
		FileHandle(const FileHandle&&) = delete;
		FileHandle(FileHandle&) = delete;

		const bool is_handle_valid();

		void set_handle(const HANDLE&);
		void set_handle(HANDLE&);
		const HANDLE get_handle();
	private:
		HANDLE _file_handle = INVALID_HANDLE_VALUE;
	};

	class VolumeHandle final
	{
	public:
		explicit VolumeHandle();
		explicit VolumeHandle(const HANDLE&);
		~VolumeHandle();

		VolumeHandle(const VolumeHandle&&) = delete;
		VolumeHandle(VolumeHandle&) = delete;

		const bool is_handle_valid();

		void set_handle(const HANDLE&);
		void set_handle(HANDLE&);
		const HANDLE get_handle();
	private:
		HANDLE _volume_handle;
	};

	class TimerHandle final
	{
	public:
		explicit TimerHandle();
		explicit TimerHandle(const HANDLE);
		~TimerHandle();

		TimerHandle(const TimerHandle&&) = delete;
		TimerHandle(TimerHandle&) = delete;

		void set_event_handle(const HANDLE&);
		void set_timer_handle(const HANDLE&);
		void set_new_timer_handle(const HANDLE&);

		void set_event_handle(HANDLE&);
		void set_timer_handle(HANDLE&);
		void set_new_timer_handle(HANDLE&);

		const HANDLE* get_new_timer_handle_ptr();
		const HANDLE* get_timer_handle_ptr();
		const HANDLE* get_event_handle_ptr();
		
		const HANDLE get_timer_handle();
		const HANDLE get_new_timer_handle();
		const HANDLE get_event_handle();
		
		const bool is_timer_handle_valid();
		const bool is_new_timer_handle_valid();
		const bool is_event_handle_valid();
	private:
		HANDLE _timer_handle = INVALID_HANDLE_VALUE;
		HANDLE _new_timer_handle = INVALID_HANDLE_VALUE;
		HANDLE _event_handle = INVALID_HANDLE_VALUE;
	};

	class PrinterHandle final
	{
	public:
		explicit PrinterHandle();
		explicit PrinterHandle(const HANDLE&);
		~PrinterHandle();

		PrinterHandle(const PrinterHandle&&) = delete;
		PrinterHandle(PrinterHandle&) = delete;

		void set_printer_handle(const HANDLE&);
		const HANDLE get_printer_handle();

		const bool is_printer_handle_valid();
		const bool is_spool_file_handle_valid();
	private:
		HANDLE _printer_handle;
		HANDLE _spool_file_handle;
	};
}


