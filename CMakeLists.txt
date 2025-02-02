cmake_minimum_required(VERSION 3.30)

project(PSXBMPPacker CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
    -std=c++20
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wuninitialized
    -Wmissing-include-dirs
    -Wshadow
    -Wundef
    -Winvalid-pch
    -Wzero-as-null-pointer-constant
    -Wctor-dtor-privacy
    -Wold-style-cast
    -Woverloaded-virtual
    -g
)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(SRC_FILES
    "${SRC_DIR}/bitmap_image.cpp"
    "${SRC_DIR}/color.cpp"
    "${SRC_DIR}/color_lookup_table.cpp"
    "${SRC_DIR}/data_pack.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/packer_config.cpp"
    "${SRC_DIR}/pixel_data.cpp"
    "${SRC_DIR}/utils.cpp"
)

set(INCL_DIR "${PROJECT_SOURCE_DIR}/include")
set(INCL_FILES
    "${INCL_DIR}/bitmap_image.hpp"
    "${INCL_DIR}/color.hpp"
    "${INCL_DIR}/color_lookup_table.hpp"
    "${INCL_DIR}/data_pack.hpp"
    "${INCL_DIR}/packer_config.hpp"
    "${INCL_DIR}/pixel_data.hpp"
    "${INCL_DIR}/utils.hpp"
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCL_DIR})

# format target
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=GNU -i ${SRC_FILES} ${INCL_FILES}
        COMMENT "Running clang-format on source files."
    )

    add_dependencies(${PROJECT_NAME} format)
else()
    message(WARNING "clang-format not found. Code formatting skipped.")
endif()

# test/full targets
find_program(VALGRIND_EXECUTABLE NAMES valgrind)
if(VALGRIND_EXECUTABLE)
    add_custom_target(test
        COMMAND ${VALGRIND_EXECUTABLE} --leak-check=yes ./${PROJECT_NAME} -o testING12345.dummy -e FONT_TEXTURE,PIPE_TEXTURE font.bmp pipes.bmp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running valgrind leak check on executable."
    )

    add_custom_target(full
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test
        COMMENT "Running full build (clean, format, build, & test)."
    )
else()
    message(WARNING "valgrind not found. Memory leak check skipped.")
endif()
