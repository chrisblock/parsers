#pragma once

#include <cstdint>
#include <string>

namespace lexing
{
	template <typename TChar>
	class basic_token
	{
	public:
		typedef std::int32_t line_type;
		typedef std::int32_t position_type;
		typedef std::basic_string<TChar> string_type;
		typedef typename std::basic_string<TChar>::size_type size_type;

		basic_token() :
			  _line(0)
			, _position(0)
		{
		};

		basic_token(const string_type &text, const string_type &type) :
			  _line(0)
			, _position(0)
			, _text(text)
			, _type(type)
		{
		};

		basic_token(const basic_token &other) :
			  _line(other._line)
			, _position(other._position)
			, _text(other._text)
			, _type(other._type)
		{
		};

		basic_token(basic_token &&other)
		{
			swap(*this, other);
		};

		virtual ~basic_token()
		{
		};

		basic_token &operator =(basic_token other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_token &left, basic_token &right)
		{
			using std::swap;

			swap(left._line, right._line);
			swap(left._position, right._position);
			swap(left._text, right._text);
			swap(left._type, right._type);
		};

		void set_text(const string_type &text)
		{
			_text = text;
		};

		const string_type &get_text() const
		{
			return _text;
		};

		size_type length() const
		{
			return _text.length();
		};

		void set_type(const string_type &type)
		{
			_type = type;
		};

		const string_type &get_type() const
		{
			return _type;
		};

		void set_line(const line_type line)
		{
			_line = line;
		};

		line_type get_line() const
		{
			return _line;
		};

		void set_position(const position_type position)
		{
			_position = position;
		};

		position_type get_position() const
		{
			return _position;
		};

	private:
		line_type _line;
		position_type _position;
		string_type _text;
		string_type _type;
	};

	typedef basic_token<char> token;
	typedef basic_token<wchar_t> wtoken;
};
