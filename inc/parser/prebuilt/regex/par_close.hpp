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
            static const inline std::string identifier = "),]";
            static const inline auto        type       = node::type::DELIMITER_END;

        public:
            inline explicit par_close(const std::string&): node(identifier, type)
            {
            }

            inline bool compute(std::string& expression) override
            {
                return true;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ROUND_PAR_CLOSE_HPP
