#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

#include <fstream>
#include <iostream>

#include <math/fraction.hpp>
#include <parser/dice.hpp>
#include <parser/math.hpp>
#include <parser/math_function.hpp>
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
        AND_WHEN("Two trees are merged")
        {
            ratl::regex_parser parser_;

            std::string parse_expr("1*2+a?[\\dA]*");
            auto        tree = parser_(parse_expr);

            std::string parse_expr1 = "[1-2]+";
            auto        tree1       = parser_(parse_expr1);

            tree->merge(std::move(tree1));

            THEN("They are correctly merged")
            {
                REQUIRE(tree->to_string() == ("(" + parse_expr + ")|(" + parse_expr1 + ")"));

                std::string expression = "12344";
                REQUIRE(tree->compute(expression));

                expression = "22222aa";
                REQUIRE(tree->compute(expression));
            }
        }
    }
}

SCENARIO("Math parse tree")
{
    GIVEN("A regex parser and an expression tree")
    {
        ratl::math_parser parser_;

        WHEN("It is asked to compute")
        {
            THEN("It correctly interprets its expression")
            {
                std::string parse_expr("12+5*2");
                auto        tree = parser_(parse_expr);
                REQUIRE(tree->to_string() == parse_expr);
                REQUIRE(tree->compute() == 34);

                parse_expr = "(12+5)*2";
                tree       = parser_(parse_expr);
                REQUIRE(tree->to_string() == parse_expr);
                REQUIRE(tree->compute() == 34);

                parse_expr = "12+5^2";
                tree       = parser_(parse_expr);
                REQUIRE(tree->to_string() == parse_expr);
                REQUIRE(tree->compute() == 289);
            }
        }
    }
}

SCENARIO("Math function parse tree")
{
    GIVEN("A regex parser and an expression tree")
    {
        ratl::math_function_parser parser_;

        WHEN("It is asked to compute")
        {
            THEN("It correctly interprets it")
            {
                std::string parse_expr("12/2+2+5xy");
                auto        tree = parser_(parse_expr);
                std::unordered_map<std::string, ratl::math::fraction<int>> unknowns;
                unknowns["x"] = ratl::math::fraction<int>(1, 2);
                unknowns["y"] = ratl::math::fraction<int>(2, 1);

                tree->simplify();

                REQUIRE(tree->to_string() == "13xy");
                auto result = tree->compute(unknowns);
                REQUIRE(result.numerator == 13);
                REQUIRE(result.denominator == 1);
            }
        }
    }
}

SCENARIO("Dice parse tree")
{
    GIVEN("A regex parser and an expression tree")
    {
        ratl::dice_parser parser_;

        std::string parse_expr("10d6");
        auto        tree = parser_(parse_expr);

        REQUIRE(tree->to_string() == parse_expr);

        WHEN("It is asked to compute")
        {
            THEN("It correctly interprets its expression")
            {
                for (int i = 0; i < 100; ++i)
                {
                    auto result = tree->compute();
                    REQUIRE(result <= 60);
                    REQUIRE(result >= 1);
                }
            }
        }
    }
}