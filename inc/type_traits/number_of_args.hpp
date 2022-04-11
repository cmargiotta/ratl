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

	template<typename Signature>
	struct number_of_args<Signature*>
	{
			static constexpr auto value = number_of_args<Signature>::value;
	};

	template<typename Signature>
	static constexpr auto number_of_args_v = number_of_args<Signature>::value;
}// namespace ratl

#endif// TYPE_TRAITS_NUMBER_OF_ARGS_HPP
