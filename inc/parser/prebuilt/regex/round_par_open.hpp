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
            static const inline std::string identifier = "(";
            static const inline auto        type       = node::type::DELIMITER_START;

        public:
            inline explicit round_par_open(const std::string& str)
                : node(identifier, type), current(str)
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

                return result;
            }

            inline std::string to_string() override
            {
                std::string result = "(";

                for (auto& child: this->children)
                {
                    result += child->to_string();
                }

                result += ")";

                return result;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ROUND_PAR_OPEN_HPP
