#include "utils.hpp"

#include <catch2/catch.hpp>

union test_data
{
        ratl::fixed_endianness<uint16_t, ratl::endianness::BIG> test_number;
        uint16_t                                                data;
};

TEST_CASE("Utilities work correctly", "[utils]")
{
    test_data test;
    test.test_number = 0x00FF;

    REQUIRE(test.test_number == 255);
    REQUIRE(test.data == 0xFF00);

    REQUIRE((test.test_number + 1) == 256);

    test.test_number = test.test_number + 1;
    REQUIRE(test.test_number == 256);
    REQUIRE(test.data == 0x0001);
}