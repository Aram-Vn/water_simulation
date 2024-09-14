
cmake_minimum_required(VERSION 3.10)

project("water_simulation")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HDR_FILES "src/*.h")

add_executable("water_simulation" main.cpp  ${SRC_FILES} ${HDR_FILES})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories("water_simulation" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# target_compile_options("water_simulation2" PRIVATE 
#     -Wall
#     -Wextra
#     -Wshadow
#     -Wswitch
#     -pedantic
#     -Wformat=2
#     -Wconversion
#     -Wnull-dereference
#     -Wunused-parameter
#     -Wunreachable-code
#     -Wimplicit-fallthrough
    
#     -Werror
#     -Werror=return-type
#     -Werror=uninitialized
#     -Werror=unused-result
#     -Werror=strict-overflow

#     -fsanitize=address
#     -fsanitize=undefined

#     -fno-omit-frame-pointer
# )

# target_link_options("water_simulation2" PRIVATE
#     -fsanitize=address
#     -fsanitize=undefined
# )

target_compile_features("water_simulation" PRIVATE cxx_std_20)

# If not Visual Studio generator, copy compile_commands.json
if(NOT CMAKE_GENERATOR MATCHES "Visual Studio")
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
        COMMENT "Copying compile_commands.json..."
    )

    add_custom_target(copy_compile_commands ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
        