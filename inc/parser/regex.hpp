#ifndef PARSER_REGEX_HPP
#define PARSER_REGEX_HPP

#include <utility>

#include <parser/parser.hpp>
#include <parser/prebuilt/regex/alphanumeric_latin.hpp>
#include <parser/prebuilt/regex/any.hpp>
#include <parser/prebuilt/regex/at_least_one.hpp>
#include <parser/prebuilt/regex/character.hpp>
#include <parser/prebuilt/regex/digit.hpp>
#include <parser/prebuilt/regex/minus.hpp>
#include <parser/prebuilt/regex/non_digit.hpp>
#include <parser/prebuilt/regex/optional.hpp>
#include <parser/prebuilt/regex/par_close.hpp>
#include <parser/prebuilt/regex/root.hpp>
#include <parser/prebuilt/regex/round_par_open.hpp>
#include <parser/prebuilt/regex/square_par_open.hpp>
#include <parser/prebuilt/regex/star.hpp>
#include <parser/tokenizer/exact_tokenizer.hpp>

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
