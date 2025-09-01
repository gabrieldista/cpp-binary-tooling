project('binary-tooling', 'cpp', 
  version : '0.0.1',
  default_options : ['cpp_std=c++23']
)

project_description = 'An ELF binary tooling library'
project_sources = [
  'src/main.cpp',
  'src/elf.cpp',
  'src/bread.cpp',
]

project_headers = [
  'include/elf.hpp',
  'include/bread.hpp',
]



add_project_arguments('-std=c++23', language : 'cpp')
executable('elfinject',
  project_sources,
  include_directories : include_directories('include'),
)
