#ifndef PARSER_TOKENIZER_REGEX_TOKENIZER_HPP
#define PARSER_TOKENIZER_REGEX_TOKENIZER_HPP

#include <initializer_list>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include <parser/regex.hpp>

namespace ratl::tokenizer
{
    /**
     * @brief Supported identifiers: comma separated list of values
     *
     */
    class regex_tokenizer
    {
        private:
            std::unordered_map<std::string, ratl::regex_tree> matchers;

        public:
            using ParsedType = std::string;

        public:
            regex_tokenizer(std::initializer_list<std::string> ids)
            {
                ratl::regex_parser parser;
                for (const auto& id: ids)
                {
                    matchers[id] = parser(id);
                }
            }

            template<typename Iterator>
            std::vector<std::pair<std::string, std::string>> operator()(Iterator begin, Iterator end)
            {
                std::vector<std::pair<std::string, std::string>> result;
                result.reserve(end - begin);

                size_t i = 0;

                while (begin != end)
                {
                    bool        found = false;
                    std::string value = std::string(begin, end - i);

                    if (value.empty())
                    {
                        throw std::runtime_error("Unexpected identifier");
                    }

                    for (auto& match: matchers)
                    {
                        auto value_copy = value;
                        if (match.second->compute(value_copy) && value_copy.empty())
                        {
                            result.emplace_back(std::make_pair(value, match.first));
                            found = true;
                            begin = end - i;
                            i     = 0;
                            break;
                        }
                    }

                    if (found)
                    {
                        continue;
                    }

                    ++i;
                }

                return result;
            }
    };
}// namespace ratl::tokenizer

#endif// PARSER_TOKENIZER_REGEX_TOKENIZER_HPP
