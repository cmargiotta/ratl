#ifndef PARSE_TREE_PARSER_HPP
#define PARSE_TREE_PARSER_HPP

#include <array>
#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <stack>
#include <stdexcept>
#include <unordered_map>

#include "parse_node.hpp"

namespace ratl
{
    template<class Tokenizer, class Root, class... Nodes>
    class parser
    {
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
                std::conjunction_v<std::is_same<typename Root::ResultType, typename Nodes::ResultType>...>,
                "Every node has the same result type");

            static_assert(std::conjunction_v<std::is_same<typename Root::ExpectedInputType,
                                                          typename Nodes::ExpectedInputType>...>,
                          "Every node has the same identifier type");

            static_assert(std::conjunction_v<std::is_base_of<node, Root>, std::is_base_of<node, Nodes>...>,
                          "Every node is based on parse_node");

        private:
            Tokenizer tokenizer {Nodes::identifier...};
            static const inline std::unordered_map<std::string,
                                                   std::function<std::unique_ptr<node>(const std::string&)>>
                nodes = {{Nodes::identifier,
                          [](const std::string& token) -> std::unique_ptr<node>
                          {
                              return std::make_unique<Nodes>(token);
                          }}...};

        private:
            void build_tree(std::unique_ptr<node>& last, std::deque<std::unique_ptr<node>>& parsed)
            {
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

                std::deque<std::unique_ptr<node>>                    output;
                std::stack<std::pair<std::unique_ptr<node>, size_t>> operators;

                for (const auto& token: tokens)
                {
                    auto node_ = nodes.at(token.second)(token.first);

                    switch (node_->get_type())
                    {
                        case (node::type::LEAF):
                            output.push_back(std::move(node_));
                            break;
                        case (node::type::DELIMITER_START):
                            operators.push(std::make_pair(std::move(node_), 0));
                            output.push_back(nodes.at(token.second)(token.first));
                            break;
                        case (node::type::DELIMITER_END):
                            while (operators.top().first->get_type() != node::type::DELIMITER_START)
                            {
                                if (operators.empty())
                                {
                                    throw std::runtime_error("Invalid expression");
                                }

                                output.push_back(std::move(operators.top().first));
                                operators.pop();
                            }

                            output.push_back(std::move(node_));

                            operators.pop();// Popping delimiter start
                            break;
                        case (node::type::OPERATOR):
                        {
                            auto priority = node_->get_priority();

                            switch (node_->get_operands_order())
                            {
                                case node::operands_order::LEFT:
                                    output.push_back(std::move(node_));
                                    break;

                                default:
                                    while (!operators.empty()
                                           && operators.top().first->get_type() != node::type::DELIMITER_START
                                           && operators.top().second >= priority)
                                    {
                                        output.push_back(std::move(operators.top().first));
                                        operators.pop();
                                    }

                                    operators.push(std::make_pair(std::move(node_), priority));

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
                        output.push_back(std::move(operators.top().first));
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
}// namespace ratl

#endif// PARSE_TREE_PARSER_HPP
