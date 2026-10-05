/* krml header omitted for test repeatability */


#include "TailLoops.h"

uint32_t TailLoops_search(uint32_t n0, uint32_t key0)
{
  uint32_t n = n0;
  uint32_t key = key0;
  while (n != 0U)
    if (n == key)
      return n;
    else
    {
      uint32_t tmp = n - 1U;
      n = tmp;
    }
  return 0U;
}

uint32_t TailLoops_countdown(uint32_t n0)
{
  uint32_t n = n0;
  while (n != 0U)
  {
    uint32_t tmp = n - 1U;
    n = tmp;
  }
  return n;
}

uint32_t TailLoops_swap(uint32_t n0, uint32_t x0, uint32_t y0)
{
  uint32_t n = n0;
  uint32_t x = x0;
  uint32_t y = y0;
  while (n != 0U)
  {
    uint32_t tmp0 = n - 1U;
    uint32_t tmp1 = y;
    uint32_t tmp = x;
    n = tmp0;
    x = tmp1;
    y = tmp;
  }
  return x;
}

void TailLoops_countdown_unit(uint32_t n0)
{
  uint32_t n = n0;
  while (n != 0U)
  {
    uint32_t tmp = n - 1U;
    n = tmp;
  }
  return;
}

