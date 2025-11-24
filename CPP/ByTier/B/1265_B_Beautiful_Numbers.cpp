// Problem: CF 1265 B - Beautiful Numbers
// https://codeforces.com/contest/1265/problem/B

/* 
B. Beautiful Numbers
Algorithm: For each position in the permutation, determine whether the number m is beautiful,
i.e., there exists a contiguous subarray that forms a permutation of numbers 1 to m.

The approach uses a sliding window concept:
- We maintain a boolean vector b to track which positions are occupied.
- As we process elements from 1 to n in order (using the inverse mapping a[x] = p), 
  we update the count of "segments" (continuous blocks) in the permutation.
- A segment is defined as a maximal sequence of consecutive numbers that form a continuous range.

Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n)
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 2, 0); // inverse mapping: a[x] = position of x in permutation
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      a[x] = p; // store the index (1-based) where value x appears
    }
    std::vector<bool> b(n + 2, 0); // tracks which positions have been seen
    long cnt(0); // count of segments (connected components)
    for (long p = 1; p <= n; p++) {
      long x = a[p]; // get the position where value p appears
      b[x] = 1; // mark the position as occupied
      if (!(b[x - 1] || b[x + 1])) {
        ++cnt; // new segment formed
      } else if (b[x - 1] && b[x + 1]) {
        --cnt; // two segments merge into one
      }
      printf("%d", (cnt <= 1)); // if segments <= 1, then m is beautiful
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/