#ifndef MATH_FRACTION_HPP
#define MATH_FRACTION_HPP

#include <concepts>
#include <exception>
#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace ratl::math
{
    template<std::signed_integral T = int>
    class fraction
    {
        public:
            T numerator   = 0;
            T denominator = 1;

        private:
            fraction& simplify()
            {
                if (numerator == 0)
                {
                    denominator = 1;
                }
                else
                {
                    auto gcd = std::gcd(numerator, denominator);
                    numerator /= gcd;
                    denominator /= gcd;
                }

                return *this;
            }

            void swap()
            {
                std::swap(numerator, denominator);
            }

        public:
            fraction(T num, T den) noexcept
            {
                if (den == 0)
                {
                    throw std::runtime_error("Cannot divide by zero");
                }

                numerator   = num;
                denominator = den;

                simplify();
            }

            explicit fraction(T num) noexcept: numerator(num)
            {
            }

            fraction& operator=(T num) noexcept
            {
                numerator = num;

                return *this;
            }

            fraction() noexcept           = default;
            ~fraction()                   = default;
            fraction(const fraction&)     = default;
            fraction(fraction&&) noexcept = default;
            fraction& operator=(fraction&&) noexcept = default;
            fraction& operator=(const fraction&) = default;

            inline bool operator==(const fraction& other) const noexcept
            {
                return (numerator == other.numerator) && (denominator == other.denominator);
            }

            inline bool operator==(T other) const noexcept
            {
                return (numerator == other) && (denominator == 1);
            }

            inline bool operator>(const fraction& other) const noexcept
            {
                return static_cast<double>(*this) > static_cast<double>(other);
            }

            inline bool operator>(T other) const noexcept
            {
                return static_cast<double>(*this) > other;
            }

            template<typename O>
            inline bool operator>=(const O& other) const noexcept
            {
                return operator>(other) || operator==(other);
            }

            template<typename O>
            inline bool operator<(const O& other) const noexcept
            {
                return !operator>(other) && !operator==(other);
            }

            template<typename O>
            inline bool operator<=(const O& other) const noexcept
            {
                return !operator>(other);
            }

            template<typename O>
            inline bool operator!=(const O& other) const noexcept
            {
                return !operator==(other);
            }

            template<typename O>
            inline fraction operator+(O other) const noexcept
            {
                auto result = *this;
                result += other;

                return result;
            }

            fraction& operator+=(const fraction& other) noexcept
            {
                auto lcm = std::lcm(denominator, other.denominator);

                numerator *= lcm / denominator;
                numerator += other.numerator * (lcm / other.denominator);

                denominator = lcm;

                simplify();

                return *this;
            }

            inline fraction& operator+=(T other) noexcept
            {
                numerator += numerator + (other * denominator);

                simplify();
            }

            template<typename O>
            inline fraction& operator-=(O other) noexcept
            {
                operator+=(-other);
            }

            inline fraction operator-() const noexcept
            {
                fraction other(-numerator, denominator);

                return other;
            }

            inline fraction operator-(const auto& other) const noexcept
            {
                return operator+(-other);
            }

            inline fraction& operator*=(const fraction& other) noexcept
            {
                numerator *= other.numerator;
                denominator *= other.denominator;

                simplify();

                return *this;
            }

            inline fraction& operator*=(T other) noexcept
            {
                numerator *= other;

                simplify();

                return *this;
            }

            template<typename O>
            inline fraction operator*(O other) const noexcept
            {
                auto result = *this;
                result *= other;

                return result;
            }

            inline fraction& operator/=(const fraction& other) noexcept
            {
                numerator *= other.denominator;
                denominator *= other.numerator;

                simplify();

                return *this;
            }

            template<typename O>
            inline fraction operator/(O other) const noexcept
            {
                auto result = *this;
                result /= other;

                return result;
            }

            explicit operator double() const noexcept
            {
                return static_cast<double>(numerator) / denominator;
            }

            explicit operator std::string() const noexcept
            {
                std::stringstream ss;

                ss << numerator;

                if (denominator != 1)
                {
                    ss << '/' << denominator;
                }

                return ss.str();
            }
    };
}// namespace ratl::math

#endif// MATH_FRACTION_HPP
