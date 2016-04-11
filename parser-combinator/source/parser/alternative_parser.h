#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "parser.h"
#include "token.h"

namespace parsing
{
	template <typename TChar>
	class basic_alternative_parser : public basic_parser<TChar>
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef ast::basic_node<TChar> node_type;
		typedef lexing::basic_token<TChar> token_type;
		typedef basic_parser<TChar> parser_type;
		typedef basic_parser_result<TChar> result_type;
		typedef std::shared_ptr<parser_type> parser_ptr;

		basic_alternative_parser()
		{
		};

		basic_alternative_parser(const string_type &name, const std::vector<parser_ptr> &parsers) :
			  _name(name)
			, _parsers(parsers)
		{
		};

		basic_alternative_parser(const basic_alternative_parser &other) :
			  _name(other._name)
			, _parsers(other._parsers)
		{
		};

		basic_alternative_parser(basic_alternative_parser &&other) :
			  basic_alternative_parser()
		{
			swap(*this, other);
		};

		virtual ~basic_alternative_parser()
		{
		};

		basic_alternative_parser &operator =(basic_alternative_parser other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_alternative_parser &left, basic_alternative_parser &right)
		{
			using std::swap;

			swap(left._name, right._name);
			swap(left._parsers, right._parsers);
		};

		virtual result_type parse(const result_type &previous) const override
		{
			result_type result(previous.start(), previous.end());

			for (const parser_ptr &parser : _parsers)
			{
				result_type intermediate = parser->parse(previous);

				if (intermediate.success())
				{
					result = intermediate;

					break;
				}
			}

			return result;
		};

	private:
		string_type _name;
		std::vector<parser_ptr> _parsers;
	};

	typedef basic_alternative_parser<char> alternative_parser;
	typedef basic_alternative_parser<wchar_t> walternative_parser;

	template <typename TChar, std::size_t N, typename... TParsers>
	static std::shared_ptr<basic_parser<TChar>> make_alternative_parser(const TChar(&name)[N], const TParsers... parsers)
	{
		return make_alternative_parser(std::basic_string<TChar>(name), parsers...);
	};

	template<typename TChar, typename... TParsers>
	static std::shared_ptr<basic_parser<TChar>> make_alternative_parser(const std::basic_string<TChar> &name, const TParsers... parsers)
	{
		std::vector<std::shared_ptr<basic_parser<TChar>>> p = { parsers... };

		return std::make_shared<basic_alternative_parser<TChar>>(name, p);
	};
};
