#ifndef UTILS_FIXED_ENDIANNESS_HPP
#define UTILS_FIXED_ENDIANNESS_HPP

#include <bit>
#include <cstdint>
#include <type_traits>

namespace ratl
{
    template<typename T, std::endian Endianness_>
    class fixed_endianness
    {
        private:
            static constexpr inline auto system_endianness = std::endian::native;

        public:
            T                            data;
            static constexpr inline auto Endianness = Endianness_;

        private:
            static void assertions()
            {
                static_assert(sizeof(fixed_endianness<T, Endianness_>) == sizeof(T),
                              "Size of fixed_endianness = size of its underlying type");

                static_assert(std::is_trivial_v<fixed_endianness<T, Endianness_>>,
                              "fixed_endianness is trivial");

                static_assert(sizeof(T) == sizeof(uint8_t) || sizeof(T) == sizeof(uint16_t)
                                  || sizeof(T) == sizeof(uint32_t) || sizeof(T) == sizeof(uint64_t),
                              "Only types of 8,16,32 or 64b are supported");
            }

            inline void set(T data_) noexcept
            {
                if constexpr (Endianness == system_endianness)
                {
                    data = data_;
                }
                else
                {
                    data = swap(data_);
                }
            }

            inline T get() const noexcept
            {
                if constexpr (Endianness == system_endianness)
                {
                    return data;
                }
                else
                {
                    return swap(data);
                }
            }

            inline T swap(T data_) const noexcept
            {
                if constexpr (sizeof(T) == sizeof(uint8_t))
                {
                    return data_;
                }

                if constexpr (sizeof(T) == sizeof(uint16_t))
                {
                    return __builtin_bswap16(data_);
                }

                if constexpr (sizeof(T) == sizeof(uint32_t))
                {
                    return __builtin_bswap32(data_);
                }

                if constexpr (sizeof(T) == sizeof(uint64_t))
                {
                    return __builtin_bswap64(data_);
                }

                return 0;
            }

        public:
            fixed_endianness& operator=(T data_) noexcept
            {
                set(data_);

                return *this;
            }

            operator T() const noexcept
            {
                return get();
            }

            inline T serialize() const noexcept
            {
                return data;
            }

            inline void deserialize(T data) noexcept
            {
                this->data = data;
            }
    };
}// namespace ratl

#endif// UTILS_FIXED_ENDIANNESS_HPP
