#ifndef PARSER_PREBUILT_MATH_FUNCTION_ROOT_HPP
#define PARSER_PREBUILT_MATH_FUNCTION_ROOT_HPP

#include <algorithm>
#include <string>

#include <parser/prebuilt/math_function/base_node.hpp>
#include <parser/prebuilt/math_function/by.hpp>
#include <parser/prebuilt/math_function/exceptions.hpp>

namespace ratl::math_function
{
    class root : public base_node
    {
        private:
            using node = base_node::node;

        public:
            root(): base_node("", node::type::ROOT, node::operands_order::ROOT)
            {
            }

            inline ratl::math::fraction<int>
                compute(std::unordered_map<std::string, ratl::math::fraction<int>>& input) override
            {
                return children[0]->compute(input);
            }

            void add_child(std::unique_ptr<node> child) override
            {
                if (children.empty())
                {
                    auto child = std::make_unique<by>();

                    node::add_child(std::move(child));
                }

                children[0]->add_child(std::move(child));
            }
    };
}// namespace ratl::math_function

#endif// PARSER_PREBUILT_MATH_FUNCTION_ROOT_HPP
