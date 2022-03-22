#ifndef TYPE_TRAITS_NUMBER_OF_ARGS_HPP
#define TYPE_TRAITS_NUMBER_OF_ARGS_HPP

#include <cstdint>
#include <functional>

namespace ratl
{
	/**
	 * @brief Extract the number of arguments of the given function signature
	 *
	 * @tparam Signature
	 */
	template<typename Signature>
	struct number_of_args;

	template<typename Ret, typename... Args>
	struct number_of_args<Ret(Args...)>
	{
			static constexpr std::size_t value = sizeof...(Args);
	};

	template<typename Signature>
	struct number_of_args<std::function<Signature>>
	{
			static constexpr auto value = number_of_args<Signature>::value;
	};

	static_assert(number_of_args<int()>::value == 0, "Number of arguments of int() is 0");
	static_assert(number_of_args<int(int, int)>::value == 2,
				  "Number of arguments of int(int, int) is 2");
	static_assert(number_of_args<std::function<int(int)>>::value == 1,
				  "Number of arguments of std::function<int(int)> is 1");
}// namespace ratl

#endif// TYPE_TRAITS_NUMBER_OF_ARGS_HPP
