#pragma once

#include "parser_result.h"

namespace parsing
{
	template <typename TChar>
	class basic_parser
	{
	public:
		typedef parsing::basic_parser_result<TChar> result_type;

		virtual ~basic_parser()
		{
		};

		virtual result_type parse(const result_type &previous) const = 0;
	};

	typedef basic_parser<char> parser;
	typedef basic_parser<wchar_t> wparser;
};
