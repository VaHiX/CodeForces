// Problem: CF 2007 C - Dora and C++
// https://codeforces.com/contest/2007/problem/C

/*
 * Problem: Dora and C++
 * Purpose: Minimize the range of an array after performing operations
 *          where each element can be increased by 'a' or 'b'.
 *
 * Algorithm:
 * - For each test case, reduce all elements modulo GCD(a, b) to find equivalence classes.
 * - Sort the reduced values and compute minimum range by checking adjacent differences.
 * - The final answer is the smallest possible range after optimal operations.
 *
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the vector of elements.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    long g = gcd(a, b);  // Compute GCD of a and b to find equivalence class
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    for (long p = 0; p < n; p++) {
      v[p] %= g;  // Reduce each element modulo GCD(a, b)
    }
    sort(v.begin(), v.end());  // Sort the reduced values
    long rng = v.back() - v[0];  // Initial range is difference between max and min
    for (long p = 1; p < n; p++) {
      long tst = g - (v[p] - v[p - 1]);  // Compute wrap-around difference
      rng = (tst < rng ? tst : rng);     // Update minimum range
    }
    printf("%ld\n", rng);
  }
}


// https://github.com/VaHiX/codeForces/