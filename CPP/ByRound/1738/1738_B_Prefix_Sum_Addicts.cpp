// Problem: CF 1738 B - Prefix Sum Addicts
// https://codeforces.com/contest/1738/problem/B

/*
Algorithm: Prefix Sum and Sorting Validation
Technique: 
- Derive the elements of the sequence from the given prefix sums.
- Use the property that a[i] = s[i] - s[i-1] to compute individual terms.
- Ensure the derived sequence is non-decreasing.

Time Complexity: O(n) per test case, since we process each prefix sum once.
Space Complexity: O(1), only using a few variables for computation.

Approach:
- Start with the first prefix sum to determine the first element.
- Compute subsequent elements using differences between consecutive prefix sums.
- Validate that the sequence remains non-decreasing (sorted).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long sprev;
    scanf("%ld", &sprev);
    // Compute the first element a[0] using the formula derived from constraints
    long aprev((sprev + (sprev > 0) * (n - k)) / (n - k + 1));
    bool possible(true);
    for (long p = 1; p < k; p++) {
      long s;
      scanf("%ld", &s);
      long a = s - sprev;  // Compute current element using prefix sum difference
      if (a < aprev) {    // Check if sequence is still non-decreasing
        possible = false;
      }
      sprev = s;
      aprev = a;
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/CodeForces/