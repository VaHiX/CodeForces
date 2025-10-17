// Problem: CF 1954 B - Make It Ugly
// https://codeforces.com/contest/1954/problem/B

/*
B. Make It Ugly

Algorithm:
The problem involves finding the minimum number of elements to remove from a "beautiful" array so that it stops being beautiful. A beautiful array can be made uniform by replacing an element at position i (where 2 ≤ i ≤ n-1) with its neighbors if they are equal. We observe that for an array to remain beautiful, every element must be connected to its neighbors in such a way that operations can be repeatedly applied.

The key insight is that we look for a subsequence of elements equal to x (say, the first element), and find how far apart these elements are. If two consecutive occurrences of x are too close (at distance < n-1), then removing one of them will break the pattern needed to make all elements equal.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <algorithm>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ans(n + 7); // Initialize with a value larger than possible
    long x;
    scanf("%ld", &x);
    long pos(-1); // Position of previous occurrence of x
    for (long p = 1; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a != x) {
        // Update answer with minimum gap between non-x elements
        ans = std::min(ans, p - 1 - pos);
        pos = p;
      }
    }
    // Account for the last segment from pos to end of array
    ans = std::min(ans, n - 1 - pos);
    if (ans >= n) {
      puts("-1");
    } else {
      printf("%ld\n", ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/