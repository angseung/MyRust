cmake_minimum_required(VERSION 3.22) # Required by Corrosion v0.5
project(MyRust LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---- Rust crate integration (Corrosion) ----
# Corrosion handles invoking cargo, build profile mapping, source change
# detection, and linking the system libraries required by the Rust std.
include(FetchContent)
FetchContent_Declare(
  Corrosion
  GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
  GIT_TAG v0.5.1
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Corrosion)

# Import the staticlib crate in myrust/Cargo.toml as the CMake target 'myrust'.
corrosion_import_crate(MANIFEST_PATH myrust/Cargo.toml)
target_include_directories(myrust INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- C++ executable ----
add_executable(main main.cpp)
target_link_libraries(main PRIVATE myrust)

# ---- Tests (GoogleTest) ----
# Provides the BUILD_TESTING option (ON by default). Disable with
# -DBUILD_TESTING=OFF
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
