#ifndef PARSE_TREE_PARSER_HPP
#define PARSE_TREE_PARSER_HPP

#include <array>
#include <functional>
#include <memory>
#include <stack>
#include <stdexcept>
#include <unordered_map>

#include "parse_node.hpp"

namespace ratl
{
    template<class Tokenizer, class Node, class... Nodes>
    class parser
    {
            using ResultType = typename Node::ResultType;
            using TokenType  = typename Node::IdentifierType;

            using node = parse_node<ResultType, TokenType>;

            static_assert(std::is_same_v<std::vector<TokenType>,
                                         decltype(std::declval<Tokenizer>()(
                                             std::declval<TokenType*>(), std::declval<TokenType*>()))>,
                          "Tokenizer handles the right token type");

            static_assert(
                std::conjunction_v<std::is_same<typename Node::ResultType, typename Nodes::ResultType>...>,
                "Every node has the same result type");

            static_assert(
                std::conjunction_v<std::is_same<typename Node::TokenType, typename Nodes::TokenType>...>,
                "Every node has the same identifier type");

            static_assert(std::conjunction_v<std::is_base_of<node, Node>, std::is_base_of<node, Nodes>...>,
                          "Every node is based on parse_node");

        private:
            Tokenizer tokenizer {Node::identifier, Nodes::identifier...};
            static const inline std::unordered_map<TokenType, std::function<std::unique_ptr<node>()>> nodes
                = {{Node::identifier,
                    []() -> std::unique_ptr<node>
                    {
                        return std::make_unique<Node>();
                    }},
                   {Nodes::identifier,
                    []() -> std::unique_ptr<node>
                    {
                        return std::make_unique<Nodes>();
                    }}...};

        private:
            std::unique_ptr<node> build_tree(std::stack<std::unique_ptr<node>>& parsed)
            {
                auto node = std::move(parsed.top());
                parsed.pop();

                if (node->get_type() != node::type::LEAF)
                {
                    for (size_t i = 0; i < node->get_operands(); ++i)
                    {
                        node->add_child(std::move(build_tree(parsed)));
                    }
                }

                return node;
            }

        public:
            template<typename Iterator>
            std::unique_ptr<node> operator()(Iterator begin, Iterator end)
            {
                // Stunting yard algorithm
                auto tokens = tokenizer(begin, end);

                std::stack<std::unique_ptr<node>>                    output;
                std::stack<std::pair<std::unique_ptr<node>, size_t>> operators;

                for (const auto& token: tokens)
                {
                    auto node_ = nodes.at(token)();

                    switch (node_->get_type())
                    {
                        case (node::type::LEAF):
                            output.push(std::move(node_));
                            break;
                        case (node::type::DELIMITER_START):
                            operators.push(std::make_pair(std::move(node_), 0));
                            break;
                        case (node::type::DELIMITER_END):
                            while (operators.top().first->get_type() != node::type::DELIMITER_START)
                            {
                                if (operators.empty())
                                {
                                    throw std::runtime_error("Invalid expression");
                                }

                                output.push(std::move(operators.top().first));
                                operators.pop();
                            }

                            operators.pop();// Popping delimiter start
                            break;
                        case (node::type::OPERATOR):
                        {
                            auto priority = node_->get_priority();

                            while (operators.top().first->get_type() != node::type::DELIMITER_START
                                   && operators.top().second >= priority)
                            {
                                output.push(std::move(operators.top().first));
                                operators.pop();
                            }

                            operators.push(std::make_pair(std::move(node_), priority));
                        }
                    }
                }

                if (!operators.empty())
                {
                    throw std::runtime_error("Invalid expression");
                }

                return build_tree(output);
            }
    };
}// namespace ratl

#endif// PARSE_TREE_PARSER_HPP
