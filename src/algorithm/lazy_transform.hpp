#ifndef ALGORITHM_LAZY_TRANSFORM_HPP
#define ALGORITHM_LAZY_TRANSFORM_HPP

#include <functional>
#include <vector>

#include <concepts.hpp>

namespace ratl
{
    template<ratl::iterator T>
    class lazy_iterator
    {
        public:
            using Type = std::decay_t<decltype(*std::declval<T>())>;

        private:
            std::vector<bool>          already_completed;
            T                          begin;
            T                          data;
            std::function<Type(Type&)> operation;

        public:
            lazy_iterator(T begin_, T end, const std::function<Type(Type&)>& op)
                : already_completed(end - begin_, false), begin(begin_), data(begin), operation(op)
            {
            }

            inline lazy_iterator& operator*()
            {
                *data = operation(*data);

                return *this;
            }

            inline lazy_iterator& operator++()
            {
                data++;

                return *this;
            }
    };

    template<ratl::iterator T>
    inline auto lazy_transform(
        T begin,
        T end,
        const std::function<std::decay_t<decltype(*std::declval<T>())>(decltype(*std::declval<T>())&)>& operation)
    {
        return lazy_iterator(begin, end, operation);
    }
}// namespace ratl

#endif// ALGORITHM_LAZY_TRANSFORM_HPP
