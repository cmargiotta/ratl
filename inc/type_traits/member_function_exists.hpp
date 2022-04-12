#ifndef TYPE_TRAITS_MEMBER_FUNCTION_EXISTS_HPP
#define TYPE_TRAITS_MEMBER_FUNCTION_EXISTS_HPP

#include <type_traits>

#define MAKE_EXISTENCE_VERIFIER(member)                                                            \
    namespace ratl                                                                                 \
    {                                                                                              \
        template<typename, typename = void>                                                        \
        struct has_##member : std::false_type                                                      \
        {                                                                                          \
        };                                                                                         \
        template<typename Type>                                                                    \
        struct has_##member<Type, decltype(Type::member, void())> : std::true_type                 \
        {                                                                                          \
        };                                                                                         \
        template<typename Type>                                                                    \
        static constexpr bool has_##member##_v = has_##member<Type>::value;                        \
    }

#endif// TYPE_TRAITS_MEMBER_FUNCTION_EXISTS_HPP
