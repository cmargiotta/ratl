#ifndef PARSER_PREBUILT_ARITHMETIC_MINUS_HPP
#define PARSER_PREBUILT_ARITHMETIC_MINUS_HPP

#include <cstdint>
#include <string>

#include <parser/parse_node.hpp>

namespace ratl::arithmetic
{
    class minus : public ratl::parse_node<int, void>
    {
        private:
            using node = ratl::parse_node<int, void>;

        private:
            std::string to_string_() override
            {
                return "-";
            }

        public:
            static const inline std::string identifier     = "\\-";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit minus(const std::string&): node(identifier, type, operands_order)
            {
            }

            inline int compute() override
            {
                return children[0]->compute() - children[1]->compute();
            }
    };
}// namespace ratl::arithmetic

#endif// PARSER_PREBUILT_ARITHMETIC_MINUS_HPP
