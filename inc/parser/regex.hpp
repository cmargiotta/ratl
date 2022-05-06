#ifndef PARSER_REGEX_HPP
#define PARSER_REGEX_HPP

#include <utility>

#include "parser.hpp"
#include "prebuilt/regex/alphanumeric_latin.hpp"
#include "prebuilt/regex/any.hpp"
#include "prebuilt/regex/at_least_one.hpp"
#include "prebuilt/regex/character.hpp"
#include "prebuilt/regex/digit.hpp"
#include "prebuilt/regex/minus.hpp"
#include "prebuilt/regex/non_digit.hpp"
#include "prebuilt/regex/optional.hpp"
#include "prebuilt/regex/par_close.hpp"
#include "prebuilt/regex/root.hpp"
#include "prebuilt/regex/round_par_open.hpp"
#include "prebuilt/regex/square_par_open.hpp"
#include "prebuilt/regex/star.hpp"
#include "tokenizer/exact_tokenizer.hpp"

namespace ratl
{
    using regex_parser = parser<tokenizer::exact_string_tokenizer,
                                regex::root,
                                regex::alphanumeric_latin,
                                regex::any,
                                regex::at_least_one,
                                regex::character,
                                regex::digit,
                                regex::non_digit,
                                regex::optional,
                                regex::minus,
                                regex::par_close,
                                regex::round_par_open,
                                regex::square_par_open,
                                regex::star>;

    using regex_tree = decltype(std::declval<regex_parser>()(std::declval<std::string>()));
}// namespace ratl

#endif// PARSER_REGEX_HPP
