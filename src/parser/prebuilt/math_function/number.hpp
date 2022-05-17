#ifndef PARSER_PREBUILT_MATH_FUNCTION_NUMBER_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_NUMBER_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

#include <parser/parse_node.hpp>

namespace ratl::math_function
{
    class number : public ratl::parse_node<ratl::math::fraction<int>,
                                           std::unordered_map<std::string, ratl::math::fraction<int>>>
    {
        private:
            using node = ratl::parse_node<ratl::math::fraction<int>,
                                          std::unordered_map<std::string, ratl::math::fraction<int>>>;

            const ratl::math::fraction<int> value;

        public:
            static const inline std::string identifier = "\\-?[0-9]+";
            static const inline auto        type       = node::type::LEAF;

        public:
            inline explicit number(const std::string& token)
                : node(identifier, type), value(std::stoi(token))
            {
            }

            inline explicit number(ratl::math::fraction<int> val)
                : node(identifier, type), value(val)
            {
            }

            inline ratl::math::fraction<int>
                compute(std::unordered_map<std::string, ratl::math::fraction<int>>&) override
            {
                return value;
            }

            inline std::string to_string() override
            {
                return static_cast<std::string>(value);
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_NUMBER_HPP
