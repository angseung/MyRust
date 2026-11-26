#pragma once

#include <cstdint>

extern "C" {
// myrust::add in Rust (myrust/src/lib.rs)
int32_t add(int32_t a, int32_t b);

int32_t mul(int32_t a, int32_t b);
}
