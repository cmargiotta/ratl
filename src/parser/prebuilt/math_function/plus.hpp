#ifndef PARSER_PREBUILT_MATH_FUNCTION_PLUS_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_PLUS_HPP

#include <cstdint>
#include <sstream>
#include <string>

#include <parser/prebuilt/math_function/base_node.hpp>

namespace ratl::math_function
{
    class plus : public base_node
    {
        private:
            using node = base_node::node;

        private:
            std::string to_string_() override
            {
                return "+";
            }

        public:
            static const inline std::string identifier     = "\\+";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit plus(const std::string&): base_node(identifier, type, operands_order)
            {
            }

            inline void add_child(std::unique_ptr<node> child) override
            {
                auto* c = dynamic_cast<plus*>(child.get());

                if (c != nullptr)
                {
                    merge(std::move(child));
                }
                else
                {
                    node::add_child(std::move(child));
                }
            }

            std::string to_string() override
            {
                std::stringstream ss;
                for (auto o = children.begin(); o < children.end(); ++o)
                {
                    ss << (*o)->to_string();

                    if (children.end() - o > 1)
                    {
                        ss << '+';
                    }
                }

                return ss.str();
            }

            inline ratl::math::fraction<int>
                compute(std::unordered_map<std::string, ratl::math::fraction<int>>& input) override
            {
                ratl::math::fraction<int> result;
                for (auto& child: children)
                {
                    result += child->compute(input);
                }

                return result;
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_PLUS_HPP
