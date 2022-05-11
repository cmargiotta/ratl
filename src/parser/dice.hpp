#ifndef PARSER_DICE_HPP
#define PARSER_DICE_HPP

#include <string>
#include <tuple>

#include <parser/math.hpp>
#include <parser/parser.hpp>
#include <parser/prebuilt/dice_roller/dice.hpp>
#include <parser/tokenizer/regex_tokenizer.hpp>

namespace ratl
{
    using dice_parser
        = parser<tokenizer::regex_tokenizer, arithmetic::root, typename math_parser::nodes, dice_roller::dice>;

    using dice_tree = decltype(std::declval<dice_parser>()(std::declval<std::string>()));
}// namespace ratl

#endif// PARSER_DICE_HPP
