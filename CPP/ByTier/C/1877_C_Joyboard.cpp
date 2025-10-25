// Problem: CF 1877 C - Joyboard
// https://codeforces.com/contest/1877/problem/C

/*
C. Joyboard
Time Complexity: O(1) per test case
Space Complexity: O(1)

Algorithm:
This problem involves determining how many valid values can be assigned to the last slot (a_{n+1}) such that
the resulting array has exactly k distinct values. The key insight is to trace back the sequence:
a_i = a_{i+1} mod i, for i from n down to 1.

The solution analyzes several cases based on k:
- If k > 3: No valid assignments (or very restrictive conditions)
- If k == 1: Only one possibility: assign a_{n+1} = 0
- If k == 2: Compute range of valid values using the formula involving n and m
- If k == 3: Use mathematical reasoning to compute how many valid assignment yield exactly three distinct values

The computation uses modular arithmetic properties and simplifies into direct formulas.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    long res(0);
    if (k > 3) {
      res = 0;
    } else if (k == 1) {
      res = 1;
    } else if (k == 2) {
      // For k=2, we compute valid range of a_{n+1} values
      res = (m < (m / n + n - 1) ? m : (m / n + n - 1));
    } else {
      // For k=3, the result is derived from derived formula using n and m
      res = m - (m / n) - n + 1;
      res = res > 0 ? res : 0;
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/