#include "include/bread.hpp"
#include <cstdint>
#include <cstring>
#include <bit>

const bool host_is_be = std::endian::native == std::endian::big;

std::uint16_t read_u16(const uint8_t* ptr) {
    uint16_t value;
    std::memcpy(&value, ptr, sizeof(value));
    return host_is_be ? std::byteswap(value) : value;
}

std::uint32_t read_u32(const uint8_t* ptr) {
    uint32_t value;
    std::memcpy(&value, ptr, sizeof(value));
    return host_is_be ? std::byteswap(value) : value;
}

std::uint64_t read_u64(const uint8_t* ptr) {
    uint64_t value;
    std::memcpy(&value, ptr, sizeof(value));
    return host_is_be ? std::byteswap(value) : value;
}

