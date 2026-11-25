// Rust 구현(myrust::add)과 C++ 레퍼런스 구현의 결과를 비교한다.

#include <cstdint>
#include <limits>
#include <random>
#include <tuple>

#include "gtest/gtest.h"
#include "myrust.h"

namespace {

constexpr int32_t kMin = std::numeric_limits<int32_t>::min();
constexpr int32_t kMax = std::numeric_limits<int32_t>::max();

// C++ 레퍼런스 구현. Rust의 wrapping_add와 같은 2의 보수 wrap-around 의미.
// signed 오버플로는 UB이므로 unsigned로 더한 뒤 다시 변환한다.
// (C++20부터 이 변환이 표준으로 정의되며, GCC/Clang/MSVC는 그 이전에도 동일
// 동작)
int32_t CppAdd(int32_t a, int32_t b) {
  return static_cast<int32_t>(static_cast<uint32_t>(a) +
                              static_cast<uint32_t>(b));
}

class AddCompareTest
    : public ::testing::TestWithParam<std::tuple<int32_t, int32_t>> {};

TEST_P(AddCompareTest, RustMatchesCpp) {
  const auto [a, b] = GetParam();
  EXPECT_EQ(add(a, b), CppAdd(a, b)) << "a=" << a << ", b=" << b;
}

INSTANTIATE_TEST_SUITE_P(BasicCases, AddCompareTest,
                         ::testing::Values(std::make_tuple(0, 0),
                                           std::make_tuple(3, 4),
                                           std::make_tuple(-4, 1),
                                           std::make_tuple(-7, -8),
                                           std::make_tuple(123456, -654321)));

INSTANTIATE_TEST_SUITE_P(
    Boundaries, AddCompareTest,
    ::testing::Values(std::make_tuple(kMax, 0), std::make_tuple(kMin, 0),
                      std::make_tuple(kMax, kMin),
                      // 오버플로: wrap-around 결과가 일치해야 함
                      std::make_tuple(kMax, 1), std::make_tuple(kMin, -1),
                      std::make_tuple(kMax, kMax),
                      std::make_tuple(kMin, kMin)));

TEST(AddTest, MatchesPlainAdditionWhenNoOverflow) {
  EXPECT_EQ(add(3, 4), 3 + 4);
  EXPECT_EQ(add(-100, 42), -100 + 42);
  EXPECT_EQ(add(kMax - 1, 1), kMax);
  EXPECT_EQ(add(kMin + 1, -1), kMin);
}

TEST(AddTest, WrapsOnOverflow) {
  EXPECT_EQ(add(kMax, 1), kMin);
  EXPECT_EQ(add(kMin, -1), kMax);
}

TEST(AddTest, RandomInputsMatchCpp) {
  std::mt19937 rng(20261125);  // 고정 시드: 실패 시 재현 가능
  std::uniform_int_distribution<int32_t> dist(kMin, kMax);
  for (int i = 0; i < 100000; ++i) {
    const int32_t a = dist(rng);
    const int32_t b = dist(rng);
    ASSERT_EQ(add(a, b), CppAdd(a, b)) << "a=" << a << ", b=" << b;
  }
}

}  // namespace
