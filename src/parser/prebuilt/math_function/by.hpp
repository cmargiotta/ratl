#ifndef PARSER_PREBUILT_MATH_FUNCTION_BY_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_BY_HPP

#include <cstdint>
#include <sstream>
#include <string>

#include <parser/prebuilt/math_function/base_node.hpp>
#include <parser/prebuilt/math_function/number.hpp>
#include <parser/prebuilt/math_function/unknown.hpp>

namespace ratl::math_function
{
    class by : public base_node
    {
        private:
            using node = base_node::node;

        private:
            std::string to_string_() override
            {
                return "*";
            }

            ratl::math::fraction<int> pre_computed_result;

        public:
            static const inline std::string identifier     = "\\*";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit by(const std::string& = std::string())
                : base_node(identifier, type, operands_order), pre_computed_result(1)
            {
            }

            inline ratl::math::fraction<int>
                compute(std::unordered_map<std::string, ratl::math::fraction<int>>& input) override
            {
                ratl::math::fraction<int> result = pre_computed_result;

                for (auto& child: children)
                {
                    result = result * child->compute(input);
                }

                return result;
            }

            inline void add_child(std::unique_ptr<node> child) override
            {
                try
                {
                    // If the child is simplifiable, accumulate it in precomputed result
                    pre_computed_result *= dynamic_cast<base_node&>(*child).simplify();
                }
                catch (...)
                {
                    auto* c = dynamic_cast<by*>(child.get());

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

            inline std::string to_string() override
            {
                std::stringstream ss;

                if (pre_computed_result != 0)
                {
                    ss << static_cast<std::string>(pre_computed_result);

                    if (!children.empty())
                    {
                        auto* test1 = dynamic_cast<unknown*>(children.begin()->get());

                        if (test1 == nullptr
                            && children.front()->get_type() != node::type::DELIMITER_START)
                        {
                            ss << '*';
                        }
                    }
                }

                for (auto child = children.begin(); child < children.end(); ++child)
                {
                    ss << (*child)->to_string();
                    auto s = ss.str();

                    if (children.end() - child > 1)
                    {
                        auto  s1    = (*(child + 1))->to_string();
                        auto* test1 = dynamic_cast<unknown*>(child->get());
                        auto* test2 = dynamic_cast<unknown*>((child + 1)->get());

                        if (test1 == nullptr && test2 == nullptr)
                        {
                            // No unknowns
                            ss << '*';
                        }
                        else if (test1 != nullptr ^ test2 != nullptr)
                        {
                            // Only one unknown
                            auto* test1 = dynamic_cast<number*>(child->get());
                            auto* test2 = dynamic_cast<number*>((child + 1)->get());

                            if (test1 == nullptr && test2 == nullptr)
                            {
                                // No unknowns
                                ss << '*';
                            }
                        }
                    }
                }

                return ss.str();
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_BY_HPP
