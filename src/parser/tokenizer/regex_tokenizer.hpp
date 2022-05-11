#ifndef PARSER_TOKENIZER_REGEX_TOKENIZER_HPP
#define PARSER_TOKENIZER_REGEX_TOKENIZER_HPP

#include <algorithm>
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
     */
    class regex_tokenizer
    {
        private:
            std::unordered_map<std::string, ratl::regex_tree> matchers;
            std::unordered_map<std::string, std::string>      exact_matchers;

        public:
            using ParsedType = std::string;

        public:
            regex_tokenizer(std::initializer_list<std::string> ids)
            {
                ratl::regex_parser parser;
                for (const auto& id: ids)
                {
                    auto matcher = parser(id);

                    if (matcher->is_exact_matcher())
                    {
                        std::string value = matcher->to_string();
                        std::string cleaned;
                        for (auto c = value.begin(); c < value.end(); ++c)
                        {
                            if (*c == '\\')
                            {
                                // Backslash found
                                if ((value.end() - c) > 1 && *(c + 1) == '\\')
                                {
                                    cleaned += *c;
                                    c++;
                                    continue;
                                }

                                continue;
                            }

                            cleaned += *c;
                        }

                        exact_matchers[cleaned] = id;
                    }
                    else
                    {
                        matchers[id] = std::move(matcher);
                    }
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
                    std::string value = std::string(begin, end - i);

                    if (value.empty())
                    {
                        throw std::runtime_error("Unexpected identifier");
                    }

                    try
                    {
                        // Trying to find an exact match (O(1))
                        auto match = exact_matchers.at(value);

                        result.emplace_back(std::make_pair(value, match));
                        begin = end - i;
                        i     = 0;
                        continue;
                    }
                    catch (...)
                    {
                        auto match = std::find_if(
                            matchers.begin(),
                            matchers.end(),
                            [&value](const typename decltype(matchers)::value_type& match)
                            {
                                auto value_ = value;
                                return (match.second->compute(value_) && value_.empty());
                            });

                        if (match != matchers.end())
                        {
                            result.emplace_back(std::make_pair(value, match->first));
                            begin = end - i;
                            i     = 0;
                            continue;
                        }
                    }

                    ++i;
                }

                return result;
            }
    };
}// namespace ratl::tokenizer

#endif// PARSER_TOKENIZER_REGEX_TOKENIZER_HPP
