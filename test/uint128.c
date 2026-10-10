/* Copyright (c) INRIA and Microsoft Corporation. All rights reserved.
   Licensed under the Apache 2.0 and MIT Licenses. */

#include <assert.h>
#include "FStar_UInt128.h"

static uint128_t words(uint64_t high, uint64_t low) {
  uint8_t bytes[16];
  store64_le(bytes, low);
  store64_le(bytes + 8, high);
  return load128_le(bytes);
}

static void check(uint128_t value, uint64_t high, uint64_t low) {
  uint8_t bytes[16];
  store128_le(bytes, value);
  assert(load64_le(bytes) == low);
  assert(load64_le(bytes + 8) == high);
  store128_be(bytes, value);
  assert(load64_be(bytes) == high);
  assert(load64_be(bytes + 8) == low);
  assert(FStar_UInt128_eq(load128_be(bytes), value));
}

int main(void) {
  uint128_t zero = words(0, 0);
  uint128_t one = words(0, 1);
  uint128_t low = words(0, UINT64_MAX);
  uint128_t high = words(1, 0);
  uint128_t max = words(UINT64_MAX, UINT64_MAX);
  uint128_t top = words(UINT64_C(0x8000000000000000), 0);

  check(words(UINT64_C(0xfedcba9876543210), UINT64_C(0x0123456789abcdef)),
      UINT64_C(0xfedcba9876543210), UINT64_C(0x0123456789abcdef));
  check(FStar_UInt128_add(low, one), 1, 0);
  check(FStar_UInt128_add_underspec(low, one), 1, 0);
  check(FStar_UInt128_add_mod(max, one), 0, 0);
  check(FStar_UInt128_sub(high, one), 0, UINT64_MAX);
  check(FStar_UInt128_sub_underspec(high, one), 0, UINT64_MAX);
  check(FStar_UInt128_sub_mod(zero, one), UINT64_MAX, UINT64_MAX);
  check(FStar_UInt128_mul_wide(UINT64_MAX, UINT64_MAX), UINT64_MAX - 1, 1);
  check(FStar_UInt128_mul32(UINT64_MAX, UINT32_MAX),
      UINT64_C(0xfffffffe), UINT64_C(0xffffffff00000001));

  check(FStar_UInt128_shift_left(low, 0), 0, UINT64_MAX);
  check(FStar_UInt128_shift_left(low, 1), 1, UINT64_MAX - 1);
  check(FStar_UInt128_shift_left(low, 63), UINT64_MAX >> 1, UINT64_C(1) << 63);
  check(FStar_UInt128_shift_left(low, 64), UINT64_MAX, 0);
  check(FStar_UInt128_shift_left(low, 127), UINT64_C(1) << 63, 0);
  check(FStar_UInt128_shift_right(max, 0), UINT64_MAX, UINT64_MAX);
  check(FStar_UInt128_shift_right(max, 1), UINT64_MAX >> 1, UINT64_MAX);
  check(FStar_UInt128_shift_right(max, 63), 1, UINT64_MAX);
  check(FStar_UInt128_shift_right(max, 64), 0, UINT64_MAX);
  check(FStar_UInt128_shift_right(max, 127), 0, 1);

  check(FStar_UInt128_logand(low, high), 0, 0);
  check(FStar_UInt128_logor(low, high), 1, UINT64_MAX);
  check(FStar_UInt128_logxor(max, low), UINT64_MAX, 0);
  check(FStar_UInt128_lognot(low), UINT64_MAX, 0);
  check(FStar_UInt128_uint64_to_uint128(UINT64_MAX), 0, UINT64_MAX);
  assert(FStar_UInt128_uint128_to_uint64(max) == UINT64_MAX);

  assert(FStar_UInt128_eq(max, max) && !FStar_UInt128_eq(low, high));
  assert(FStar_UInt128_gt(high, low) && !FStar_UInt128_gt(low, low));
  assert(FStar_UInt128_lt(low, high) && !FStar_UInt128_lt(high, high));
  assert(FStar_UInt128_gte(high, low) && FStar_UInt128_gte(low, low));
  assert(FStar_UInt128_lte(low, high) && FStar_UInt128_lte(high, high));
  check(FStar_UInt128_eq_mask(max, max), UINT64_MAX, UINT64_MAX);
  check(FStar_UInt128_eq_mask(low, max), 0, 0);
  check(FStar_UInt128_eq_mask(zero, one), 0, 0);
  check(FStar_UInt128_gte_mask(top, high), UINT64_MAX, UINT64_MAX);
  check(FStar_UInt128_gte_mask(high, top), 0, 0);
  check(FStar_UInt128_gte_mask(low, one), UINT64_MAX, UINT64_MAX);
  check(FStar_UInt128_gte_mask(one, low), 0, 0);
  check(FStar_UInt128_gte_mask(max, max), UINT64_MAX, UINT64_MAX);
  return 0;
}
