#include "stdafx.h"

#include <sequence_parser.h>

#include <terminal_symbol_parser.h>

class sequence_parser_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(sequence_parser_tests, parse_recognized_token_sequence_is_successful)
{
	std::shared_ptr<parsing::parser> left_paren_parser = parsing::make_terminal_parser("left-paren");
	std::shared_ptr<parsing::parser> variable_name_parser = parsing::make_terminal_parser("variable-name");
	std::shared_ptr<parsing::parser> right_paren_parser = parsing::make_terminal_parser("right-paren");

	parsing::sequence_parser parser("sequence", { left_paren_parser, variable_name_parser, right_paren_parser });

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token("local", "variable-name"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_EQ(true, result.success());
}

TEST_F(sequence_parser_tests, parse_reads_token_stream_to_end)
{
	std::shared_ptr<parsing::parser> left_paren_parser = parsing::make_terminal_parser("left-paren");
	std::shared_ptr<parsing::parser> variable_name_parser = parsing::make_terminal_parser("variable-name");
	std::shared_ptr<parsing::parser> right_paren_parser = parsing::make_terminal_parser("right-paren");

	parsing::sequence_parser parser("sequence", { left_paren_parser, variable_name_parser, right_paren_parser });

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token("local", "variable-name"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_EQ(v.cend(), result.start());
}

TEST_F(sequence_parser_tests, parse_produces_ast_with_node_named_after_sequence_parser)
{
	static const char NAME[] = "sequence";

	std::shared_ptr<parsing::parser> left_paren_parser = parsing::make_terminal_parser("left-paren");
	std::shared_ptr<parsing::parser> variable_name_parser = parsing::make_terminal_parser("variable-name");
	std::shared_ptr<parsing::parser> right_paren_parser = parsing::make_terminal_parser("right-paren");

	parsing::sequence_parser parser(NAME, { left_paren_parser, variable_name_parser, right_paren_parser });

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token("local", "variable-name"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	auto tree = result.ast();

	EXPECT_STREQ(NAME, tree.get_name().c_str());
}

TEST_F(sequence_parser_tests, parse_produces_ast_with_a_child_for_each_parser_in_sequence)
{
	std::shared_ptr<parsing::parser> left_paren_parser = parsing::make_terminal_parser("left-paren");
	std::shared_ptr<parsing::parser> variable_name_parser = parsing::make_terminal_parser("variable-name");
	std::shared_ptr<parsing::parser> right_paren_parser = parsing::make_terminal_parser("right-paren");

	parsing::sequence_parser parser("sequence", { left_paren_parser, variable_name_parser, right_paren_parser });

	std::vector<lexing::token> v;

	v.push_back(lexing::token("(", "left-paren"));
	v.push_back(lexing::token("local", "variable-name"));
	v.push_back(lexing::token(")", "right-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	auto tree = result.ast();

	EXPECT_EQ(3, tree.get_children().size());
}

TEST_F(sequence_parser_tests, parse_unrecognized_token_sequence_is_not_successful)
{
	std::shared_ptr<parsing::parser> left_paren_parser = parsing::make_terminal_parser("left-paren");
	std::shared_ptr<parsing::parser> variable_name_parser = parsing::make_terminal_parser("variable-name");
	std::shared_ptr<parsing::parser> right_paren_parser = parsing::make_terminal_parser("right-paren");

	parsing::sequence_parser parser("sequence", { left_paren_parser, variable_name_parser, right_paren_parser });

	std::vector<lexing::token> v;

	v.push_back(lexing::token(")", "right-paren"));
	v.push_back(lexing::token("local", "variable-name"));
	v.push_back(lexing::token("(", "left-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_EQ(false, result.success());
}

TEST_F(sequence_parser_tests, parse_unrecognized_token_sequence_has_correct_error_message)
{
	std::shared_ptr<parsing::parser> left_paren_parser = parsing::make_terminal_parser("left-paren");
	std::shared_ptr<parsing::parser> variable_name_parser = parsing::make_terminal_parser("variable-name");
	std::shared_ptr<parsing::parser> right_paren_parser = parsing::make_terminal_parser("right-paren");

	parsing::sequence_parser parser("sequence", { left_paren_parser, variable_name_parser, right_paren_parser });

	std::vector<lexing::token> v;

	v.push_back(lexing::token(")", "right-paren"));
	v.push_back(lexing::token("local", "variable-name"));
	v.push_back(lexing::token("(", "left-paren"));

	ast::node ast;

	parsing::parser_result input(ast, v.cbegin(), v.cend());

	auto result = parser.parse(input);

	EXPECT_EQ("Unrecognized token ')' at line 0, position 0.", result.error());
}
