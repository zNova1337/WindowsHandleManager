#pragma once
#include <Windows.h>

template <typename type>
class GenericType
{
public:
	GenericType(type& data) : _data(data) {}
	~GenericType() {}

	GenericType(const GenericType&&) = delete;
	GenericType(GenericType&) = delete;

	const type& get_data()
	{
		return _data;
	}

	void set_data(const type& data)
	{
		_data = data;
	}

	void set_data(type& data)
	{
		_data = data;
	}

	template<typename new_type>
	const new_type& cast_to()
	{
		return *reinterpret_cast<new_type*>(&_data);
	}

	const type* get_data_pointer()
	{
		return reinterpret_cast<type*>(&_data);
	}

	const bool is_valid_handle()
	{
		return ((cast_to<HANDLE>() != INVALID_HANDLE_VALUE) && (cast_to<HANDLE>() != 0));
	}
private:
	type _data;
};