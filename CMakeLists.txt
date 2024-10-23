cmake_minimum_required(VERSION 3.12...3.27.4)

project(twbl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

option(TWBL_DEBUG "activate bot debug comments" OFF)

include(CheckCCompilerFlag)

function(add_compiler_flag_if_supported FLAG)
    string(REGEX REPLACE "[^A-Za-z0-9]" "_" CONFIG_VARIABLE "FLAG_SUPPORTED${FLAG}")
    check_c_compiler_flag("${FLAG}" ${CONFIG_VARIABLE})
    if(${CONFIG_VARIABLE})
        add_definitions(${FLAG})
    endif()
endfunction()

add_definitions( -DTWBL_SHARED_OBJECT )

if(TWBL_DEBUG)
    add_definitions( -DTWBL_DEBUG )
endif()

FILE(GLOB BOT_SOURCE_FILES
    src/shared/base/*.cpp
    src/shared/base/*.h
    src/shared/*.cpp
    src/shared/*.h
    src/bots/*/*.cpp
    src/bots/*/*.h
    src/bots/*.cpp
    src/bots/*.h
)

set(TWBL_DEPS ${CMAKE_DL_LIBS})

add_library(twbl STATIC ${BOT_SOURCE_FILES})
target_compile_options(twbl PRIVATE -std=gnu++17)
add_compiler_flag_if_supported(-Wno-format-truncation)
target_link_libraries(twbl ${TWBL_DEPS})
include_directories(src)

if(TARGET_OS STREQUAL "windows")
    # See https://learn.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers
    add_compile_definitions(${target} PRIVATE NOMINMAX) # windows.h shouldn't define min/max macros
    add_compile_definitions(${target} PRIVATE WIN32_LEAN_AND_MEAN) # windows.h shouldn't define the name IStorage
    # 0x0501 (Windows XP) is required for mingw to get getaddrinfo to work
    # 0x0600 (Windows Vista) is required to use RegGetValueW and RegDeleteTreeW
    add_compile_definitions(${target} PRIVATE NTDDI_VERSION=0x06000000) # Minimum OS version (new macro, since Vista)
    add_compile_definitions(${target} PRIVATE _WIN32_WINNT=0x0600) # Minimum OS version (old macro, both must be defined)
    add_compile_definitions(${target} PRIVATE UNICODE) # Windows headers
    add_compile_definitions(${target} PRIVATE _UNICODE) # C-runtime
endif()

set(LINK_FLAGS_PLATFORM "")

# use the mock collision from the test code
# or the probe tool
# not from the bottick lite shared object
if(UNIX)
    set(LINK_FLAGS_PLATFORM -rdynamic)
endif()

# tools

add_executable(twbl_probe ${BOT_SOURCE_FILES} src/tools/twbl_probe.cpp)
target_link_libraries(twbl_probe ${TWBL_DEPS} ${LINK_FLAGS_PLATFORM})
target_compile_options(twbl_probe PRIVATE -std=gnu++17)

# tests

include(CTest)

function(register_test test_name)
    FILE(GLOB TEST_SOURCE_FILES
        src/test/*.cpp
        src/test/*.h
        src/test/${test_name}/*.cpp
        src/test/${test_name}/*.h)
    set(test_target "test_${test_name}")
    add_executable(${test_target} ${TEST_SOURCE_FILES})
    target_link_libraries(${test_target} twbl ${TWBL_DEPS} ${LINK_FLAGS_PLATFORM})
    target_compile_options(${test_target} PRIVATE -std=gnu++17)
    add_test(NAME ${test_target}
             COMMAND ${test_target})
endfunction()

register_test("sample")
register_test("follow")

