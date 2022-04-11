#include <catch2/catch.hpp>

#include <type_traits>

#include "type_traits.hpp"

void function1();
int	 function2(int, int);

struct A
{
		int b;
};

MAKE_EXISTANCE_VERIFIER(b)

TEST_CASE("Function traits work correctly", "[traits]")
{
	REQUIRE(std::is_same_v<ratl::arg_type_t<0, decltype(function1)>, void>);
	REQUIRE(std::is_same_v<ratl::arg_type_t<0, decltype(function2)>, int>);
	REQUIRE(std::is_same_v<ratl::arg_type_t<1, decltype(function2)>, int>);

	REQUIRE(std::is_same_v<ratl::return_type_t<decltype(function1)>, void>);
	REQUIRE(std::is_same_v<ratl::return_type_t<decltype(function2)>, int>);

	REQUIRE(ratl::number_of_args_v<decltype(function1)> == 0);
	REQUIRE(ratl::number_of_args_v<decltype(function2)> == 2);

	REQUIRE(ratl::has_b_v<A>);
}