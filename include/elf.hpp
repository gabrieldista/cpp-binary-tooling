#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

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
    std::uint32_t e_version;

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

struct Elf_Shdr {
    std::uint32_t sh_name;
    std::uint32_t sh_type;
    std::uint32_t sh_flags;
    std::uint64_t sh_addr;
    std::uint64_t sh_offset;
    std::uint32_t sh_size;
    std::uint32_t sh_link;
    std::uint32_t sh_info;
    std::uint32_t sh_addralign;
    std::uint32_t sh_entsize;
};

class Elf {
    public:
        std::vector<Elf_Shdr> sections;
        struct Elf_Ehdr ehdr;
        std::uint8_t e_class;
        std::uint8_t e_data;
        char* filepath;

        Elf(const char* filepath);
        void load_ehdr();
        void load_sections();
        void print_ehdr();

    private:
        std::uint8_t* mapped;
};

