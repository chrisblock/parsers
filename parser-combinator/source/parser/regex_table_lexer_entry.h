#pragma once

#include <regex>

#include "token.h"

namespace lexing
{
	template <typename TChar, typename TTraits = std::regex_traits<TChar>>
	class basic_regex_table_lexer_entry
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef typename string_type::const_iterator string_const_iterator;
		typedef std::basic_regex<TChar, TTraits> regex_type;
		typedef basic_token<TChar> token_type;

		basic_regex_table_lexer_entry()
		{
		};

		basic_regex_table_lexer_entry(const string_type &expression, const string_type &type) :
			  basic_regex_table_lexer_entry(expression, std::regex_constants::ECMAScript, type)
		{
		};

		basic_regex_table_lexer_entry(const string_type &expression, const std::regex_constants::syntax_option_type flags, const string_type &type) :
			  _expression(expression, flags)
			, _type(type)
		{
		};

		basic_regex_table_lexer_entry(const basic_regex_table_lexer_entry &other) :
			  _expression(other._expression)
			, _type(other._type)
		{
		};

		basic_regex_table_lexer_entry(basic_regex_table_lexer_entry &&other)
		{
			swap(*this, other);
		};

		virtual ~basic_regex_table_lexer_entry()
		{
		};

		basic_regex_table_lexer_entry &operator =(basic_regex_table_lexer_entry other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_regex_table_lexer_entry &left, basic_regex_table_lexer_entry &right)
		{
			using std::swap;

			swap(left._expression, right._expression);
			swap(left._type, right._type);
		};

		void set_expression(const string_type &expression)
		{
			set_expression(expression, std::regex_constants::ECMAScript);
		};

		void set_expression(const string_type &expression, const std::regex_constants::syntax_option_type flags)
		{
			_expression = regex_type(expression, flags);
		};

		void set_expression(const regex_type &expression)
		{
			_expression = expression;
		};

		const regex_type &get_expression() const
		{
			return _expression;
		};

		void set_type(const string_type &type)
		{
			_type = type;
		};

		const string_type &get_type() const
		{
			return _type;
		};

		bool is_match(const string_type &str) const
		{
			bool result = std::regex_search(str, _expression, std::regex_constants::match_default | std::regex_constants::match_continuous);

			return result;
		};

		bool consume(const string_const_iterator &start, const string_const_iterator &end, token_type &token) const
		{
			bool result = false;

			std::match_results<string_const_iterator> results;

			if (std::regex_search(start, end, results, _expression, std::regex_constants::match_default | std::regex_constants::match_continuous))
			{
				token = token_type(results.str(), _type);

				result = true;
			}

			return result;
		};

		bool consume(const TChar *str, token_type &token) const
		{
			bool result = false;

			std::match_results<const TChar *> results;

			if (std::regex_search(str, results, _expression, std::regex_constants::match_default | std::regex_constants::match_continuous))
			{
				token = token_type(results.str(), _type);

				result = true;
			}

			return result;
		};

	private:
		string_type _type;
		regex_type _expression;
	};

	typedef basic_regex_table_lexer_entry<char> regex_table_lexer_entry;
	typedef basic_regex_table_lexer_entry<wchar_t> wregex_table_lexer_entry;
};
