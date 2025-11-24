// Problem: CF 1374 E1 - Reading Books (easy version)
// https://codeforces.com/contest/1374/problem/E1

/*
 * Problem: E1. Reading Books (easy version)
 *
 * Purpose:
 *   Find the minimum total time to select a set of books such that:
 *   - Alice likes at least k books in the set
 *   - Bob likes at least k books in the set
 *   - The set is shared between both and all chosen books are read together
 *
 * Approach:
 *   - Categorize books into three groups:
 *     - Both like (a[i] == 1 && b[i] == 1) -> d[]
 *     - Only Alice likes (a[i] == 1 && b[i] == 0) -> a[]
 *     - Only Bob likes (a[i] == 0 && b[i] == 1) -> b[]
 *   - Use prefix sums to efficiently compute minimum cost for choosing
 *     exactly p books from 'd' and (k-p) each from 'a' and 'b'.
 *   - Enumerate over all valid splits of how many books come from 'd'.
 *
 * Time Complexity: O(n * log(n))
 *   Sorting: O(n * log(n))
 *   Prefix sum computation: O(n)
 *   Main loop over possible splits: O(k), which is <= n
 *
 * Space Complexity: O(n)
 *   Vectors a, b, d store at most all n books.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a, b, d; // a: only Alice likes, b: only Bob likes, d: both like
  for (long p = 0; p < n; p++) {
    long t, x, y;
    scanf("%ld %ld %ld", &t, &x, &y);
    if (x && y) {
      d.push_back(t); // Both like the book
    } else if (x) {
      a.push_back(t); // Only Alice likes
    } else if (y) {
      b.push_back(t); // Only Bob likes
    }
  }

  // Early exit: not enough books to satisfy requirements
  if ((a.size() + d.size() < k) || (b.size() + d.size() < k)) {
    puts("-1");
    return 0;
  }

  // Sort each category by time (ascending)
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  sort(d.begin(), d.end());

  // Compute prefix sums for optimization
  for (long p = 1; p < a.size(); p++) {
    a[p] += a[p - 1];
  }
  for (long p = 1; p < b.size(); p++) {
    b[p] += b[p - 1];
  }
  for (long p = 1; p < d.size(); p++) {
    d[p] += d[p - 1];
  }

  long mt(2e9 + 7); // Initialize with large value to track minimum

  // Try all valid combinations of choosing some books from 'd', and remaining
  // from 'a' and 'b'. We use a variable p indicating how many books we take from d.
  for (long p = 0; p <= d.size() && p <= k; p++) {
    long time = (p > 0) ? d[p - 1] : 0; // Sum of first p books from d
    long idv = k - p; // Number of additional books needed for both Alice and Bob

    if (a.size() >= idv && b.size() >= idv) {
      // Add minimum cost to get "idv" books for Alice and Bob
      time += (idv > 0) ? (a[idv - 1] + b[idv - 1]) : 0;
      mt = (mt < time) ? mt : time; // Keep track of minimal total time
    }
  }

  printf("%ld\n", mt);
  return 0;
}


// https://github.com/VaHiX/codeForces/