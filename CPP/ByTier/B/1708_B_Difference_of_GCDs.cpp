// Problem: CF 1708 B - Difference of GCDs
// https://codeforces.com/contest/1708/problem/B

/*
 * Problem: B. Difference of GCDs
 * Algorithm: Greedy Construction
 * 
 * Approach:
 * For each position i (1-based), we want to assign a value a_i such that gcd(i, a_i) is unique.
 * To achieve this, for position i, we set a_i = (1 + (l - 1) / i) * i.
 * This ensures that:
 *   - a_i >= l (since we're taking the smallest multiple of i that is >= l)
 *   - gcd(i, a_i) = i (because a_i is a multiple of i)
 *   - All gcd values will be distinct because they are the indices themselves.
 * 
 * Time Complexity: O(n) per test case, where n is the array size.
 * Space Complexity: O(n) for storing the array.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, l, r;
    scanf("%ld %ld %ld", &n, &l, &r);
    std::vector<long> a(n);
    bool possible(true);
    for (long p = 1; p <= n; p++) {
      // Assign a[p-1] to the smallest multiple of p greater than or equal to l
      a[p - 1] = (1 + (l - 1) / p) * p;
      if (a[p - 1] > r) {
        // If even the smallest valid assignment exceeds r, no solution exists
        possible = false;
      }
    }
    if (possible) {
      puts("YES");
      for (long p = 0; p < n; p++) {
        printf("%ld ", a[p]);
      }
      puts("");
    } else {
      puts("NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/