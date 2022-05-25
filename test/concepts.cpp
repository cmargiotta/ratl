#include <catch2/catch.hpp>

#include <type_traits>
#include <vector>

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

    REQUIRE(ratl::iterator<A*>);
    REQUIRE(!ratl::iterator<A>);
}

TEST_CASE("Iterator trait works correctly", "[traits]")
{
    REQUIRE(ratl::iterator<std::vector<int>::iterator>);
    REQUIRE(ratl::iterator<int*>);
}