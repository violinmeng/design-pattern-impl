cmake_minimum_required(VERSION 3.10)
project(cpp-design-pattern)

set(CMAKE_CXX_STANDARD 14)

# 启用 clang-tidy
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  find_program(CLANG_TIDY_EXE NAMES clang-tidy)
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
  endif()
endif()


# 添加基础库

# 添加子目录
add_subdirectory(lib/base)
add_subdirectory(lib/common)


add_subdirectory(bin/main)


