#ifndef PARSE_TREE_TOKENIZERS_exact_string_tokenizer_HPP
#define PARSE_TREE_TOKENIZERS_exact_string_tokenizer_HPP

#include <initializer_list>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace ratl::tokenizer
{
    /**
     * @brief Supported identifiers: comma separated list of values
     *
     */
    class exact_string_tokenizer
    {
        private:
            std::unordered_map<std::string, std::string> identifiers;

        public:
            using ParsedType = std::string;

        public:
            exact_string_tokenizer(std::initializer_list<std::string> ids)
            {
                for (const auto& id_list: ids)
                {
                    std::stringstream ss(id_list);
                    std::string       id;
                    while (getline(ss, id, ','))
                    {
                        identifiers[id] = id_list;
                    }
                }
            }

            template<typename Iterator>
            std::vector<std::pair<std::string, std::string>> operator()(Iterator begin, Iterator end)
            {
                std::vector<std::pair<std::string, std::string>> result;
                result.reserve(end - begin);

                for (auto i = begin; i < end; ++i)
                {
                    bool        found = false;
                    std::string value;

                    for (auto j = i; j < end; ++j)
                    {
                        value += *j;

                        if (identifiers.contains(value))
                        {
                            result.emplace_back(std::make_pair(value, identifiers.at(value)));
                            found = true;
                            i     = j;
                            break;
                        }
                    }

                    if (!found)
                    {
                        throw std::runtime_error("Unexpected identifier");
                    }
                }

                return result;
            }
    };
}// namespace ratl::tokenizer

#endif// PARSE_TREE_TOKENIZERS_exact_string_tokenizer_HPP
