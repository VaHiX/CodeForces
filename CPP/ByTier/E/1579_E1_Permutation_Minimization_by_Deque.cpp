// Problem: CF 1579 E1 - Permutation Minimization by Deque
// https://codeforces.com/contest/1579/problem/E1

/*
 * Problem: E1. Permutation Minimization by Deque
 * Algorithm: Greedy approach using deque
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the deque storage
 *
 * The algorithm processes each element of the permutation from left to right,
 * deciding whether to place it at the front or back of the deque based on
 * minimizing the lexicographical result.
 * Key insight:
 *   - If the current element is smaller than the front of the deque, 
 *     we place it at the front (to minimize the prefix).
 *   - Otherwise, we append it to the back to preserve ordering.
 */

#include <cstdio>
#include <deque>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::deque<long> d;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // If deque is empty or current element is smaller than front,
      // place it at the front to keep result lexicographically small
      if (d.empty() || x < d.front()) {
        d.push_front(x);
      } else {
        // Otherwise, place it at the back
        d.push_back(x);
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", d[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/