#ifndef PARSE_TREE_PARSER_HPP
#define PARSE_TREE_PARSER_HPP

#include <array>
#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <stack>
#include <stdexcept>
#include <tuple>
#include <unordered_map>

#include "parse_node.hpp"

namespace ratl
{
    template<class Tokenizer, class Root, class... Nodes_>
    class parser
    {
        public:
            using nodes = std::tuple<Nodes_...>;

        private:
            using ResultType        = typename Root::ResultType;
            using ExpectedInputType = typename Root::ExpectedInputType;

            using node = parse_node<ResultType, ExpectedInputType>;

            static_assert(
                std::is_same_v<std::vector<std::pair<std::string, std::string>>,
                               decltype(std::declval<Tokenizer>()(std::declval<std::string*>(),
                                                                  std::declval<std::string*>()))>,
                "Tokenizer handles the right token type");

            static_assert(
                std::conjunction_v<std::is_same<typename Root::ResultType, typename Nodes_::ResultType>...>,
                "Every node has the same result type");

            static_assert(std::conjunction_v<std::is_same<typename Root::ExpectedInputType,
                                                          typename Nodes_::ExpectedInputType>...>,
                          "Every node has the same identifier type");

            static_assert(std::conjunction_v<std::is_base_of<node, Root>, std::is_base_of<node, Nodes_>...>,
                          "Every node is based on parse_node");

        private:
            Tokenizer tokenizer {Nodes_::identifier...};
            static const inline std::unordered_map<std::string,
                                                   std::function<std::unique_ptr<node>(const std::string&)>>
                nodes_map = {{Nodes_::identifier,
                              [](const std::string& token) -> std::unique_ptr<node>
                              {
                                  return std::make_unique<Nodes_>(token);
                              }}...};

        private:
            void build_tree(std::unique_ptr<node>& last, std::deque<std::unique_ptr<node>>& parsed)
            {
                auto i = last->to_string(false);

                if (last->get_type() == node::type::LEAF)
                {
                    return;
                }

                if (parsed.empty())
                {
                    return;
                }

                if (last->get_type() == node::type::ROOT)
                {
                    while (!parsed.empty())
                    {
                        auto node = std::move(parsed.back());
                        parsed.pop_back();
                        build_tree(node, parsed);
                        last->add_child(std::move(node));
                    }
                }
                else if (last->get_type() == node::type::DELIMITER_END)
                {
                    std::list<std::unique_ptr<node>> children;

                    while (!parsed.empty() && parsed.back()->get_type() != node::type::DELIMITER_START)
                    {
                        // Accumulating children until the right delimiter_start is found
                        auto node = std::move(parsed.back());
                        parsed.pop_back();
                        build_tree(node, parsed);

                        children.emplace_back(std::move(node));
                    }

                    if (parsed.empty())
                    {
                        throw std::runtime_error("Invalid expression");
                    }

                    auto delimiter_start = std::move(parsed.back());
                    parsed.pop_back();

                    for (auto& child: children)
                    {
                        delimiter_start->add_child(std::move(child));
                    }

                    last = std::move(delimiter_start);
                }
                else
                {
                    for (size_t i = 0; i < last->get_operands(); ++i)
                    {
                        auto node_ = std::move(parsed.back());
                        parsed.pop_back();
                        build_tree(node_, parsed);
                        last->add_child(std::move(node_));
                    }
                }
            }

        public:
            template<typename T>
            std::unique_ptr<node> operator()(T expression)
            {
                return operator()(expression.begin(), expression.end());
            }

            template<typename Iterator>
            std::unique_ptr<Root> operator()(Iterator begin, Iterator end)
            {
                // Stunting yard algorithm
                auto tokens = tokenizer(begin, end);

                std::deque<std::unique_ptr<node>> output;
                std::stack<std::unique_ptr<node>> operators;

                for (const auto& token: tokens)
                {
                    auto node_ = nodes_map.at(token.second)(token.first);

                    switch (node_->get_type())
                    {
                        case (node::type::LEAF):
                            output.push_back(std::move(node_));
                            break;
                        case (node::type::DELIMITER_START):
                            operators.push(std::move(node_));
                            output.push_back(nodes_map.at(token.second)(token.first));
                            break;
                        case (node::type::DELIMITER_END):
                            while (operators.top()->get_type() != node::type::DELIMITER_START)
                            {
                                if (operators.empty())
                                {
                                    throw std::runtime_error("Invalid expression");
                                }

                                output.push_back(std::move(operators.top()));
                                operators.pop();
                            }

                            output.push_back(std::move(node_));

                            operators.pop();// Popping delimiter start
                            break;
                        case (node::type::OPERATOR):
                        {
                            switch (node_->get_operands_order())
                            {
                                case node::operands_order::LEFT:
                                    output.push_back(std::move(node_));
                                    break;

                                default:
                                    while (!operators.empty()
                                           && operators.top()->get_type() != node::type::DELIMITER_START)
                                    {
                                        output.push_back(std::move(operators.top()));
                                        operators.pop();
                                    }

                                    operators.push(std::move(node_));

                                    break;
                            }
                        }
                        default:
                            break;
                    }
                }

                if (!operators.empty())
                {
                    if (operators.size() == 1)
                    {
                        output.push_back(std::move(operators.top()));
                        operators.pop();
                    }
                    else
                    {
                        throw std::runtime_error("Invalid expression");
                    }
                }

                std::unique_ptr<node> root_ = std::make_unique<Root>();
                build_tree(root_, output);

                return std::unique_ptr<Root>(dynamic_cast<Root*>(root_.release()));
            }
    };

    template<class Tokenizer, class Root, class... Nodes, class... Nodes1>
    class parser<Tokenizer, Root, std::tuple<Nodes...>, Nodes1...>
        : public parser<Tokenizer, Root, Nodes..., Nodes1...>
    {
    };
}// namespace ratl

#endif// PARSE_TREE_PARSER_HPP
