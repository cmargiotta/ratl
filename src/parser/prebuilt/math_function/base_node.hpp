#ifndef PARSER_PREBUILT_MATH_FUNCTION_BASE_MATH_NODE_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_BASE_MATH_NODE_HPP

#include <algorithm>
#include <string>
#include <unordered_map>

#include <math/fraction.hpp>
#include <parser/parse_node.hpp>
#include <parser/prebuilt/math_function/base_node.hpp>
#include <parser/prebuilt/math_function/exceptions.hpp>
#include <parser/prebuilt/math_function/number.hpp>

namespace ratl::math_function
{
    class base_node
        : public ratl::parse_node<ratl::math::fraction<int>,
                                  std::unordered_map<std::string, ratl::math::fraction<int>>>
    {
        public:
            using node = ratl::parse_node<ratl::math::fraction<int>,
                                          std::unordered_map<std::string, ratl::math::fraction<int>>>;

        public:
            base_node(const std::string& id_,
                      type               t = node::type::LEAF,
                      operands_order     o = node::operands_order::LEFT_RIGHT)
                : node(id_, t, o)
            {
            }

            ~base_node() override = default;

            virtual ratl::math::fraction<int> simplify()
            {
                try
                {
                    std::unordered_map<std::string, ratl::math::fraction<int>> arg;
                    ratl::math::fraction<int>                                  value = compute(arg);

                    return value;
                }
                catch (...)
                {
                    auto children = std::move(this->children);
                    while (!children.empty())
                    {
                        try
                        {
                            auto value = dynamic_cast<base_node&>(*children.back()).simplify();

                            add_child(std::make_unique<number>(value));
                        }
                        catch (not_simplifiable&)
                        {
                            add_child(std::move(children.back()));
                        }

                        children.pop_back();
                    }
                }

                throw(not_simplifiable());
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_BASE_MATH_NODE_HPP
