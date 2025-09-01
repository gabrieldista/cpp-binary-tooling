#include "include/elf.hpp"
#include "include/bread.hpp"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

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

    e_class = mapped[EI_CLASS];
    e_data = mapped[EI_DATA];
}

void Elf::load_ehdr() { 
    std::cout << "Loading ELF header" << std::endl; 

    uint8_t *ptr = mapped;
    std::memcpy(ehdr.e_ident, ptr, EI_NIDENT);
    ptr += EI_NIDENT;

    ehdr.e_type = stream_bytes<uint16_t>(ptr);
    ehdr.e_machine = stream_bytes<uint16_t>(ptr);
    ehdr.e_version = stream_bytes<uint16_t>(ptr);
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


    std::cout << "e_type : " << +ehdr.e_type << std::endl;
};
