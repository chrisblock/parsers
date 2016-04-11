#include "stdafx.h"

#include <conio.h>

std::int32_t _tmain(std::int32_t argc, TCHAR *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::GTEST_FLAG(shuffle) = true;

	RUN_ALL_TESTS();

#if _DEBUG
	if (::_isatty(::_fileno(stdin)))
	{
		::_tprintf_s(_T("Please press any key to continue."));

		int result = ::_gettch();

		result;
	}
#endif

	return EXIT_SUCCESS;
}
