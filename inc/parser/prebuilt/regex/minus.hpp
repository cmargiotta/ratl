#ifndef PARSER_PREBUILT_REGEX_MINUS_HPP
#define PARSER_PREBUILT_REGEX_MINUS_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class minus : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier     = "-";
            static const inline size_t      priority       = 0;
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit minus(const std::string&)
                : node(identifier, priority, type, operands_order)
            {
            }

            inline bool compute(std::string& expression) override
            {
                char to_match = expression[0];
                expression    = expression.substr(1);

                char range_l = this->children[0]->to_string(false)[0];
                char range_h = this->children[1]->to_string(false)[0];

                return (to_match >= range_l && to_match <= range_h);
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_MINUS_HPP
