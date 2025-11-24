// Problem: CF 1878 A - How Much Does Daytona Cost?
// https://codeforces.com/contest/1878/problem/A

/*
 * Problem: A. How Much Does Daytona Cost?
 * Purpose: Determine if there exists a subsegment in which k is the most common element.
 *
 * Algorithm:
 *   - For each test case, read array elements and check whether k appears at least once.
 *   - If k appears, we can always construct a subsegment where it's the most common
 *     by including only k's occurrences (or including one more k than any other number).
 *   - The key insight is that if k exists in the array, there's always a way to form such a segment.
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <cstdio>
int main() {
  long t;                             // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    long n, k;                        // n: size of array, k: target element
    scanf("%ld %ld", &n, &k);
    bool res(false);                  // Result flag, initially false
    for (long p = 0; p < n; p++) {    // Iterate through all elements
      long x;
      scanf("%ld", &x);
      if (x == k) {                   // If current element equals k
        res = true;                   // Set result to true
      }
    }
    puts(res ? "YES" : "NO");         // Print result
  }
}


// https://github.com/VaHiX/codeForces/