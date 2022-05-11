#ifndef PARSE_TREE_PARSE_NODE_HPP
#define PARSE_TREE_PARSE_NODE_HPP

#include <algorithm>
#include <deque>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace ratl
{
    namespace _private_
    {
        template<typename R, typename I>
        class compute_specialized
        {
            public:
                virtual ~compute_specialized()                    = default;
                virtual R compute(std::add_lvalue_reference_t<I>) = 0;
        };

        template<typename R>
        class compute_specialized<R, void>
        {
            public:
                virtual ~compute_specialized() = default;
                virtual R compute()            = 0;
        };
    }// namespace _private_

    template<typename ResultType_ = int, typename ExpectedInputType_ = std::string>
    class parse_node : public _private_::compute_specialized<ResultType_, ExpectedInputType_>
    {
        public:
            using ResultType        = ResultType_;
            using ExpectedInputType = ExpectedInputType_;

            enum class type : char
            {
                LEAF,
                DELIMITER_START,
                DELIMITER_END,
                OPERATOR,
                ROOT
            };

            enum class operands_order : char
            {
                LEFT,      // Assuming operands = 1
                RIGHT,     // Assuming operands = 1
                LEFT_RIGHT,// Assuming operands = 2
                ROOT
            };

        protected:
            virtual std::string to_string_()
            {
                return identifier;
            }

            std::deque<std::unique_ptr<parse_node<ResultType, ExpectedInputType>>> children;

        private:
            const std::string    identifier;
            const type           type_;
            const operands_order operands_order_;

        public:
            parse_node(const std::string& id_,
                       type               t = type::LEAF,
                       operands_order     o = operands_order::LEFT_RIGHT)
                : identifier(id_), type_(t), operands_order_(o)
            {
            }

            parse_node(const parse_node& other)     = default;
            parse_node(parse_node&& other) noexcept = default;
            parse_node& operator=(const parse_node& other) = default;
            parse_node& operator=(parse_node&& other) noexcept = default;

            virtual ~parse_node() = default;

            inline std::string get_identifier() const
            {
                return identifier;
            }

            inline size_t get_operands() const
            {
                if (operands_order_ == operands_order::LEFT_RIGHT)
                {
                    return 2;
                }

                return 1;
            }

            inline operands_order get_operands_order() const
            {
                return operands_order_;
            }

            inline type get_type() const
            {
                return type_;
            }

            inline void add_child(std::unique_ptr<parse_node<ResultType, ExpectedInputType>> child)
            {
                if (type_ != type::ROOT && type_ != type::DELIMITER_START
                    && (children.size() + 1) > get_operands())
                {
                    throw std::runtime_error("Operands number exceeded");
                }

                children.emplace_front(std::move(child));
            }

            inline std::string to_string(bool recursive)
            {
                if (!recursive)
                {
                    return to_string();
                }

                return to_string_();
            }

            inline virtual std::string to_string()
            {
                if (children.empty())
                {
                    return to_string_();
                }

                std::string result;

                if (type_ == type::LEAF || type_ == type::DELIMITER_END)
                {
                    result += to_string_();
                }
                else if (type_ == type::DELIMITER_START)
                {
                    result += to_string_();
                    result += children[0]->to_string();
                    result += children[1]->to_string();
                }
                else
                {
                    switch (operands_order_)
                    {
                        case operands_order::LEFT:
                            result += children[0]->to_string();
                            result += to_string_();
                            break;

                        case operands_order::RIGHT:
                            result += to_string_();
                            result += children[0]->to_string();
                            break;

                        case operands_order::LEFT_RIGHT:
                            result += children[0]->to_string();
                            result += to_string_();
                            result += children[1]->to_string();
                            break;

                        case operands_order::ROOT:
                            for (auto& child: children)
                            {
                                result += child->to_string();
                            }
                            break;
                    }
                }

                return result;
            }
    };

}// namespace ratl

#endif// PARSE_TREE_PARSE_NODE_HPP
