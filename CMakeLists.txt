cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=armv8.2-a")

# Check if using Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--version-script=${VERSION_SCRIPT}")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

add_subdirectory(cmake)

add_executable(main ./tools/android_unwind.cpp)
target_link_libraries(main unwindstack)

add_custom_target(
  copy_database_compile_commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${PROJECT_BINARY_DIR}/compile_commands.json
  ${PROJECT_SOURCE_DIR}/compile_commands.json
)
