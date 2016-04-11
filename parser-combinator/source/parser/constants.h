#pragma once

namespace lexing
{
	class char_constants
	{
	public:
		static const char newline[];
		static const char newline_type[];
		static const char whitespace[];
		static const char whitespace_type[];
	};

	class wchar_constants
	{
	public:
		static const wchar_t newline[];
		static const wchar_t newline_type[];
		static const wchar_t whitespace[];
		static const wchar_t whitespace_type[];
	};

	template <typename TChar>
	class const_expressions
	{
	};

	template <>
	class const_expressions<char> : public char_constants
	{
	};

	template <>
	class const_expressions<wchar_t> : public wchar_constants
	{
	};
}
