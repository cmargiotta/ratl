#ifndef PARSER_PREBUILT_DICE_ROLLER_DICE_HPP
#define PARSER_PREBUILT_DICE_ROLLER_DICE_HPP

#include <cstdint>
#include <ctime>
#include <random>
#include <string>

#include <parser/parse_node.hpp>

namespace ratl::dice_roller
{
    class dice : public ratl::parse_node<int, void>
    {
        private:
            using node = ratl::parse_node<int, void>;
            std::mt19937 random_generator;

        public:
            static const inline std::string identifier     = "d";
            static const inline auto        type           = node::type::OPERATOR;
            static const inline auto        operands_order = node::operands_order::LEFT_RIGHT;

        public:
            inline explicit dice(const std::string&): node(identifier, type, operands_order)
            {
                random_generator.seed(std::time(nullptr));
            }

            inline int compute() override
            {
                std::uniform_int_distribution<int> distribution(1, children[1]->compute());
                return children[0]->compute() * distribution(random_generator);
            }
    };
}// namespace ratl::dice_roller

#endif// PARSER_PREBUILT_DICE_ROLLER_DICE_HPP
