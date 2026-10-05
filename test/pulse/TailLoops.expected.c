/* krml header omitted for test repeatability */


#include "TailLoops.h"

uint32_t TailLoops_search(uint32_t n0, uint32_t key0)
{
  uint32_t n = n0;
  uint32_t key = key0;
  while (true)
    if (n == 0U)
      return 0U;
    else if (n == key)
      return n;
    else
    {
      uint32_t tmp = n - 1U;
      n = tmp;
    }
}

uint32_t TailLoops_countdown(uint32_t n0)
{
  uint32_t n = n0;
  while (true)
    if (n != 0U)
    {
      uint32_t tmp = n - 1U;
      n = tmp;
    }
    else
      return n;
}

uint32_t TailLoops_swap(uint32_t n0, uint32_t x0, uint32_t y0)
{
  uint32_t n = n0;
  uint32_t x = x0;
  uint32_t y = y0;
  while (true)
    if (n == 0U)
      return x;
    else
    {
      uint32_t tmp0 = n - 1U;
      uint32_t tmp1 = y;
      uint32_t tmp = x;
      n = tmp0;
      x = tmp1;
      y = tmp;
    }
}

