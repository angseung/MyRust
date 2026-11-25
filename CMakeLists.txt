cmake_minimum_required(VERSION 3.22) # Corrosion v0.5 요구사항
project(MyRust LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---- Rust 크레이트 연동 (Corrosion) ----
# Corrosion이 cargo 호출, 빌드 프로필 매핑, 소스 변경 감지, Rust std가 요구하는 시스템 라이브러리 링크를 모두
# 처리한다.
include(FetchContent)
FetchContent_Declare(
  Corrosion
  GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
  GIT_TAG v0.5.1
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Corrosion)

# myrust/Cargo.toml의 staticlib 크레이트를 CMake 타깃 'myrust'로 가져온다.
corrosion_import_crate(MANIFEST_PATH myrust/Cargo.toml)
target_include_directories(myrust INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- C++ 실행 파일 ----
add_executable(main main.cpp)
target_link_libraries(main PRIVATE myrust)

# ---- 테스트 (GoogleTest) ----
# BUILD_TESTING 옵션 제공 (기본 ON). 끄려면 -DBUILD_TESTING=OFF
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
