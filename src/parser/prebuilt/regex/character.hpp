#ifndef PARSER_PREBUILT_REGEX_CHARACTER_HPP
#define PARSER_PREBUILT_REGEX_CHARACTER_HPP

#include <cstdint>
#include <string>

#include <parser/parse_node.hpp>

namespace ratl::regex
{
    class character : public ratl::parse_node<bool>
    {
        private:
            using node = ratl::parse_node<bool>;

            std::string matched;

        public:
            static const inline std::string identifier
                = "\\(,\\),\\[,\\],\\?,\\|,\\-,^,\n,\t,\r,1,2,3,4,5,6,7,8,9,0,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, ,\\+,\\*,\\.,/";
            static const inline size_t priority = 0;
            static const inline auto   type     = node::type::LEAF;

        private:
            std::string to_string_() override
            {
                return matched;
            }

        public:
            inline explicit character(const std::string& matched_)
                : node(identifier, type), matched(matched_)
            {
            }

            inline bool compute(std::string& expression) override
            {
                if (expression.empty())
                {
                    return false;
                }

                std::string to_match(expression.begin(), expression.begin() + 1);

                if (to_match.back() == matched.back())
                {
                    expression.erase(0, 1);

                    return true;
                }

                return false;
            }
    };
}// namespace ratl::regex

#endif// PARSER_PREBUILT_REGEX_CHARACTER_HPP
