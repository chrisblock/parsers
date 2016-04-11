#include "stdafx.h"

#include "regex_table_lexer.h"

class regex_table_lexer_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(regex_table_lexer_tests, lex_ProducesCorrectTokenStream)
{
	lexing::regex_table_lexer lexer;

	lexer.add_entry("look\\b", "look");
	lexer.add_entry("a\\b", "a");
	lexer.add_entry("string\\b", "string");

	std::vector<lexing::token> tokens = lexer.lex("look a string\r\nlook\na");

	EXPECT_EQ(5, tokens.size());

	lexing::token first = tokens.at(0);
	lexing::token second = tokens.at(1);
	lexing::token third = tokens.at(2);
	lexing::token fourth = tokens.at(3);
	lexing::token fifth = tokens.at(4);

	EXPECT_EQ(1, first.get_line());
	EXPECT_EQ(1, first.get_position());

	EXPECT_EQ(1, second.get_line());
	EXPECT_EQ(6, second.get_position());

	EXPECT_EQ(1, third.get_line());
	EXPECT_EQ(8, third.get_position());

	EXPECT_EQ(2, fourth.get_line());
	EXPECT_EQ(1, fourth.get_position());

	EXPECT_EQ(3, fifth.get_line());
	EXPECT_EQ(1, fifth.get_position());
}
