include(FetchContent)

FetchContent_Declare(
  googletest
  URL
    https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
  URL_HASH
    SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
  DOWNLOAD_EXTRACT_TIMESTAMP
  TRUE
)
# Windows: 부모 프로젝트의 CRT 설정을 덮어쓰지 않도록
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# 프로젝트에 gtest/gmock을 설치 대상으로 넣지 않음
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(add_test add_test.cpp)
target_link_libraries(add_test PRIVATE myrust GTest::gtest_main)

gtest_discover_tests(add_test)
