#pragma once

#include <queue>
#include <string>

#include "node.h"
#include "token.h"

namespace parsing
{
	template <typename TChar>
	class basic_parser_result
	{
	public:
		typedef ast::basic_node<TChar> node_type;
		typedef std::basic_string<TChar> string_type;
		typedef lexing::basic_token<TChar> token_type;
		typedef typename std::vector<token_type>::const_iterator iter_type;

		basic_parser_result() :
			  _success(false)
		{
		};

		basic_parser_result(const iter_type &start, const iter_type &end) :
			  _success(false)
			, _start(start)
			, _end(end)
		{
		};

		basic_parser_result(const string_type &error, const iter_type &start, const iter_type &end) :
			  _success(false)
			, _error(error)
			, _start(start)
			, _end(end)
		{
		};

		basic_parser_result(const node_type &ast, const iter_type &start, const iter_type &end) :
			  _success(true)
			, _ast(ast)
			, _start(start)
			, _end(end)
		{
		};

		basic_parser_result(const basic_parser_result &other) :
			  _success(other._success)
			, _error(other._error)
			, _ast(other._ast)
			, _start(other._start)
			, _end(other._end)
		{
		};

		basic_parser_result(basic_parser_result &&other) :
			  basic_parser_result()
		{
			swap(*this, other);
		};

		virtual ~basic_parser_result()
		{
		};

		basic_parser_result &operator =(basic_parser_result other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_parser_result &left, basic_parser_result &right)
		{
			using std::swap;

			swap(left._ast, right._ast);
			swap(left._end, right._end);
			swap(left._error, right._error);
			swap(left._start, right._start);
			swap(left._success, right._success);
		};

		bool success() const
		{
			return _success;
		};

		const string_type &error() const
		{
			return _error;
		};

		const node_type &ast() const
		{
			return _ast;
		};

		const iter_type &start() const
		{
			return _start;
		};

		const iter_type &end() const
		{
			return _end;
		};

	private:
		bool _success;
		string_type _error;
		node_type _ast;
		iter_type _start;
		iter_type _end;
	};

	typedef basic_parser_result<char> parser_result;
	typedef basic_parser_result<wchar_t> wparser_result;
};
