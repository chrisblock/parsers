#pragma once

#include <iterator>

#include "token.h"

namespace lexing
{
	// TODO: make this work good

	/*
	template <typename TChar>
	class basic_token_iterator : public std::iterator<std::forward_iterator_tag, basic_token<TChar>>
	{
	public:
		basic_token_iterator()
		{
		};

		basic_token_iterator(const basic_token_iterator &other)
		{
		};

		basic_token_iterator(basic_token_iterator &&other) :
			  basic_token_iterator()
		{
			swap(*this, other);
		};

		~basic_token_iterator()
		{
		};

		friend void swap(basic_token_iterator &left, basic_token_iterator &right)
		{
			using std::swap;
		};

		basic_token_iterator &operator =(basic_token_iterator other)
		{
			swap(*this, other);

			return *this;
		};

		basic_token_iterator &operator ++() const
		{
			return *this;
		};

		basic_token_iterator &operator ++(int) const
		{
			return *this;
		};

		basic_token<TChar> &operator *()
		{
			static basic_token<TChar> tkn;

			return tkn;
		}
	};

	typedef basic_token_iterator<char> token_iterator;
	typedef basic_token_iterator<wchar_t> wtoken_iterator;
	*/
}
