#ifndef TYPE_TRAITS_NUMBER_OF_ARGS_HPP
#define TYPE_TRAITS_NUMBER_OF_ARGS_HPP

#include <cstdint>
#include <functional>
#include <type_traits>

namespace ratl
{
    /**
     * @brief Extract the number of arguments of the given function signature
     *
     * @tparam Signature
     */
    template<typename Signature>
    struct number_of_args : std::integral_constant<std::size_t, 0>
    {
    };

    template<typename Ret, typename... Args>
    struct number_of_args<Ret(Args...)> : std::integral_constant<std::size_t, sizeof...(Args)>
    {
    };

    template<typename Signature>
    struct number_of_args<std::function<Signature>> : number_of_args<Signature>
    {
    };

    template<typename Signature>
    struct number_of_args<Signature*> : number_of_args<Signature>
    {
    };

    template<typename Signature>
    static constexpr auto number_of_args_v = number_of_args<Signature>::value;
}// namespace ratl

#endif// TYPE_TRAITS_NUMBER_OF_ARGS_HPP
