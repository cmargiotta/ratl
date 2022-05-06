#include <catch2/catch.hpp>

#include <fstream>
#include <iostream>

#include <parser/math.hpp>
#include <parser/regex.hpp>

SCENARIO("Regex parse tree")
{
    GIVEN("A regex parser and an expression tree")
    {
        ratl::regex_parser parser_;

        std::string parse_expr("1*2+a?[\\dA]*");
        auto        tree = parser_(parse_expr);

        std::string parse_expr1("[1-2]+");
        auto        tree1 = parser_(parse_expr1);

        REQUIRE(tree->to_string() == parse_expr);
        REQUIRE(tree1->to_string() == parse_expr1);

        WHEN("It is asked to compute")
        {
            THEN("It correctly interprets its language")
            {
                std::string expression("1222");
                REQUIRE(tree->compute(expression));

                expression = "22222";
                REQUIRE(tree->compute(expression));

                expression = "1111122222";
                REQUIRE(tree->compute(expression));

                expression = "122222a";
                REQUIRE(tree->compute(expression));

                expression = "122222a9999";
                REQUIRE(tree->compute(expression));

                expression = "122222aAAAA";
                REQUIRE(tree->compute(expression));

                expression = "122222a9AA999";
                REQUIRE(tree->compute(expression));

                expression = "22222aa";
                REQUIRE(tree->compute(expression));

                expression = "111aa";
                REQUIRE(!tree->compute(expression));

                expression = "111";
                REQUIRE(!tree->compute(expression));

                expression = "";
                REQUIRE(!tree->compute(expression));

                expression = "12344";
                REQUIRE(tree1->compute(expression));
            }
        }
    }
}

SCENARIO("Math parse tree")
{
    GIVEN("A regex parser and an expression tree")
    {
        ratl::math_parser parser_;

        std::string parse_expr("12+5");
        auto        tree = parser_(parse_expr);

        REQUIRE(tree->to_string() == parse_expr);

        WHEN("It is asked to compute")
        {
            THEN("It correctly interprets its expression")
            {
                REQUIRE(tree->compute() == 17);
            }
        }
    }
}