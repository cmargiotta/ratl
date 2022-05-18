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

            std::string to_string_() override
            {
                return "+";
            }

            ratl::math::fraction<int> pre_computed_result;

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
                try
                {
                    // If the child is simplifiable, accumulate it in precomputed result
                    pre_computed_result += dynamic_cast<base_node&>(*child).simplify();
                }
                catch (...)
                {
                    auto c = dynamic_cast<plus*>(child.get());

                    if (c != nullptr)
                    {
                        merge(std::move(child));
                    }
                    else
                    {
                        node::add_child(std::move(child));
                    }
                }
            }

            std::string to_string() override
            {
                std::stringstream ss;

                if (pre_computed_result != 0)
                {
                    ss << static_cast<std::string>(pre_computed_result);

                    if (!children.empty())
                    {
                        ss << '+';
                    }
                }

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

                result += pre_computed_result;

                return result;
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_PLUS_HPP
