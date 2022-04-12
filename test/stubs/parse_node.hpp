#ifndef STUBS_PARSE_NODE_HPP
#define STUBS_PARSE_NODE_HPP

#include "parser/parse_node.hpp"

class node : public ratl::parse_node<int, char>
{
        using base = ratl::parse_node<int, char>;

    public:
        static const inline char identifier = 'a';

        inline node(): base(identifier, 0, 0, base::type::LEAF)
        {
        }

    private:
        inline int compute_(const std::vector<int>& data) override
        {
            return 0;
        }
};

#endif// STUBS_PARSE_NODE_HPP
