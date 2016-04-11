#include "stdafx.h"

#include <terminal_symbol_parser.h>

class terminal_symbol_parser_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(terminal_symbol_parser_tests, make_terminal_symbol_parser)
{
	std::shared_ptr<parsing::parser> parser = parsing::make_terminal_parser("left-paren");

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser->parse(input);

	EXPECT_EQ(true, result.success());
}

TEST_F(terminal_symbol_parser_tests, parse_parses_successfully)
{
	parsing::terminal_symbol_parser parser("left-paren");

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_EQ(true, result.success());
}

TEST_F(terminal_symbol_parser_tests, parse_produces_ast_with_name_equal_to_symbol_name)
{
	parsing::terminal_symbol_parser parser("left-paren");

	std::vector<lexing::token> v;

	lexing::token token("(", "left-paren");

	v.push_back(token);
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	auto tree = result.ast();

	EXPECT_EQ(token.get_type(), tree.get_name());
}

TEST_F(terminal_symbol_parser_tests, parse_produces_ast_with_no_children)
{
	parsing::terminal_symbol_parser parser("left-paren");

	std::vector<lexing::token> v;

	lexing::token token("(", "left-paren");

	v.push_back(token);
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	auto tree = result.ast();

	EXPECT_TRUE(tree.get_children().empty());
}

TEST_F(terminal_symbol_parser_tests, parse_does_not_read_token_stream_to_the_end)
{
	parsing::terminal_symbol_parser parser("left-paren");

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_GT(v.cend(), result.start());
}

TEST_F(terminal_symbol_parser_tests, parse_parses_unsuccessfully)
{
	parsing::terminal_symbol_parser parser("left-paren");

	std::vector<lexing::token> v;

	v.push_back(lexing::token(")", "right-paren"));
	v.push_back(lexing::token("(", "left-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_EQ(false, result.success());
}
