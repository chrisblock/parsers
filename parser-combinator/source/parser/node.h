#pragma once

#include <string>
#include <vector>

#include "token.h"

namespace ast
{
	template <typename TChar>
	class basic_node
	{
	public:
		typedef std::basic_string<TChar> string_type;
		typedef lexing::basic_token<TChar> token_type;
		typedef typename std::vector<token_type>::const_iterator iter_type;

		basic_node()
		{
		};

		basic_node(const string_type &name) :
			  _name(name)
		{
		};

		basic_node(const string_type &name, const iter_type &start, const iter_type &end) :
			  _name(name)
			, _start(start)
			, _end(end)
		{
		};

		basic_node(const string_type &name, const std::vector<basic_node> &children, const iter_type &start, const iter_type &end) :
			  _name(name)
			, _start(start)
			, _end(end)
			, _children(children)
		{
		};

		basic_node(const basic_node &other) :
			  _name(other._name)
			, _start(other._start)
			, _end(other._end)
			, _children(other._children)
		{
		};

		basic_node(basic_node &&other) :
			  basic_node()
		{
			swap(*this, other);
		};

		virtual ~basic_node()
		{
		};

		basic_node &operator =(basic_node other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_node &left, basic_node &right)
		{
			using std::swap;

			swap(left._children, right._children);
			swap(left._end, right._end);
			swap(left._name, right._name);
			swap(left._start, right._start);
		};

		const string_type &get_name() const
		{
			return _name;
		};

		void set_name(const string_type &name)
		{
			_name = name;
		};

		const iter_type &get_token_start() const
		{
			return _start;
		};

		void set_token_start(const iter_type &start)
		{
			_start = start;
		};

		const iter_type &get_token_end() const
		{
			return _end;
		};

		void set_token_end(const iter_type &end)
		{
			_end = end;
		};

		const std::vector<basic_node> &get_children() const
		{
			return _children;
		};

		void add_child(const basic_node &node)
		{
			_children.push_back(node);
		};

	private:
		string_type _name;
		iter_type _start; // TODO: replace this with a fancy iterator
		iter_type _end;
		std::vector<basic_node> _children;
	};

	typedef basic_node<char> node;
	typedef basic_node<wchar_t> wnode;
}
