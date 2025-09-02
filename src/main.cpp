#include "elf.hpp"

#include <stdio.h>

int main(int argc, char **argv) {

    Elf elf = Elf("/bin/ls");
    elf.load_ehdr();
    elf.print_ehdr();
    elf.load_sections();

    return 0;
}
