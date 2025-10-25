// Problem: CF 1592 B - Hemose Shopping
// https://codeforces.com/contest/1592/problem/B

/*
B. Hemose Shopping

Algorithm:
- For each test case, determine if an array can be sorted using only swaps between indices i and j where |i - j| >= x.
- Key insight: We can think of the array as two separate arrays - one starting at index 0, and another at index 1, 
  but with a step of x. That means we can sort elements that are at positions i, i+x, i+2x, ... independently.
- If x >= n/2, then all elements are reachable from each other (since distance constraint is never restrictive).
- Otherwise, we check whether for each group of elements spaced by x, 
  their sorted versions match the current values.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the temporary copy of the array

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read array elements
      b[p] = a[p];        // Copy to temporary array for sorting
    }
    if (2 * x <= n) {
      puts("YES");       // If x is large enough, full connectivity allows sorting
      continue;
    }
    sort(b.begin(), b.end()); // Sort the copied array to know what final values should be
    bool possible(true);
    for (long p = n - x; possible && p < x; p++) {
      if (a[p] != b[p]) {  // Check if current element matches expected sorted value
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/