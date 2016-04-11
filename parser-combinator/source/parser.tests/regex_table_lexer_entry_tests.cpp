#include "stdafx.h"

#include <regex>

#include "regex_table_lexer_entry.h"

class regex_table_lexer_entry_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(regex_table_lexer_entry_tests, DefaultConstructor_CreatesExpressionWithDefaultSyntaxOptions)
{
	lexing::regex_table_lexer_entry entry;

	std::regex_constants::syntax_option_type expected = std::regex().flags();

	std::regex_constants::syntax_option_type actual = entry.get_expression().flags();

	EXPECT_EQ(expected, actual);
}

TEST_F(regex_table_lexer_entry_tests, ConstructorAcceptingExpressionString_CreatesExpressionWithDefaultSyntaxOptions)
{
	static const char REGEX[] = "\\w+";

	std::regex_constants::syntax_option_type expected = std::regex(REGEX).flags();

	lexing::regex_table_lexer_entry entry(REGEX, "type");

	std::regex_constants::syntax_option_type actual = entry.get_expression().flags();

	EXPECT_EQ(expected, actual);
}

TEST_F(regex_table_lexer_entry_tests, CopyConstructor_CopiesExpression)
{
	static const char REGEX[] = "\\w+";
	static const char TYPE[] = "type";

	lexing::regex_table_lexer_entry entry(REGEX, TYPE);

	lexing::regex_table_lexer_entry copy(entry);

	// TODO: regex does not have an equality operator....
	//EXPECT_EQ(entry.get_expression(), copy.get_expression());
}

TEST_F(regex_table_lexer_entry_tests, CopyConstructor_CopiesType)
{
	static const char REGEX[] = "\\w+";
	static const char TYPE[] = "type";

	lexing::regex_table_lexer_entry entry(REGEX, TYPE);

	lexing::regex_table_lexer_entry copy(entry);

	EXPECT_EQ(entry.get_type(), copy.get_type());
}

TEST_F(regex_table_lexer_entry_tests, AssignmentOperator_CopiesExpression)
{
	static const char REGEX[] = "\\w+";
	static const char TYPE[] = "type";

	lexing::regex_table_lexer_entry entry(REGEX, TYPE);

	lexing::regex_table_lexer_entry copy;

	copy = entry;

	// TODO: regex does not have an equality operator....
	//EXPECT_EQ(entry.get_expression(), copy.get_expression());
}

TEST_F(regex_table_lexer_entry_tests, AssignmentOperator_CopiesType)
{
	static const char REGEX[] = "\\w+";
	static const char TYPE[] = "type";

	lexing::regex_table_lexer_entry entry(REGEX, TYPE);

	lexing::regex_table_lexer_entry copy;

	copy = entry;

	EXPECT_EQ(entry.get_type(), copy.get_type());
}

TEST_F(regex_table_lexer_entry_tests, consume_produces_token_when_consume_is_true)
{
	static const char REGEX[] = "\\w+";
	static const char TYPE[] = "type";

	lexing::regex_table_lexer_entry entry(REGEX, TYPE);

	std::string str = "hello, world";

	lexing::token t;

	bool result = entry.consume(str.cbegin(), str.cend(), t);

	EXPECT_EQ(true, result);
	// TODO: consume doesn't actually move the iterator..this maybe should change
	//EXPECT_EQ(5, std::distance(str.cbegin(), start));
	EXPECT_EQ("hello", t.get_text());
	EXPECT_EQ(TYPE, t.get_type());
	EXPECT_EQ(0, t.get_line());
	EXPECT_EQ(0, t.get_position());
}
