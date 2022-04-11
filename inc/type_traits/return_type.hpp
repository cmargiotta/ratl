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
	struct return_type<std::function<Signature>> : return_type<Signature>
	{
	};

	template<typename Signature>
	struct return_type<Signature*> : return_type<Signature>
	{
	};

	template<typename Signature>
	using return_type_t = typename return_type<Signature>::type;
}// namespace ratl

#endif// TYPE_TRAITS_RETURN_TYPE_HPP
