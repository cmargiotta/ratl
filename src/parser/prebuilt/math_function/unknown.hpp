#ifndef PARSER_PREBUILT_MATH_FUNCTION_UNKNOWN_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_UNKNOWN_HPP

#include <cstdint>
#include <string>

#include <parser/prebuilt/math_function/base_node.hpp>

namespace ratl::math_function
{
    class unknown : public base_node
    {
        private:
            using node = base_node::node;
            const std::string name;

            inline std::string to_string_() override
            {
                return name;
            }

        public:
            static const inline std::string identifier = "a-z";
            static const inline auto        type       = node::type::LEAF;

        public:
            inline explicit unknown(const std::string& token)
                : base_node(identifier, type), name(token)
            {
            }

            inline ratl::math::fraction<int>
                compute(std::unordered_map<std::string, ratl::math::fraction<int>>& input) override
            {
                return input.at(name);
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_UNKNOWN_HPP
