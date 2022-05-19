#ifndef CONCEPTS_ITERATOR_HPP
#define CONCEPTS_ITERATOR_HPP

namespace ratl
{
    template<typename T>
    concept iterator = requires(T i)
    {
        i++;
        ++i;

        i < i;
        i <= i;
        i > i;
        i >= i;
        i == i;
        i != i;

        *i;
    };
}// namespace ratl

#endif// CONCEPTS_ITERATOR_HPP
