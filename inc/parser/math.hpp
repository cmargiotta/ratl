#ifndef PARSER_MATH_HPP
#define PARSER_MATH_HPP

#include <utility>

#include <parser/tokenizer/regex_tokenizer.hpp>

#include "parser.hpp"
#include "prebuilt/arithmetic/by.hpp"
#include "prebuilt/arithmetic/divided_by.hpp"
#include "prebuilt/arithmetic/minus.hpp"
#include "prebuilt/arithmetic/number.hpp"
#include "prebuilt/arithmetic/par_close.hpp"
#include "prebuilt/arithmetic/par_open.hpp"
#include "prebuilt/arithmetic/plus.hpp"
#include "prebuilt/arithmetic/power.hpp"
#include "prebuilt/arithmetic/root.hpp"

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
