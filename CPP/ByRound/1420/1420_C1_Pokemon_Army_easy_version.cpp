// Problem: CF 1420 C1 - Pokémon Army (easy version)
// https://codeforces.com/contest/1420/problem/C1

/*
C1. Pokémon Army (easy version)
Algorithms/Techniques: Dynamic Programming, Kadane's Algorithm variant
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storage

This problem asks to find the maximum alternating sum of any subsequence 
from the given array. An alternating sum is defined as:
a[b1] - a[b2] + a[b3] - a[b4] + ...
The solution uses dynamic programming where we track two states:
- f: maximum alternating sum ending at current position with an odd index (positive term)
- g: maximum alternating sum ending at current position with an even index (negative term)

For each element, we decide whether to include it in our subsequence or not,
updating the states accordingly.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, q;
    scanf("%ld %ld", &n, &q);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    // f represents max alternating sum ending at current position with positive term
    // g represents max alternating sum ending at current position with negative term
    long long f(a[0]), g(0);
    for (long p = 1; p < n; p++) {
      // Update f: either extend previous g + a[p] (if we add current element as negative)
      // or start fresh from 0, or continue previous f
      f = std::max(f, std::max(g + a[p], 0LL));
      // Update g: either extend previous f - a[p] (if we're starting new subsequence)
      // or keep previous g
      g = std::max(g, f - a[p]);
    }
    printf("%lld\n", std::max(f, g));
  }
}


// https://github.com/VaHiX/codeForces/