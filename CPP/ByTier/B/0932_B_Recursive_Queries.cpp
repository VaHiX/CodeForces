// Problem: CF 932 B - Recursive Queries
// https://codeforces.com/contest/932/problem/B

/*
 * Problem: B. Recursive Queries
 * 
 * Purpose:
 *   This code computes the number of integers x in a given range [l, r] such that g(x) = k,
 *   where g(x) is a recursively defined function. The function g(x) is defined as:
 *   - If x < 10, then g(x) = x
 *   - Otherwise, g(x) = g(product of non-zero digits of x)
 *   
 *   The solution uses precomputation and prefix sums to efficiently answer multiple queries.
 * 
 * Algorithms/Techniques:
 *   - Preprocessing using dynamic programming to compute g(x) for all x up to 10^6
 *   - Prefix sum technique for fast range query answers
 * 
 * Time Complexity: O(N + Q), where N = 10^6 and Q is the number of queries.
 * Space Complexity: O(N * 10) = O(N), for storing the prefix sum array.
 */

#include <cstdio>
#include <vector>
int main() {
  const long N = 1e6 + 7;
  std::vector<long> g(N, 0); // g[p] stores the value of function g for number p
  for (long p = 1; p < N; p++) {
    if (p < 10) {
      g[p] = p; // Base case: g(x) = x if x is a single digit
    } else {
      long prod(1), x(p);
      while (x > 0) {
        long md = x % 10;
        if (md > 0) {
          prod *= md; // Multiply non-zero digits
        };
        x /= 10;
      }
      g[p] = g[prod]; // Recursively define g(x) using the product of its digits
    }
  }
  // h[p][u] stores the count of numbers from 1 to p having g(x) = u
  std::vector<std::vector<long>> h(N, std::vector<long>(10, 0));
  for (long p = 1; p < N; p++) {
    for (long u = 1; u < 10; u++) {
      h[p][u] = h[p - 1][u]; // Copy previous counts
    }
    ++h[p][g[p]]; // Increment count for current value of g[p]
  }
  long q;
  scanf("%ld", &q);
  while (q--) {
    long l, r, k;
    scanf("%ld %ld %ld", &l, &r, &k);
    printf("%ld\n", h[r][k] - h[l - 1][k]); // Answer query using prefix sum
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/