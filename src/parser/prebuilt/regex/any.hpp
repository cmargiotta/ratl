#ifndef PARSER_PREBUILT_REGEX_ANY_HPP
#define PARSER_PREBUILT_REGEX_ANY_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class any : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier = ".";
            static const inline auto        type       = node::type::LEAF;

        public:
            inline explicit any(const std::string&): node(identifier, type)
            {
            }

            inline bool compute(std::string& expression) override
            {
                if (expression.empty())
                {
                    return false;
                }

                char to_match = expression[0];
                expression    = expression.substr(1);

                return (to_match != '\r' && to_match != '\n');
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ANY_HPP
