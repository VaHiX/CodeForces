// Problem: CF 1872 G - Replace With Product
// https://codeforces.com/contest/1872/problem/G

/*
Algorithm: Dynamic Programming with Sliding Window Optimization
Time Complexity: O(n)
Space Complexity: O(n)

This implementation finds the optimal subarray to replace with its product to maximize the sum of the resulting array.
It uses a segmented approach where consecutive 1s are grouped together and other numbers are treated as segments.
The algorithm tracks the sum and product of segments and compares various combinations to find the maximum possible sum.

The key idea is to:
1. Group consecutive 1s as they don't change the product but affect the sum
2. Treat other numbers as segments
3. Try different combinations of merging segments to find the maximum sum
4. Handle edge cases such as all 1s or single element arrays
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint64_t ac_t;
ac_t max_sum = (ac_t)400004;
struct s_unit {
  ac_t sum;
  ac_t mul;
  int l;
  int r;
};
inline static bool my_mul(ac_t &m1, ac_t m2) {
  m1 *= m2;
  if (m1 > max_sum) {
    return true; // Overflow occurred
  }
  return false;
}
int main() {
  int cx_test;
  scanf("%i", &cx_test);
  for (int i = 0; i < cx_test; i++) {
    int n;
    scanf("%i", &n);
    ac_t sum = 0;
    ac_t mul = 1;
    s_unit *unit = (s_unit *)malloc(sizeof(s_unit) * n);
    s_unit *e = unit;
    s_unit *b = unit;
    int cx = 0;
    bool begin = true;
    bool start_unit = true;
    bool max = false;
    int cx_1 = 0;
    for (int i = 0; i < n; i++) {
      int mmm;
      scanf("%i", &mmm);
      if (mmm == 1) {
        cx_1++;
        if (!start_unit) {
          start_unit = true;
          sum += e->sum;
          if (!max) {
            max = my_mul(mul, e->mul);
          }
          cx++;
          e++;
        }
        continue;
      }
      if (begin) {
        begin = false;
      } else {
        sum += cx_1;
      }
      cx_1 = 0;
      if (start_unit) {
        e->mul = mmm;
        e->sum = mmm;
        e->l = i;
        e->r = i;
        start_unit = false;
        continue;
      }
      if (!max) {
        max = my_mul(e->mul, mmm);
      }
      e->sum += mmm;
      e->r = i;
    }
    if (!start_unit) {
      sum += e->sum;
      if (!max) {
        max = my_mul(mul, e->mul);
      }
      cx++;
    } else if (cx > 0) {
      e--;
    }
    int l;
    int r;
    ac_t msum;
    ac_t lsum2 = 0;
    if (cx == 0) {
      l = 0;
      r = 0;
      goto l1;
    }
    if (max) {
      l = b->l;
      r = e->r;
      goto l1;
    }
    if (sum > mul) {
      l = 0;
      r = 0;
      msum = sum;
    } else {
      l = b->l;
      r = e->r;
      msum = mul;
    }
    if (cx == 1)
      goto l1;
    do {
      s_unit *e2 = e;
      ac_t rsum2 = 0;
      ac_t mul2 = mul;
      do {
        ac_t msum2 = lsum2 + mul2 + rsum2;
        if (msum2 > msum) {
          msum = msum2;
          l = b->l;
          r = e2->r;
        }
        mul2 /= e2->mul;
        ac_t tmp = e2->sum + (e2->l - (e2 - 1)->r - 1);
        rsum2 += tmp;
        e2--;
      } while (b != e2);
      ac_t msum2 = lsum2 + mul2 + rsum2;
      if (msum2 > msum) {
        msum = msum2;
        l = b->l;
        r = e2->r;
      }
      mul = mul / b->mul;
      ac_t tmp = b->sum + ((b + 1)->l - b->r - 1);
      lsum2 += tmp;
      b++;
      if (b == e) {
        msum2 = lsum2 + mul;
        if (msum2 > msum) {
          msum = msum2;
          l = b->l;
          r = b->r;
        }
      }
    } while (b != e);
  l1:
    printf("%i %i\n", l + 1, r + 1);
    free(unit);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/