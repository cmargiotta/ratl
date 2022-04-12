#ifndef PARSE_TREE_TOKENIZERS_EXACT_TOKENIZER_HPP
#define PARSE_TREE_TOKENIZERS_EXACT_TOKENIZER_HPP

#include <initializer_list>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace ratl::tokenizer
{
    template<typename Token>
    class exact_tokenizer
    {
        private:
            std::set<Token> identifiers;
        public:
            using ParsedType = Token;

        public:
            exact_tokenizer(std::initializer_list<Token> ids): identifiers(ids)
            {
            }

            template<typename Iterator>
            auto operator()(Iterator begin, Iterator end)
            {
                std::vector<std::decay_t<decltype(*std::declval<Iterator>())>> tokens;
                tokens.reserve(end - begin);

                for (auto i = begin; i < end; ++i)
                {
                    if (!identifiers.contains(*i))
                    {
                        throw std::runtime_error("Unexpected identifier");
                    }

                    tokens.push_back(*i);
                }

                return tokens;
            }
    };
}// namespace ratl::tokenizer

#endif// PARSE_TREE_TOKENIZERS_EXACT_TOKENIZER_HPP
