#include "stdafx.h"

#include <fstream>
#include <regex>
#include <windows.h>

#include "regex_table_lexer.h"
#include "regex_table_lexer_entry.h"

#include <alternative_parser.h>
#include <kleene_plus_parser.h>
#include <sequence_parser.h>
#include <terminal_symbol_parser.h>

#include <handle.h>
#include <map_view.h>

TEST(file_tests, can_memory_map_file)
{
	handle create = ::CreateFile(_T("C:\\test.qml"), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (create.is_valid())
	{
		handle map = ::CreateFileMapping(create.get(), nullptr, PAGE_READONLY, 0, 0, nullptr);

		if (map.is_valid())
		{
			map_view view(std::move(map));

			LPCSTR str = view.get_str();

			::_tprintf(_T("%S\n"), str);

			std::regex r("\\w+");

			std::match_results<const char *> match;

			if (std::regex_search(str, match, r))
			{
				::_tprintf(_T("%S"), match.str().c_str());
			}
		}
		else
		{
		}
	}
	else
	{
	}
}

TEST(file_tests, can_parse_simple_file)
{
	std::ifstream file("C:\\test.qml");

	std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	lexing::regex_table_lexer lexer;

	lexer.add_entry(R"(^\{)", "left-curly-brace");
	lexer.add_entry(R"(^\})", "right-curly-brace");
	lexer.add_entry(R"(^\[)", "left-bracket");
	lexer.add_entry(R"(^\])", "right-bracket");
	lexer.add_entry(R"(^:)", "colon");
	lexer.add_entry(R"(^;)", "semi-colon");
	lexer.add_entry(R"(^,)", "comma");
	lexer.add_entry(R"(^\.)", "dot");

	lexer.add_entry(R"(^property\b)", "property-keyword");
	lexer.add_entry(R"(^import\b)", "import-keyword");
	lexer.add_entry(R"(^function\b)", "function-keyword");

	lexer.add_entry(R"regex(^(['"])(?:\\.|[^\\])*\1)regex", "string");
	lexer.add_entry(R"(^\d+)", "number"); // enhance this to also recognize negatives and floating-point
	lexer.add_entry(R"(^[A-Z]\w*)", "object-name");
	lexer.add_entry(R"(^\w+)", "name");

	// TODO: lexing iterator???
	auto tokens = lexer.lex(buffer);

	ast::node ast;

	parsing::parser_result input(ast, tokens.cbegin(), tokens.cend());

	std::shared_ptr<parsing::parser> object_name_parser = parsing::make_terminal_parser("object-name");
	std::shared_ptr<parsing::parser> left_curly_brace_parser = parsing::make_terminal_parser("left-curly-brace");
	std::shared_ptr<parsing::parser> right_curly_brace_parser = parsing::make_terminal_parser("right-curly-brace");

	std::shared_ptr<parsing::parser> name_parser = parsing::make_terminal_parser("name");
	std::shared_ptr<parsing::parser> colon_parser = parsing::make_terminal_parser("colon");
	std::shared_ptr<parsing::parser> number_parser = parsing::make_terminal_parser("number");
	std::shared_ptr<parsing::parser> string_parser = parsing::make_terminal_parser("string");
	std::shared_ptr<parsing::parser> value_parser = parsing::make_alternative_parser("property-value", number_parser, string_parser);
	std::shared_ptr<parsing::parser> property_parser = parsing::make_sequence_parser("property", name_parser, colon_parser, value_parser);

	std::shared_ptr<parsing::parser> property_list_parser = parsing::make_kleene_plus_parser("property-list", property_parser);

	std::shared_ptr<parsing::parser> object_parser = parsing::make_sequence_parser("object", object_name_parser, left_curly_brace_parser, property_list_parser, right_curly_brace_parser);

	auto result = object_parser->parse(input);

	EXPECT_EQ(true, result.success());
}
