#ifndef PARSER_PREBUILT_ARITHMETIC_DIVIDED_BY_HPP
#define PARSER_PREBUILT_ARITHMETIC_DIVIDED_BY_HPP

#include <cstdint>
#include <string>

#include <parser/parse_node.hpp>

namespace ratl::arithmetic
{
    class divided_by : public ratl::parse_node<int, void>
    {
        private:
            using node = ratl::parse_node<int, void>;

        public:
            static const inline std::string identifier     = "/";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit divided_by(const std::string&): node(identifier, type, operands_order)
            {
            }

            inline int compute() override
            {
                return children[0]->compute() / children[1]->compute();
            }
    };
}// namespace ratl::arithmetic

#endif// PARSER_PREBUILT_ARITHMETIC_DIVIDED_BY_HPP
