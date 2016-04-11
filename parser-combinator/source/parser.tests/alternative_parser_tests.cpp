#include "stdafx.h"

#include <alternative_parser.h>

#include <node.h>
#include <terminal_symbol_parser.h>

class alternative_parser_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(alternative_parser_tests, parse_parses_this_successfully)
{
	std::shared_ptr<parsing::parser> this_parser = parsing::make_terminal_parser("this");
	std::shared_ptr<parsing::parser> that_parser = parsing::make_terminal_parser("that");

	parsing::alternative_parser alternative("alternative", { this_parser, that_parser });

	std::vector<lexing::token> v;

	v.emplace_back("this", "this");

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = alternative.parse(input);

	EXPECT_EQ(true, result.success());
}

TEST_F(alternative_parser_tests, parse_parses_that_successfully)
{
	std::shared_ptr<parsing::parser> this_parser = parsing::make_terminal_parser("this");
	std::shared_ptr<parsing::parser> that_parser = parsing::make_terminal_parser("that");

	parsing::alternative_parser alternative("alternative", { this_parser, that_parser });

	std::vector<lexing::token> v;

	v.emplace_back("that", "that");

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = alternative.parse(input);

	EXPECT_EQ(true, result.success());
}

TEST_F(alternative_parser_tests, parse_returns_ast_with_root_node_with_name_of_matched_parser)
{
	static const char expected[] = "this";

	std::shared_ptr<parsing::parser> this_parser = parsing::make_terminal_parser(expected);
	std::shared_ptr<parsing::parser> that_parser = parsing::make_terminal_parser("that");

	parsing::alternative_parser alternative("alternative", { this_parser, that_parser });

	std::vector<lexing::token> v;

	v.emplace_back("this", "this");

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = alternative.parse(input);

	auto tree = result.ast();

	EXPECT_EQ(expected, tree.get_name());
}
