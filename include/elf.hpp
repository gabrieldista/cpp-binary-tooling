#pragma once

#include <cstdint>
#include <cstddef>

constexpr std::size_t EI_NIDENT  = 16;
constexpr std::size_t EI_CLASS = 4; 
constexpr std::size_t EI_DATA = 5; 

constexpr std::uint8_t ELFCLASSNONE = 0;
constexpr std::uint8_t ELFCLASS32 = 1;
constexpr std::uint8_t ELFCLASS64 = 2;

constexpr std::uint8_t ELFDATA2LSB = 1;
constexpr std::uint8_t ELFDATA2MSB = 2;

inline constexpr const char* S_ELFDATA2LSB = "LE";
inline constexpr const char* S_ELFDATA2MSB = "BE";
inline constexpr const char* S_ELFCLASS32 = "ELF32";
inline constexpr const char* S_ELFCLASS64 = "ELF64";

struct Elf_Ehdr {
    std::uint8_t e_ident[EI_NIDENT];
    std::uint16_t e_type;
    std::uint16_t e_machine;
    std::uint16_t e_version;

    std::uint64_t e_entry;
    std::uint64_t e_phoff;
    std::uint64_t e_shoff;

    std::uint32_t e_flags;
    std::uint16_t e_ehsize;
    std::uint16_t e_phentsize;
    std::uint16_t e_phnum;
    std::uint16_t e_shentsize;
    std::uint16_t e_shnum;
    std::uint16_t e_shstrndx;
};

class Elf {
    public:
        struct Elf_Ehdr ehdr;
        std::uint8_t e_class;
        std::uint8_t e_data;
        char* filepath;

        Elf(const char* filepath);
        void load_edata();
        void load_eclass();
        void load_ehdr();

    private:
        std::uint8_t* mapped;
};

