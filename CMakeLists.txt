cmake_minimum_required(VERSION 3.14)
project(tbd)

include(FetchContent)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Collect code
file(GLOB SOURCES "src/tbd/*.cpp")
file(GLOB HEADERS "include/tbd/*.h")

# tbd executable 
add_executable(tbd ${SOURCES} ${HEADERS})
target_include_directories(tbd PRIVATE include)

if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Compiler flags based on compiler type
if(MSVC)
    # See https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
    add_compile_options(/utf-8 /FS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /FS")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# SDL2
set(SDL_TEST OFF CACHE BOOL "Disable SDL test build")
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.28.5 # Replace with the desired version or branch
)
FetchContent_MakeAvailable(SDL2)
target_link_libraries(tbd PRIVATE SDL2::SDL2 SDL2::SDL2main)

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.1 
)
FetchContent_MakeAvailable(spdlog)
target_include_directories(tbd PRIVATE ${spdlog_SOURCE_DIR}/include)

# glm
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1 
)
FetchContent_MakeAvailable(glm)
target_link_libraries(tbd PRIVATE glm::glm)

# volk
FetchContent_Declare(volk
    GIT_REPOSITORY https://github.com/zeux/volk.git
    GIT_TAG 1.4.304 
)
FetchContent_MakeAvailable(volk)
target_include_directories(tbd PRIVATE ${volk_SOURCE_DIR})
target_link_libraries(tbd PRIVATE volk)

# Vulkan Memory Allocator (VMA)
FetchContent_Declare(vma
    GIT_REPOSITORY https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git
    GIT_TAG v3.2.1 
)
FetchContent_MakeAvailable(vma)
target_include_directories(tbd PRIVATE ${vma_SOURCE_DIR}/include)

# Add Vulkan package (you may need to link Vulkan manually depending on your setup)
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

# Catch2
# set(CATCH_BUILD_TESTING OFF CACHE BOOL "Disable Catch2 tests")
# set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "Disable Catch2 examples")
# FetchContent_Declare(
#     Catch2
#     GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#     GIT_TAG v3.8.0 
# )
# FetchContent_MakeAvailable(Catch2)
# target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
