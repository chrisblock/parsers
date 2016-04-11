#pragma once

#include <cstdint>
#include <regex>
#include <vector>

#include "constants.h"
#include "regex_table_lexer_entry.h"

namespace lexing
{
	template <typename TChar, typename TTraits = std::regex_traits<TChar>>
	class basic_regex_table_lexer
	{
	public:
		typedef basic_regex_table_lexer_entry<TChar, TTraits> entry_type;
		typedef std::basic_regex<TChar, TTraits> regex_type;
		typedef std::basic_string<TChar> string_type;
		typedef typename std::basic_string<TChar>::const_iterator string_const_iterator;
		typedef basic_token<TChar> token_type;

		basic_regex_table_lexer() :
			  _whitespace(const_expressions<TChar>::whitespace, const_expressions<TChar>::whitespace_type)
			, _newline(const_expressions<TChar>::newline, const_expressions<TChar>::newline_type)
		{
		};

		basic_regex_table_lexer(const basic_regex_table_lexer &other) :
			  _entries(other._entries)
			, _whitespace(other._whitespace)
			, _newline(other._newline)
		{
		};

		basic_regex_table_lexer(basic_regex_table_lexer &&other) :
			basic_regex_table_lexer()
		{
			swap(*this, other);
		};

		virtual ~basic_regex_table_lexer()
		{
		};

		basic_regex_table_lexer &operator =(basic_regex_table_lexer other)
		{
			swap(*this, other);

			return *this;
		};

		friend void swap(basic_regex_table_lexer &left, basic_regex_table_lexer &right)
		{
			using std::swap;

			swap(left._entries, right._entries);
			swap(left._newline, right._newline);
			swap(left._whitespace, right._whitespace);
		};

		void add_entry(const entry_type &entry)
		{
			_entries.push_back(entry);
		};

		void add_entry(const string_type &regex, const string_type &type)
		{
			entry_type entry(regex, type);

			add_entry(entry);
		};

		void clear()
		{
			_entries.clear();
		};

		std::vector<token_type> lex(const string_type &str) const
		{
			std::vector<token_type> result;

			std::uint32_t line = 1;
			std::uint32_t position = 1;

			string_const_iterator pos = str.cbegin();
			string_const_iterator end = str.cend();

			while (pos != end)
			{
				token_type token;

				for (const auto &entry : _entries)
				{
					if (entry.consume(pos, end, token))
					{
						token.set_line(line);
						token.set_position(position);

						pos += token.length();
						position += token.length();

						result.push_back(token);

						break;
					}
				}

				if (_newline.consume(pos, end, token))
				{
					pos += token.length();
					line++;
					position = 1;
				}
				else if (_whitespace.consume(pos, end, token))
				{
					pos += token.length();
					position += token.length();
				}
			}

			return result;
		};

		std::vector<token_type> lex_file() const
		{
			std::vector<token_type> result;

			std::uint32_t line = 1;
			std::uint32_t position = 1;

			string_const_iterator pos = str.cbegin();
			string_const_iterator end = str.cend();

			while (pos != end)
			{
				token_type token;

				for (const auto &entry : _entries)
				{
					if (entry.consume(pos, end, token))
					{
						token.set_line(line);
						token.set_position(position);

						pos += token.length();
						position += token.length();

						result.push_back(token);

						break;
					}
				}

				if (_newline.consume(pos, end, token))
				{
					pos += token.length();
					line++;
					position = 1;
				}
				else if (_whitespace.consume(pos, end, token))
				{
					pos += token.length();
					position += token.length();
				}
			}

			return result;
		};

	private:
		std::vector<entry_type> _entries;
		entry_type _whitespace;
		entry_type _newline;
	};

	typedef basic_regex_table_lexer<char> regex_table_lexer;
	typedef basic_regex_table_lexer<wchar_t> wregex_table_lexer;
};
