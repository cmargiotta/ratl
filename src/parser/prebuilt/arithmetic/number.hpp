#ifndef PARSER_PREBUILT_ARITHMETIC_NUMBER_HPP
#define PARSER_PREBUILT_ARITHMETIC_NUMBER_HPP

#include <cstdint>
#include <string>

#include <parser/parse_node.hpp>

namespace ratl::arithmetic
{
    class number : public ratl::parse_node<int, void>
    {
        private:
            using node = ratl::parse_node<int, void>;
            const int value;

        public:
            static const inline std::string identifier = "\\-?[0-9]+";
            static const inline auto        type       = node::type::LEAF;

        public:
            inline explicit number(const std::string& token)
                : node(identifier, type), value(std::stoi(token))
            {
            }

            inline int compute() override
            {
                return value;
            }

            inline std::string to_string() override
            {
                return std::to_string(value);
            }
    };
}// namespace ratl::arithmetic

#endif// PARSER_PREBUILT_ARITHMETIC_NUMBER_HPP
