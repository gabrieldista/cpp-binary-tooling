#pragma once

#include <cstdint>
#include <cstring>
#include <bit>

extern const bool host_is_be;
std::uint16_t read_u16(const uint8_t* ptr);
std::uint32_t read_u32(const uint8_t* ptr);
std::uint64_t read_u64(const uint8_t* ptr);


template <typename T>
T read_bytes(const uint8_t* ptr);

template <>
inline uint16_t read_bytes<uint16_t>(const uint8_t* ptr) { return read_u16(ptr); }

template <>
inline uint32_t read_bytes<uint32_t>(const uint8_t* ptr) { return read_u32(ptr); }

template <>
inline uint64_t read_bytes<uint64_t>(const uint8_t* ptr) { return read_u64(ptr); }

template <typename T>
inline T stream_bytes(uint8_t*& ptr) {
    T val = read_bytes<T>(ptr);
    ptr += sizeof(T);
    return val;
}

