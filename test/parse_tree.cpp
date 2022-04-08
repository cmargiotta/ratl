#include <iostream>

#include "catch2/catch.hpp"
#include "parse_tree/parse_node.hpp"
#include "parse_tree/parser.hpp"
#include "parse_tree/tokenizer/exact_tokenizer.hpp"
#include "stubs/parse_node.hpp"

SCENARIO("Parse tree realization")
{
	GIVEN("A simple parse node")
	{
		WHEN("A parser is declared with the node inside")
		{
			ratl::parser<ratl::tokenizer::exact_tokenizer<char>, node> parser;

			THEN("No errors occur")
			{
			}
		}
		AND_WHEN("The built parser is called for an expression")
		{
			ratl::parser<ratl::tokenizer::exact_tokenizer<char>, node> parser;

			std::string expression("a");

			auto tree = parser(expression.begin(), expression.end());

			THEN("The built parse tree is correct")
			{
				REQUIRE(tree->get_identifier() == 'a');
			}
		}
	}
}