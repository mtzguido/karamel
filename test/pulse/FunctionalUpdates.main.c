#include "FunctionalUpdates.h"
#include <stdio.h>
#include <stdint.h>
#define CHECK(p) do { if (!(p)) { fprintf(stderr, "check failed at line %d: %s\n", __LINE__, #p); return 1; } } while (0)
#define COUNTERS(p,a,b,c) CHECK((p).first == (a) && (p).second == (b) && (p).untouched == (c))
#define FOO(p,c,d) CHECK((p).a == 1 && (p).b == 2 && (p).y == (c) && (p).z == (d))
static FunctionalUpdates_counters *callback_target;
static uint32_t mutate(void)
{
  *callback_target = (FunctionalUpdates_counters){999U, 888U, 777U};
  return 50U;
}
int main(void)
{
  FunctionalUpdates_foo initial = {1, 2, 3, 4}, f = initial;
  FunctionalUpdates_upd_1_ptr(&f, 9); FOO(f, 3, 9);
  FunctionalUpdates_upd_2_ptr(&f, 7, 8); FOO(f, 7, 8);
  FunctionalUpdates_upd_2_seq_ptr(&f, 6, 5); FOO(f, 6, 5);
  f = FunctionalUpdates_upd_1_local(initial, 9); FOO(f, 3, 9);
  CHECK(FunctionalUpdates_upd_1_local_snapshot(initial, 9) == 4);
  f = FunctionalUpdates_upd_2_local(initial, 7, 8); FOO(f, 7, 8);
  f = FunctionalUpdates_upd_2_seq_local(initial, 6, 5); FOO(f, 6, 5);
  f = FunctionalUpdates_upd_1_local_direct(initial, 9); FOO(f, 3, 9);
  f = FunctionalUpdates_upd_1_array(initial, 9); FOO(f, 3, 9);

  FunctionalUpdates_counters original = {11U, 22U, 17U}, p = original;
  FunctionalUpdates_unchanged(&p); COUNTERS(p, 11U, 22U, 17U);
  FunctionalUpdates_replace_all(&p, 3U, 4U, 5U); COUNTERS(p, 3U, 4U, 5U);
  FunctionalUpdates_four_counters q = {11U, 22U, 33U, 44U};
  FunctionalUpdates_set_two_constants(&q);
  CHECK(q.a1 == 1U && q.b1 == 2U && q.c == 33U && q.keep == 44U);
  FunctionalUpdates_set_three_constants(&q);
  CHECK(q.a1 == 1U && q.b1 == 2U && q.c == 3U && q.keep == 44U);
  FunctionalUpdates_set_two_values(&q, 9U, 8U);
  CHECK(q.a1 == 9U && q.b1 == 8U && q.c == 3U && q.keep == 44U);
  p = original; FunctionalUpdates_read_then_set(&p); COUNTERS(p, 22U, 42U, 17U);
  p.first = UINT32_MAX; FunctionalUpdates_increment_field(&p); COUNTERS(p, 0U, 42U, 17U);
  FunctionalUpdates_four_counters qs[] = {{11U, 22U, 33U, 44U}, {55U, 66U, 77U, 88U}};
  FunctionalUpdates_set_at_offset(qs, 0U);
  CHECK(qs[0].a1 == 11U && qs[1].a1 == 1U && qs[1].b1 == 2U && qs[1].c == 3U && qs[1].keep == 88U);

  p = original; FunctionalUpdates_swap_snapshot(&p); COUNTERS(p, 22U, 11U, 17U);
  p = original; FunctionalUpdates_swap_mixed(&p); COUNTERS(p, 22U, 11U, 17U);
  p = original; CHECK(FunctionalUpdates_increment_and_return_old(&p) == 11U); COUNTERS(p, 12U, 22U, 17U);
  p = original; CHECK(FunctionalUpdates_swap_and_return_old(&p) == 11U); COUNTERS(p, 22U, 11U, 17U);
  p = original; FunctionalUpdates_swap_fields(&p); COUNTERS(p, 22U, 11U, 17U);
  p = original; CHECK(FunctionalUpdates_set_and_return_old(&p, 9U) == 11U); COUNTERS(p, 9U, 22U, 17U);
  p = original; CHECK(FunctionalUpdates_set_and_return_arg(&p, 9U, 42U) == 42U); COUNTERS(p, 9U, 22U, 17U);
  FunctionalUpdates_counters ps[] = {{11U, 22U, 17U}, {33U, 44U, 55U}};
  FunctionalUpdates_set_at_index(ps, 1U, 9U); COUNTERS(ps[0], 11U, 22U, 17U); COUNTERS(ps[1], 9U, 44U, 55U);
  CHECK(FunctionalUpdates_set_at_index_and_return(ps, 1U, 8U) == 9U);
  COUNTERS(ps[1], 8U, 44U, 55U);
  CHECK(FunctionalUpdates_copy_index(ps, 0U, 1U, 6U) == 11U);
  COUNTERS(ps[0], 11U, 22U, 17U); COUNTERS(ps[1], 6U, 22U, 17U);
  ps[1] = (FunctionalUpdates_counters){33U, 44U, 55U};
  FunctionalUpdates_copy_index_terminal(ps, 0U, 1U, 7U);
  COUNTERS(ps[0], 11U, 22U, 17U); COUNTERS(ps[1], 7U, 22U, 17U);
  p = original; FunctionalUpdates_clobber(&p); COUNTERS(p, 22U, 22U, 17U);
  p = original; callback_target = &p;
  FunctionalUpdates_not_even_with_a_single_field(&p, mutate);
  COUNTERS(p, 50U, 22U, 17U);
  FunctionalUpdates_unused_buffer(3U);
  uint32_t cell = 7U;
  CHECK(FunctionalUpdates_increment(&cell) == 7U && cell == 8U);
  CHECK(FunctionalUpdates_read_before_call(7U) == 7U);
  CHECK(FunctionalUpdates_call_before_read(7U) == 22U);
  CHECK(FunctionalUpdates_increment_snapshot(&cell) == 8U && cell == 8U);
  p = FunctionalUpdates_local_swap_alias(11U, 22U); COUNTERS(p, 22U, 11U, 17U);
  FunctionalUpdates_indexed_counters indexed = FunctionalUpdates_local_index_alias();
  CHECK(indexed.index == 1U && indexed.value == 2U && indexed.spare == 17U);
  FunctionalUpdates_nested_record nested = {{11U, 22U}, 33U};
  FunctionalUpdates_nested_update(&nested);
  CHECK(nested.fields.left == 12U && nested.fields.right == 22U && nested.tag == 33U);
  nested = FunctionalUpdates_nested_update_local(nested, 7U);
  CHECK(nested.fields.left == 7U && nested.fields.right == 22U && nested.tag == 33U);
  return 0;
}
