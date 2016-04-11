#pragma once

#include "handle.h"	

class map_view
{
public:
	map_view();
	map_view(handle &&map);
	map_view(const map_view &other) = delete;
	map_view(map_view &&other);
	~map_view();

	map_view &operator =(map_view other);

	friend void swap(map_view &left, map_view &right);

	const char *get_str() const;
	const wchar_t *get_wstr() const;

private:
	const void *_ptr;
	handle _handle;
};

void swap(map_view &left, map_view &right);
