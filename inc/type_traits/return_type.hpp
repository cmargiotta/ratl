#ifndef TYPE_TRAITS_RETURN_TYPE_HPP
#define TYPE_TRAITS_RETURN_TYPE_HPP

#include <functional>
#include <type_traits>

namespace ratl
{
	/**
	 * @brief Extract return type from a function signature
	 *
	 * @tparam Signature
	 */
	template<typename>
	struct return_type;

	template<typename Ret, typename... Args>
	struct return_type<Ret(Args...)>
	{
			using type = Ret;
	};

	template<typename Signature>
	struct return_type<std::function<Signature>>
	{
			using type = typename return_type<Signature>::type;
	};

	template<typename Signature>
	using return_type_t = typename return_type<Signature>::type;

	static_assert(std::is_same<return_type_t<int(int, char)>, int>::value,
				  "Return type of int(int, char) is int");
	static_assert(std::is_same<return_type_t<std::function<int(int, char)>>, int>::value,
				  "Return type of std::function<int(int, char)> is int");
}// namespace ratl

#endif// TYPE_TRAITS_RETURN_TYPE_HPP
