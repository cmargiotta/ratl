#ifndef PARSER_PREBUILT_REGEX_SQUARE_PAR_OPEN_HPP
#define PARSER_PREBUILT_REGEX_SQUARE_PAR_OPEN_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class square_par_open : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier     = "[";
            static const inline size_t      priority       = 0;
            static const inline auto        type           = node::type::DELIMITER_START;
            static const inline auto        operands_order = node::operands_order::LEFT;

        public:
            inline explicit square_par_open(const std::string&)
                : node(identifier, priority, type, operands_order)
            {
            }

            inline bool compute(std::string& expression) override
            {
                if (expression.empty())
                {
                    return false;
                }

                for (auto& child: this->children)
                {
                    auto expression_copy = expression;
                    if (child->compute(expression_copy))
                    {
                        expression = expression_copy;
                        return true;
                    }
                }

                return false;
            }

            inline std::string to_string() override
            {
                std::string result = "[";

                for (auto& child: this->children)
                {
                    result += child->to_string();
                }

                result += "]";

                return result;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_SQUARE_PAR_OPEN_HPP
