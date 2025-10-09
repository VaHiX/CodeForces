// Problem: CF 2044 E - Insane Problem
// https://codeforces.com/contest/2044/problem/E

/*
E. Insane Problem

Purpose:
This code counts the number of ordered pairs (x, y) such that:
- l1 <= x <= r1
- l2 <= y <= r2
- There exists a non-negative integer n such that y = x * k^n

Algorithm:
The approach iterates through all possible powers of k (i.e., k^n) up to r2,
and for each such power, it calculates how many valid x values exist such that
y = x * k^n is within [l2, r2]. This is done using inclusion-exclusion principle
on the range [l2, r2] intersected with [x * k^n, x * k^n].

Time Complexity: O(log_k(r2)) per test case. Since we iterate over powers of k
up to r2, and each iteration involves constant-time operations.

Space Complexity: O(1). Only a few variables are used regardless of input size.

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int t, k, l1, r1, l2, r2;
long long ans;
int main() {
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d%d%d%d%d", &k, &l1, &r1, &l2, &r2);
    ans = 0;
    for (long long i = 1; i <= r2; i *= k) { // Loop over powers of k
      long long l = max(0ll + l2, i * l1), r = min(0ll + r2, i * r1); // Compute range of valid y values
      if (l <= r)
        ans += 1ll * r / i - 1ll * (l - 1) / i; // Count of valid x values for current power of k
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/