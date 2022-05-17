#ifndef PARSER_MATH_FUNCTION_HPP
#define PARSER_MATH_FUNCTION_HPP

#include <utility>

#include <parser/parser.hpp>
#include <parser/prebuilt/math_function/by.hpp>
#include <parser/prebuilt/math_function/divided_by.hpp>
#include <parser/prebuilt/math_function/minus.hpp>
#include <parser/prebuilt/math_function/number.hpp>
#include <parser/prebuilt/math_function/par_close.hpp>
#include <parser/prebuilt/math_function/par_open.hpp>
#include <parser/prebuilt/math_function/plus.hpp>
//#include <parser/prebuilt/math_function/power.hpp>
#include <parser/prebuilt/math_function/root.hpp>
#include <parser/prebuilt/math_function/unknown.hpp>
#include <parser/tokenizer/regex_tokenizer.hpp>

namespace ratl
{
    using math_function_parser = parser<tokenizer::regex_tokenizer,
                                        math_function::root,
                                        math_function::number,
                                        math_function::plus,
                                        math_function::by,
                                        math_function::divided_by,
                                        math_function::minus,
                                        // math_function::power,
                                        math_function::par_close,
                                        math_function::par_open,
                                        math_function::unknown>;

    using math_function_tree = decltype(std::declval<math_parser>()(std::declval<std::string>()));
}// namespace ratl

#endif// PARSER_MATH_HPP