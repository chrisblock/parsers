#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "parser.h"
#include "token.h"

namespace parsing
{
	template <typename TChar>
	class basic_kleene_star_parser : public basic_parser<TChar>
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef ast::basic_node<TChar> node_type;
		typedef lexing::basic_token<TChar> token_type;
		typedef basic_parser<TChar> parser_type;
		typedef basic_parser_result<TChar> result_type;
		typedef std::shared_ptr<parser_type> parser_ptr;

		basic_kleene_star_parser()
		{
		};

		basic_kleene_star_parser(const string_type &name, const parser_ptr &parser) :
			  _name(name)
			, _parser(parser)
		{
		};

		basic_kleene_star_parser(const basic_kleene_star_parser &other) :
			  _name(other._name)
			, _parser(other._parser)
		{
		};

		basic_kleene_star_parser(basic_kleene_star_parser &&other) :
			  basic_kleene_star_parser()
		{
			swap(*this, other);
		};

		virtual ~basic_kleene_star_parser()
		{
		};

		basic_kleene_star_parser &operator =(basic_kleene_star_parser other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_kleene_star_parser &left, basic_kleene_star_parser &right)
		{
			using std::swap;

			swap(left._name, right._name);
			swap(left._parsers, right._parsers);
		};

		virtual result_type parse(const result_type &previous) const override
		{
			result_type result(previous.start(), previous.end());

			if (previous.success())
			{
				node_type ast(_name);

				result_type intermediate = _parser->parse(previous);

				while (intermediate.success())
				{
					ast.add_child(intermediate.ast());

					intermediate = _parser->parse(intermediate);
				}

				result = result_type(ast, intermediate.start(), intermediate.end());
			}
			else
			{
				// TODO: this may be uneccessary
				result = previous;
			}

			return result;
		};

	private:
		string_type _name;
		parser_ptr _parser;
	};

	typedef basic_kleene_star_parser<char> kleene_star_parser;
	typedef basic_kleene_star_parser<wchar_t> wkleene_star_parser;

	template <typename TChar, std::size_t N>
	static std::shared_ptr<basic_parser<TChar>> make_kleene_star_parser(const TChar (&name)[N], const std::shared_ptr<basic_parser<TChar>> &parser)
	{
		return make_kleene_star_parser(std::basic_string<TChar>(name), parser);
	};

	template<typename TChar>
	static std::shared_ptr<basic_parser<TChar>> make_kleene_star_parser(const std::basic_string<TChar> &name, const std::shared_ptr<basic_parser<TChar>> &parser)
	{
		std::shared_ptr<basic_parser<TChar>> result = std::make_shared<basic_kleene_star_parser<TChar>>(name, parser);

		return result;
	};
};
