#include "stdafx.h"

#include <kleene_plus_parser.h>

#include <terminal_symbol_parser.h>

class kleene_plus_parser_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(kleene_plus_parser_tests, parse_does_not_recognize_empty_token_stream)
{
	std::shared_ptr<parsing::parser> plus_parser = parsing::make_terminal_parser("plus");

	ast::node ast;

	std::vector<lexing::token> v;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	parsing::kleene_plus_parser parser("plus-list", plus_parser);

	auto result = parser.parse(input);

	EXPECT_EQ(false, result.success());
}

TEST_F(kleene_plus_parser_tests, parse_recognizes_sequence_of_exactly_one_symbol)
{
	std::shared_ptr<parsing::parser> plus_parser = parsing::make_terminal_parser("plus");

	ast::node ast;

	std::vector<lexing::token> v;

	v.emplace_back("+", "plus");

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	parsing::kleene_plus_parser parser("plus-list", plus_parser);

	auto result = parser.parse(input);

	EXPECT_EQ(true, result.success());
}

TEST_F(kleene_plus_parser_tests, parse_recognizes_sequence_of_more_than_one_symbol)
{
	std::shared_ptr<parsing::parser> plus_parser = parsing::make_terminal_parser("plus");

	ast::node ast;

	std::vector<lexing::token> v;

	v.emplace_back("+", "plus");
	v.emplace_back("+", "plus");
	v.emplace_back("+", "plus");
	v.emplace_back("+", "plus");

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	parsing::kleene_plus_parser parser("plus-list", plus_parser);

	auto result = parser.parse(input);

	EXPECT_EQ(true, result.success());
}
