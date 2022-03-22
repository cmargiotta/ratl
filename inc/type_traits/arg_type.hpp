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
	struct arg_type<n, Ret(Arg, Args...)>
	{
			using type = typename arg_type<n - 1, Ret(Args...)>::type;
	};

	template<std::size_t n, typename Signature>
	struct arg_type<n, std::function<Signature>>
	{
			using type = typename arg_type<n, Signature>::type;
	};

	template<std::size_t n, typename Signature>
	using arg_type_t = typename arg_type<n, Signature>::type;

	static_assert(std::is_same<arg_type_t<0, int()>, void>::value,
				  "First argument of a int() function is void");
	static_assert(std::is_same<arg_type_t<0, int(int)>, int>::value,
				  "First argument of a int(int) function is int");
	static_assert(std::is_same<arg_type_t<1, int(char, int)>, int>::value,
				  "Second argument of a int(char, int) function is int");
	static_assert(std::is_same<arg_type_t<1, std::function<int(char, int)>>, int>::value,
				  "Second argument of a std::function<int(char, int)> is int");

}// namespace ratl

#endif// TYPE_TRAITS_ARG_TYPE_HPP
