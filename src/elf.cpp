#include "include/elf.hpp"
#include "include/bread.hpp"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include <format>
#include <iostream>
#include <stdexcept>


Elf::Elf(const char* filepath) {
    filepath = filepath;
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        throw std::runtime_error("Failed to open file for reading");
    }

    mapped = (uint8_t*) mmap(NULL, 1024, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        close(fd);
        throw std::runtime_error("Failed to mmap file");
    }
}

void Elf::load_ehdr() { 
    std::cout << "Loading ELF header" << std::endl; 

    uint8_t *ptr = mapped;
    std::memcpy(ehdr.e_ident, ptr, EI_NIDENT);
    ptr += EI_NIDENT;

    ehdr.e_type = stream_bytes<uint16_t>(ptr);
    ehdr.e_machine = stream_bytes<uint16_t>(ptr);
    ehdr.e_version = stream_bytes<uint32_t>(ptr);
    if (e_class == ELFCLASS32) {
        ehdr.e_entry = (uint64_t) stream_bytes<uint32_t>(ptr);
        ehdr.e_phoff = (uint64_t) stream_bytes<uint32_t>(ptr);
        ehdr.e_shoff = (uint64_t) stream_bytes<uint32_t>(ptr);
    } else {
        ehdr.e_entry = stream_bytes<uint64_t>(ptr);
        ehdr.e_phoff = stream_bytes<uint64_t>(ptr);
        ehdr.e_shoff = stream_bytes<uint64_t>(ptr);
    }
    ehdr.e_flags = stream_bytes<uint32_t>(ptr);
    ehdr.e_ehsize = stream_bytes<uint16_t>(ptr);
    ehdr.e_phentsize = stream_bytes<uint16_t>(ptr);
    ehdr.e_phnum = stream_bytes<uint16_t>(ptr);
    ehdr.e_shentsize = stream_bytes<uint16_t>(ptr);
    ehdr.e_shnum = stream_bytes<uint16_t>(ptr);
    ehdr.e_shstrndx = stream_bytes<uint16_t>(ptr);


};

void Elf::print_ehdr() {
    for (uint8_t x: ehdr.e_ident) {
        std::cout << std::format("{:#02x}", x) << " ";
    }
    std::cout << std::endl;
    std::cout << "e_type : " << std::format("{:#02x}", ehdr.e_type) << std::endl;
    std::cout << "e_machine : " << std::format("{:#010x}", ehdr.e_machine) << std::endl;
    std::cout << "e_version : " << std::format("{:#010x}", ehdr.e_version) << std::endl;
    std::cout << "e_entry : " << std::format("{:#010x}", ehdr.e_entry) << std::endl;
    std::cout << "e_phoff : " << std::format("{:#010x}", ehdr.e_phoff) << std::endl;
    std::cout << "e_shoff : " << std::format("{:#010x}", ehdr.e_shoff) << std::endl;
    std::cout << "e_shnum : " << std::format("{:#010x}", ehdr.e_shnum) << std::endl;
}

void Elf::load_sections() {
    std::cout << "Loading ELF Section (by headers)" << std::endl;

    for (uint16_t i = 0; i < ehdr.e_shnum; i++) {
        uint8_t* ptr = mapped + ehdr.e_shoff + i * ehdr.e_shentsize;
        Elf_Shdr shdr {};
        shdr.sh_name = stream_bytes<uint32_t>(ptr);
        shdr.sh_type = stream_bytes<uint32_t>(ptr);
        if (e_class == ELFCLASS32) {
            shdr.sh_flags = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_addr = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_offset = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_size = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_link = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_info = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_addralign = (uint64_t) stream_bytes<uint32_t>(ptr);
            shdr.sh_entsize = (uint64_t) stream_bytes<uint32_t>(ptr);
        } else {
            shdr.sh_flags = stream_bytes<uint64_t>(ptr);
            shdr.sh_addr = stream_bytes<uint64_t>(ptr);
            shdr.sh_offset = stream_bytes<uint64_t>(ptr);
            shdr.sh_size = stream_bytes<uint64_t>(ptr);
            shdr.sh_link = stream_bytes<uint32_t>(ptr);
            shdr.sh_info = stream_bytes<uint32_t>(ptr);
            shdr.sh_addralign = stream_bytes<uint64_t>(ptr);
            shdr.sh_entsize = stream_bytes<uint64_t>(ptr);
        }
        sections.push_back(shdr);
    }
};
