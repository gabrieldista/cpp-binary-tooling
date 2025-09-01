#include "elf.hpp"

#include <stdio.h>

int main(int argc, char **argv) {

    Elf elf = Elf("/bin/ls");
    elf.load_ehdr();

    return 0;
}
