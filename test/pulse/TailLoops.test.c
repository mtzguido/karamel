#include <assert.h>
#include "TailLoops.h"

int main(void)
{
  for (uint32_t n = 0; n < 64; ++n)
  {
    for (uint32_t key = 0; key < 70; ++key)
      assert(TailLoops_search(n, key) == (key <= n ? key : 0));
    assert(TailLoops_countdown(n) == 0);
    assert(TailLoops_swap(n, 17, 23) == (n % 2 == 0 ? 17U : 23U));
  }
  assert(TailLoops_search(UINT32_MAX, UINT32_MAX) == UINT32_MAX);
  return 0;
}
