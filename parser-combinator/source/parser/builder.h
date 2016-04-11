#pragma once

#include <string>
#include <sstream>

#include "token.h"

namespace errors
{
	template <typename TChar>
	class basic_builder
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef lexing::basic_token<TChar> token_type;

		basic_builder() = delete;
		basic_builder(const basic_builder &other) = delete;
		basic_builder(basic_builder &&other) = delete;
		~basic_builder() = delete;

		basic_builder &operator =(basic_builder other) = delete;

		static string_type expected_token(const string_type &token_type)
		{
			std::basic_stringstream<TChar> stream;

			stream << "Expected token of type '" << token_type << "'.";

			return stream.str();
		};

		static string_type unrecognized_token(const token_type &token)
		{
			std::basic_stringstream<TChar> stream;

			stream << "Unrecognized token '" << token.get_text() << "' at line " << token.get_line() << ", position " << token.get_position() << ".";

			return stream.str();
		};
	};

	typedef basic_builder<char> builder;
	typedef basic_builder<wchar_t> wbuilder;
}
