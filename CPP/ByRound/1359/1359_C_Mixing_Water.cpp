// Problem: CF 1359 C - Mixing Water
// https://codeforces.com/contest/1359/problem/C

/*
C. Mixing Water

Problem Description:
We have two infinite sources of water: hot water at temperature h and cold water at temperature c (c < h).
We perform alternating moves: take one cup of hot water, then one cup of cold water, and so on, starting with hot.
The resulting temperature in the barrel is the average of all poured temperatures.
Goal: Find minimum number of cups to pour such that the resulting temperature is as close as possible to target t.
If multiple answers give same difference, choose the smallest.

Algorithms/Techniques:
- Mathematical optimization with binary search or direct formula
- Analytical approach for minimizing absolute difference
- Case analysis based on comparison of t with h and (h + c)/2

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll h, c, t;
    scanf("%lld %lld %lld", &h, &c, &t);
    if (t >= h) {
      // If target temperature is greater than or equal to hot water temp,
      // we can only use one cup (hot water)
      puts("1");
    } else if (2 * t <= h + c) {
      // If 2*t <= h + c, then using two cups (one hot, one cold) gives
      // average = (h + c)/2 which is less than or equal to t.
      // This is optimal for this case.
      puts("2");
    } else {
      // General case: use mathematical approach to find best n
      // n is derived from solving the equation for optimal ratio of hot/cold cups
      long n = (h - t) / (2 * t - c - h);
      // Compute difference for n+1 and n+2 cups configurations
      long double u = (((n + 1.0) * h + n * c) / (2.0 * n + 1) - t);
      long double v = (((n + 2.0) * h + (n + 1) * c) / (2.0 * n + 3) - t);
      u = (u > 0) ? u : -u;
      v = (v > 0) ? v : -v;
      // Choose between configurations with n+1 and n+2 cups
      long res = 2 * (n + (v < u)) + 1;
      printf("%ld\n", res);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/