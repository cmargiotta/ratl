#ifndef PARSER_PREBUILT_REGEX_ROOT_HPP
#define PARSER_PREBUILT_REGEX_ROOT_HPP

#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class root : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

        public:
            root(): node("", node::type::ROOT, node::operands_order::ROOT)
            {
            }

            bool compute(ExpectedInputType& expr) override
            {
                bool result = true;

                for (auto& child: this->children)
                {
                    result = result && child->compute(expr);
                }

                return result;
            }

            bool is_exact_matcher()
            {
                for (auto& child: this->children)
                {
                    if (child->get_type() != node::type::LEAF)
                    {
                        return false;
                    }
                }

                return true;
            }

            inline root& operator+=(std::unique_ptr<root>&& other)
            {
                merge(std::move(other));
                return *this;
            }

            void merge(std::unique_ptr<root>&& other);
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_ROOT_HPP
