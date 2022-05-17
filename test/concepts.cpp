#include <catch2/catch.hpp>

#include <type_traits>

#include <concepts.hpp>

void function1();
int  function2(int, int);

struct A
{
        int b;

        virtual ~A() = default;
};

struct B : public A
{
};

struct C
{
};

MAKE_EXISTENCE_VERIFIER(b)

TEST_CASE("Function traits work correctly", "[traits]")
{
    REQUIRE(ratl::with_b<A>);
    REQUIRE(ratl::with_b<B>);
    REQUIRE(!ratl::with_b<C>);
}