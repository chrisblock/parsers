#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "builder.h"
#include "parser.h"
#include "token.h"

namespace parsing
{
	template <typename TChar>
	class basic_sequence_parser : public basic_parser<TChar>
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef ast::basic_node<TChar> node_type;
		typedef lexing::basic_token<TChar> token_type;
		typedef basic_parser<TChar> parser_type;
		typedef basic_parser_result<TChar> result_type;
		typedef std::shared_ptr<parser_type> parser_ptr;

		basic_sequence_parser()
		{
		};

		basic_sequence_parser(const string_type &name, const std::vector<parser_ptr> &parsers) :
			  _name(name)
			, _parsers(parsers)
		{
		};

		basic_sequence_parser(const basic_sequence_parser &other) :
			  _name(other._name)
			, _parsers(other._parsers)
		{
		};

		basic_sequence_parser(basic_sequence_parser &&other) :
			  basic_sequence_parser()
		{
			swap(*this, other);
		};

		virtual ~basic_sequence_parser()
		{
		};

		basic_sequence_parser &operator =(basic_sequence_parser other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_sequence_parser &left, basic_sequence_parser &right)
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
				std::vector<node_type> children;

				children.reserve(_parsers.size());

				result_type intermediate = previous;

				for (const parser_ptr &parser : _parsers)
				{
					result_type what = parser->parse(intermediate);

					if (what.success())
					{
						children.push_back(what.ast());

						intermediate = what;
					}
					else
					{
						break;
					}
				}

				if (children.size() == _parsers.size())
				{
					node_type ast(_name, children, previous.start(), intermediate.start());

					result = result_type(ast, intermediate.start(), intermediate.end());
				}
				else
				{
					string_type error = errors::basic_builder<TChar>::unrecognized_token(*(intermediate.start()));

					result = result_type(error, intermediate.start(), intermediate.end());
				}
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
		std::vector<parser_ptr> _parsers;
	};

	typedef basic_sequence_parser<char> sequence_parser;
	typedef basic_sequence_parser<wchar_t> wsequence_parser;

	template <typename TChar, std::size_t N, typename... TParsers>
	static std::shared_ptr<basic_parser<TChar>> make_sequence_parser(const TChar (&name)[N], const TParsers... parsers)
	{
		return make_sequence_parser(std::basic_string<TChar>(name), parsers...);
	};

	template<typename TChar, typename... TParsers>
	static std::shared_ptr<basic_parser<TChar>> make_sequence_parser(const std::basic_string<TChar> &name, const TParsers... parsers)
	{
		// TODO: not sure how this syntax works
		//static_assert(std::is_base_of<basic_parser<TChar>, TParsers>::value, "Oh no");

		std::vector<std::shared_ptr<basic_parser<TChar>>> p = { parsers... };

		std::shared_ptr<basic_parser<TChar>> result = std::make_shared<basic_sequence_parser<TChar>>(name, p);

		return result;
	};
};
