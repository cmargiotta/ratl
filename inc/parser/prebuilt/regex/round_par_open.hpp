#ifndef PARSER_PREBUILT_REGEX_ROUND_PAR_OPEN_HPP
#define PARSER_PREBUILT_REGEX_ROUND_PAR_OPEN_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class round_par_open : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

            std::string current;

        public:
            static const inline std::string identifier     = "(";
            static const inline size_t      priority       = 0;
            static const inline auto        type           = node::type::DELIMITER_START;
            static const inline auto        operands_order = node::operands_order::LEFT;

        public:
            inline explicit round_par_open(const std::string& str)
                : node(identifier, priority, type, operands_order), current(str)
            {
            }

            inline bool compute(std::string& expression) override
            {
                if (expression.empty())
                {
                    return false;
                }

                bool result = true;

                for (auto& child: this->children)
                {
                    result = result && child->compute(expression);
                }

                result += ")";

                return result;
            }

            inline std::string to_string() override
            {
                return current;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ROUND_PAR_OPEN_HPP
