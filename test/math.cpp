#include <catch2/catch.hpp>

#include <math/fraction.hpp>

TEST_CASE("Fractions operations")
{
    ratl::math::fraction f1(1, 2);
    ratl::math::fraction f2(2, 4);

    auto f_sum = f1 + f2;
    auto f_sub = f1 - f2;
    auto f_mul = f1 * f2;
    auto f_div = f1 / f2;

    REQUIRE(f_sum.numerator == 1);
    REQUIRE(f_sum.denominator == 1);

    REQUIRE(f_sub.numerator == 0);
    REQUIRE(f_sub.denominator == 1);

    REQUIRE(f_mul.numerator == 1);
    REQUIRE(f_mul.denominator == 4);

    REQUIRE(f_div.numerator == 1);
    REQUIRE(f_div.denominator == 1);
}