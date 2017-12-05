cmake_minimum_required(VERSION 3.1)
project(dinamite)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set(LLVM_DIR /home/pan/project/LLVM/llvm-src/llvm-3.5.0.build/share/llvm/cmake)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "[+] Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "[+] Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(pass)
