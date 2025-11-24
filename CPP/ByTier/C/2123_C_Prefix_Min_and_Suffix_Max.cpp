// Problem: CF 2123 C - Prefix Min and Suffix Max
// https://codeforces.com/contest/2123/problem/C

/*
C. Prefix Min and Suffix Max
Algorithms/Techniques: Prefix minimum and suffix maximum tracking.

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem asks to determine for each element in the array whether it's possible
to reduce the entire array down to a single element equal to that value using
specific operations:
- Replace any prefix with its minimum value
- Replace any suffix with its maximum value

The key insight is that an element a[i] can be the final remaining element if and only if:
1. It's the minimum in some prefix (from left)
2. It's the maximum in some suffix (from right)

So we compute:
- For each position: Is it the minimum of all elements from the start up to this point?
- For each position: Is it the maximum of all elements from this point to the end?

These two checks are done using prefix min and suffix max arrays.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<int> b(n, 0);
    long x(1e7); // Initialize to very large number for prefix min tracking
    for (long p = 0; p < n; p++) {
      if (a[p] < x) {
        b[p] = 1; // Mark as valid if a[p] is minimum so far from left
        x = a[p];
      }
    }
    x = 0; // Initialize to zero for suffix max tracking
    for (long p = n - 1; p >= 0; p--) {
      if (a[p] > x) {
        b[p] = 1; // Mark as valid if a[p] is maximum so far from right
        x = a[p];
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%d", b[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/