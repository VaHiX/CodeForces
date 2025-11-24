// Problem: CF 466 B - Wonder Room
// https://codeforces.com/contest/466/problem/B

/*
B. Wonder Room
Problem: Given a room of size a x b, we need to enlarge it so that it can fit n students,
where each student requires at least 6 square meters. We want the new area to be minimized.

Approach:
- If current area (a * b) is already >= 6*n, no change is needed.
- Otherwise, try increasing one or both dimensions.
- We use a loop from initial smaller dimension up to sqrt(6*n) to find optimal dimensions.
- For each p, compute q = ceil(6*n / p), then check if p*q >= 6*n and update best solution.
- Time complexity: O(sqrt(6*n)) ~ O(10^9) in worst case, but effectively much smaller due to loop bounds.
  Space complexity: O(1)

Algorithms/Techniques:
- Brute force with optimized search range
- Mathematical calculation for ceiling division
- Optimization using square root bound

Input:
3 3 5
Output:
18
3 6

Input:
2 4 4
Output:
16
4 4
*/

#include <cstdio>
int main() {
  long long n, a, b;
  scanf("%lld %lld %lld\n", &n, &a, &b);
  if (a * b >= 6 * n) {
    printf("%lld\n%lld %lld\n", a * b, a, b);
    return 0;
  }
  long long initialSmall = (a < b) ? a : b;  // Store smaller dimension
  long long initialLarge = (a < b) ? b : a;  // Store larger dimension
  long long area = 1e18, bestSmall(0), bestLarge(0);  // Track minimal area and dimensions

  for (long long p = initialSmall; p * p < 6 * n; p++) {  // Loop up to sqrt(6*n)
    long long q = 6 * n / p;  // Compute quotient
    if (p * q < 6 * n) {
      ++q;  // Ensure q is at least ceil(6*n/p)
    }
    if (q < initialLarge) {
      continue;  // Skip if q smaller than original large dimension
    }
    if (p * q < area) {
      area = p * q;
      bestSmall = p;
      bestLarge = q;
    }
  }

  printf("%lld\n%lld %lld\n", area, (initialSmall == a ? bestSmall : bestLarge),
         (initialSmall == a ? bestLarge : bestSmall));
  return 0;
}


// https://github.com/VaHiX/codeForces/