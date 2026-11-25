cmake_minimum_required(VERSION 3.16)
project(MyRust LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CARGO cargo REQUIRED)

# ---- Rust 정적 라이브러리 빌드 ----
set(RUST_CRATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/myrust)
set(RUST_TARGET_DIR ${CMAKE_CURRENT_BINARY_DIR}/rust-target)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CARGO_PROFILE_FLAG "")
  set(RUST_PROFILE_DIR debug)
else()
  set(CARGO_PROFILE_FLAG --release)
  set(RUST_PROFILE_DIR release)
endif()

set(
  RUST_LIB
  ${RUST_TARGET_DIR}/${RUST_PROFILE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}myrust${CMAKE_STATIC_LIBRARY_SUFFIX}
)

add_custom_command(
  OUTPUT ${RUST_LIB}
  COMMAND ${CARGO} build ${CARGO_PROFILE_FLAG} --target-dir ${RUST_TARGET_DIR}
  WORKING_DIRECTORY ${RUST_CRATE_DIR}
  DEPENDS ${RUST_CRATE_DIR}/Cargo.toml ${RUST_CRATE_DIR}/src/lib.rs
  COMMENT "Building Rust crate 'myrust' with cargo"
  VERBATIM
)
add_custom_target(myrust_build DEPENDS ${RUST_LIB})

# Rust std가 정적 링크될 때 필요한 시스템 라이브러리
find_package(Threads REQUIRED)
set(RUST_SYSTEM_LIBS Threads::Threads ${CMAKE_DL_LIBS})
if(UNIX AND NOT APPLE)
  list(APPEND RUST_SYSTEM_LIBS m)
endif()

add_library(myrust STATIC IMPORTED GLOBAL)
set_target_properties(
  myrust
  PROPERTIES
    IMPORTED_LOCATION ${RUST_LIB}
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE_LINK_LIBRARIES "${RUST_SYSTEM_LIBS}"
)
add_dependencies(myrust myrust_build)

# ---- C++ 실행 파일 ----
add_executable(main main.cpp)
target_link_libraries(main PRIVATE myrust)

# ---- 테스트 (GoogleTest) ----
# BUILD_TESTING 옵션 제공 (기본 ON). 끄려면 -DBUILD_TESTING=OFF
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
