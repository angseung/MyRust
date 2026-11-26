// Compares the Rust implementation (myrust::add) with a C++ reference
// implementation.

#include <cstdint>
#include <limits>
#include <random>
#include <tuple>

#include "gtest/gtest.h"
#include "myrust.h"

namespace {

constexpr int32_t kMin = std::numeric_limits<int32_t>::min();
constexpr int32_t kMax = std::numeric_limits<int32_t>::max();

// C++ reference implementation with two's complement wrap-around semantics,
// same as Rust's wrapping_add.
// Signed overflow is UB, so add as unsigned and convert back.
// (This conversion is well-defined since C++20; GCC/Clang/MSVC behave the
// same way before that.)
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
                      // Overflow: wrap-around results must match
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
  std::mt19937 rng(20261125);  // Fixed seed: failures are reproducible
  std::uniform_int_distribution<int32_t> dist(kMin, kMax);
  for (int i = 0; i < 100000; ++i) {
    const int32_t a = dist(rng);
    const int32_t b = dist(rng);
    ASSERT_EQ(add(a, b), CppAdd(a, b)) << "a=" << a << ", b=" << b;
  }
}

}  // namespace
