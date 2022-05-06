#ifndef PARSER_PREBUILT_REGEX_ROUND_PAR_CLOSE_HPP
#define PARSER_PREBUILT_REGEX_ROUND_PAR_CLOSE_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class par_close : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            static const inline std::string identifier     = "),]";
            static const inline size_t      priority       = 0;
            static const inline auto        type           = node::type::DELIMITER_END;
            static const inline auto        operands_order = node::operands_order::LEFT;

        public:
            inline explicit par_close(const std::string&)
                : node(identifier, priority, type, operands_order)
            {
            }

            inline bool compute(std::string& expression) override
            {
                return true;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ROUND_PAR_CLOSE_HPP
