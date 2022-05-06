#ifndef PARSER_PREBUILT_REGEX_STAR_HPP
#define PARSER_PREBUILT_REGEX_STAR_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class star : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier     = "*";
            static const inline size_t      priority       = 0;
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT;

        public:
            inline explicit star(const std::string&)
                : node(identifier, priority, type, operands_order)
            {
            }

            inline bool compute(std::string& expression) override
            {
                while (!expression.empty() && children.back()->compute(expression))
                    ;

                return true;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_STAR_HPP
