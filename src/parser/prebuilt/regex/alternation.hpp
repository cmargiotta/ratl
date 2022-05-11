#ifndef PARSER_PREBUILT_REGEX_OR_HPP
#define PARSER_PREBUILT_REGEX_OR_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class alternation : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier     = "|";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit alternation(const std::string&): node(identifier, type, operands_order)
            {
            }

            inline bool compute(std::string& expression) override
            {
                auto expression_backup = expression;

                if (this->children[0]->compute(expression))
                {
                    return true;
                }

                expression = expression_backup;

                if (this->children[1]->compute(expression))
                {
                    return true;
                }

                expression = expression_backup;
                return false;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_OR_HPP
