#pragma once

#include <windows.h>

class handle
{
public:
	handle();
	handle(const HANDLE handle);
	handle(const handle &other) = delete;
	handle(handle &&other);
	virtual ~handle();

	handle &operator =(handle other);

	friend void swap(handle &left, handle &right);

	bool is_valid() const;

	const HANDLE &get() const;

private:
	HANDLE _handle;
};

void swap(handle &left, handle &right);
