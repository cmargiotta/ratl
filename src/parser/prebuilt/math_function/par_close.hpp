#ifndef PARSER_PREBUILT_MATH_FUNCTION_PAR_CLOSE_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_PAR_CLOSE_HPP

#include <cstdint>
#include <string>

#include <parser/prebuilt/math_function/base_node.hpp>

namespace ratl::math_function
{
    class par_close : public base_node
    {
        private:
            using node = base_node::node;

        private:
            std::string to_string_() override
            {
                return ")";
            }

        public:
            static const inline std::string identifier = "\\)";
            static const inline auto        type       = node::type::DELIMITER_END;

        public:
            inline explicit par_close(const std::string&): base_node(identifier, type)
            {
            }

            inline ratl::math::fraction<int>
                compute(std::unordered_map<std::string, ratl::math::fraction<int>>&) override
            {
                return ratl::math::fraction<int>();
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_PAR_CLOSE_HPP
