#pragma once

#include "parser.h"

namespace parsing
{
	template <typename TChar>
	class basic_terminal_symbol_parser : public basic_parser<TChar>
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef ast::basic_node<TChar> node_type;
		typedef lexing::basic_token<TChar> token_type;
		typedef basic_parser_result<TChar> result_type;

		basic_terminal_symbol_parser()
		{
		};

		basic_terminal_symbol_parser(const string_type &symbol) :
			  _symbol(symbol)
		{
		};

		basic_terminal_symbol_parser(const basic_terminal_symbol_parser &other) :
			  _symbol(other._symbol)
		{
		};

		basic_terminal_symbol_parser(basic_terminal_symbol_parser &&other) :
			  basic_terminal_symbol_parser()
		{
			swap(*this, other);
		};

		virtual ~basic_terminal_symbol_parser()
		{
		};

		basic_terminal_symbol_parser &operator =(basic_terminal_symbol_parser other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_terminal_symbol_parser &left, basic_terminal_symbol_parser &right)
		{
			using std::swap;

			swap(left._symbol, right._symbol);
		};

		virtual result_type parse(const result_type &previous) const override
		{
			result_type result(previous.start(), previous.end());

			if (previous.success())
			{
				auto token = previous.start();

				if ((token != previous.end()) && (token->get_type() == _symbol))
				{
					node_type ast(_symbol, token, ++token);

					result = result_type(ast, token, previous.end());
				}
			}

			return result;
		};

	private:
		string_type _symbol;
	};

	typedef basic_terminal_symbol_parser<char> terminal_symbol_parser;
	typedef basic_terminal_symbol_parser<wchar_t> wterminal_symbol_parser;

	template <typename TChar, std::size_t N>
	std::shared_ptr<basic_parser<TChar>> make_terminal_parser(const TChar (&symbol)[N])
	{
		return make_terminal_parser(std::basic_string<TChar>(symbol));
	};

	template <typename TChar>
	std::shared_ptr<basic_parser<TChar>> make_terminal_parser(const std::basic_string<TChar> &symbol)
	{
		std::shared_ptr<basic_parser<TChar>> result = std::make_shared<basic_terminal_symbol_parser<TChar>>(symbol);

		return result;
	};
};
