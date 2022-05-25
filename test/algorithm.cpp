#include <catch2/catch.hpp>

#include <functional>
#include <vector>

#include <algorithm/lazy_transform.hpp>

using Catch::Matchers::Equals;

SCENARIO("Lazy transform of a vector")
{
    GIVEN("A vector of items and a transform function")
    {
        std::vector<int>         v({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        std::function<int(int&)> transform([](int& val) -> int { return val * 2; });

        WHEN("The lazy transform operation is requested")
        {
            auto lazy = ratl::lazy_transform(v.begin(), v.end(), transform);

            THEN("The operation is applied only when the lazy iterator is accessed")
            {
                REQUIRE_THAT(v, Equals(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})));

                *lazy;
                ++lazy;
                *lazy;

                REQUIRE_THAT(v, Equals(std::vector<int>({2, 4, 3, 4, 5, 6, 7, 8, 9, 10})));
            }
        }
    }
}