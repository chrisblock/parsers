#include "stdafx.h"

#include "map_view.h"

#include <windows.h>

void swap(map_view &left, map_view &right)
{
	using std::swap;

	swap(left._handle, right._handle);
	swap(left._ptr, right._ptr);
}

map_view::map_view() :
	  _ptr(nullptr)
{
}

map_view::map_view(handle &&map) :
	  _ptr(nullptr)
	, _handle(std::move(map))
{
	_ptr = ::MapViewOfFile(_handle.get(), FILE_MAP_READ, 0, 0, 0);
}

map_view::map_view(map_view &&other) :
	  map_view()
{
	swap(*this, other);
}

map_view::~map_view()
{
	::UnmapViewOfFile(_ptr);
}

map_view &map_view::operator =(map_view other)
{
	swap(*this, other);

	return *this;
}

const char *map_view::get_str() const
{
	auto result = reinterpret_cast<const char *>(_ptr);

	return result;
}

const wchar_t *map_view::get_wstr() const
{
	auto result = reinterpret_cast<const wchar_t *>(_ptr);

	return result;
}
