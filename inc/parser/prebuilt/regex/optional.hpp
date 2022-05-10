#ifndef PARSER_PREBUILT_REGEX_MAYBE_HPP
#define PARSER_PREBUILT_REGEX_MAYBE_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class optional : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier     = "?";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT;

        public:
            inline explicit optional(const std::string&): node(identifier, type, operands_order)
            {
            }

            inline bool compute(std::string& expression) override
            {
                auto expression_backup = expression;

                if (!this->children[0]->compute(expression))
                {
                    expression = expression_backup;
                }

                return true;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_MAYBE_HPP
