#include "utils.hpp"

#include <catch2/catch.hpp>

union test_data
{
        ratl::fixed_endianness<uint16_t, std::endian::big> test_number;
        uint16_t                                           data;
};

struct test_packed
{
        ratl::fixed_endianness<uint16_t, std::endian::big> test;
        uint8_t                                            test_;
} __attribute__((packed));

TEST_CASE("Utilities work correctly", "[utils]")
{
    test_data test;
    test.test_number = 0x00FF;

    REQUIRE(test.test_number == 255);
    REQUIRE(test.data == 0xFF00);
    REQUIRE(test.test_number.serialize() == 0xFF00);

    REQUIRE((test.test_number + 1) == 256);

    REQUIRE(sizeof(test_packed) == (sizeof(uint16_t) + sizeof(uint8_t)));

    test.test_number = test.test_number + 1;
    REQUIRE(test.test_number == 256);
    REQUIRE(test.data == 0x0001);
}