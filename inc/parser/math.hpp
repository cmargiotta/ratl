#ifndef PARSER_MATH_HPP
#define PARSER_MATH_HPP

#include <utility>

#include <parser/parser.hpp>
#include <parser/prebuilt/arithmetic/by.hpp>
#include <parser/prebuilt/arithmetic/divided_by.hpp>
#include <parser/prebuilt/arithmetic/minus.hpp>
#include <parser/prebuilt/arithmetic/number.hpp>
#include <parser/prebuilt/arithmetic/par_close.hpp>
#include <parser/prebuilt/arithmetic/par_open.hpp>
#include <parser/prebuilt/arithmetic/plus.hpp>
#include <parser/prebuilt/arithmetic/power.hpp>
#include <parser/prebuilt/arithmetic/root.hpp>
#include <parser/tokenizer/regex_tokenizer.hpp>

namespace ratl
{
    using math_parser = parser<tokenizer::regex_tokenizer,
                               arithmetic::root,
                               arithmetic::number,
                               arithmetic::plus,
                               arithmetic::by,
                               arithmetic::divided_by,
                               arithmetic::minus,
                               arithmetic::power,
                               arithmetic::par_close,
                               arithmetic::par_open>;

    using math_tree = decltype(std::declval<math_parser>()(std::declval<std::string>()));
}// namespace ratl

#endif// PARSER_MATH_HPP
