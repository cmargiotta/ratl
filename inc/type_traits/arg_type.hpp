#ifndef TYPE_TRAITS_ARG_TYPE_HPP
#define TYPE_TRAITS_ARG_TYPE_HPP

#include <cstdint>
#include <functional>
#include <type_traits>

namespace ratl
{
	/**
	 * @brief Get the nth argument type
	 *
	 * @tparam std::size_t n
	 * @tparam Signature
	 */
	template<std::size_t n, typename Signature>
	struct arg_type;

	template<typename Ret, typename Arg, typename... Args>
	struct arg_type<0, Ret(Arg, Args...)>
	{
			using type = Arg;
	};

	template<typename Ret>
	struct arg_type<0, Ret()>
	{
			using type = void;
	};

	template<std::size_t n, typename Ret, typename Arg, typename... Args>
	struct arg_type<n, Ret(Arg, Args...)> : arg_type<n - 1, Ret(Args...)>
	{
	};

	template<std::size_t n, typename Signature>
	struct arg_type<n, std::function<Signature>> : arg_type<n, Signature>
	{
	};

	template<std::size_t n, typename Signature>
	struct arg_type<n, Signature*> : arg_type<n, Signature>
	{
	};

	template<std::size_t n, typename Signature>
	using arg_type_t = typename arg_type<n, Signature>::type;

}// namespace ratl

#endif// TYPE_TRAITS_ARG_TYPE_HPP
