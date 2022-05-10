#ifndef PARSER_PREBUILT_REGEX_ROOT_HPP
#define PARSER_PREBUILT_REGEX_ROOT_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class root : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            root(): node("", node::type::ROOT, node::operands_order::ROOT)
            {
            }

            bool compute(ExpectedInputType& expr) override
            {
                bool result = true;

                for (auto& child: this->children)
                {
                    result = result && child->compute(expr);
                }

                return result;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ROOT_HPP
