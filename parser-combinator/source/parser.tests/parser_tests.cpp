#include "stdafx.h"

#include "alternative_parser.h"
#include "parser.h"
#include "terminal_symbol_parser.h"

class parser_tests : public testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(parser_tests, test)
{
	parsing::alternative_parser parser;
}

TEST_F(parser_tests, test2)
{
	std::vector<std::shared_ptr<parsing::parser>> parsers;

	parsing::alternative_parser parser("name", parsers);
}

TEST_F(parser_tests, test3)
{
	std::shared_ptr<parsing::parser> p = std::make_shared<parsing::terminal_symbol_parser>("hello");

	std::shared_ptr<parsing::parser> parser = parsing::make_alternative_parser("name", p, p, p);
}
