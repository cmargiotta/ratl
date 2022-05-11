#ifndef PARSER_PREBUILT_ARITHMETIC_ROOT_HPP
#define PARSER_PREBUILT_ARITHMETIC_ROOT_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::arithmetic
{
    class root : public ratl::parse_node<int, void>
    {
        private:
            using node = ratl::parse_node<int, void>;

        public:
            root(): node("", node::type::ROOT, node::operands_order::ROOT)
            {
            }

            int compute() override
            {
                return children[0]->compute();
            }
    };
}// namespace ratl::arithmetic

#endif// PARSER_PREBUILT_ARITHMETIC_ROOT_HPP
