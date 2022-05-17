#ifndef TYPE_TRAITS_MEMBER_FUNCTION_EXISTS_HPP
#define TYPE_TRAITS_MEMBER_FUNCTION_EXISTS_HPP

#include <type_traits>

#define MAKE_EXISTENCE_VERIFIER(member)                                                            \
    namespace ratl                                                                                 \
    {                                                                                              \
        template<typename Type>                                                                    \
        concept with_##member = requires                                                           \
        {                                                                                          \
            Type::member;                                                                          \
        };                                                                                         \
    }

#endif// TYPE_TRAITS_MEMBER_FUNCTION_EXISTS_HPP
