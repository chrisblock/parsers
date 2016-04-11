#include "stdafx.h"

#include "handle.h"

void swap(handle &left, handle &right)
{
	using std::swap;

	swap(left._handle, right._handle);
}

handle::handle() :
	  _handle(INVALID_HANDLE_VALUE)
{
}

handle::handle(const HANDLE handle) :
	  _handle(handle)
{
}

handle::handle(handle &&other) :
	  handle()
{
	swap(*this, other);
}

handle::~handle()
{
	::CloseHandle(_handle);
}

handle &handle::operator =(handle other)
{
	swap(*this, other);

	return *this;
}

bool handle::is_valid() const
{
	auto result = (_handle != INVALID_HANDLE_VALUE);

	return result;
}

const HANDLE &handle::get() const
{
	return _handle;
}
