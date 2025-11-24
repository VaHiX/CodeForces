// Problem: CF 863 D - Yet Another Array Queries Problem
// https://codeforces.com/contest/863/problem/D

/*
 * Problem: Yet Another Array Queries Problem
 * 
 * Approach:
 * - Process queries in reverse order to simulate the effect of operations on a specific index.
 * - For each important index (b_i), trace its movement through all queries.
 * - Type 1 (cyclic shift right): If index is in range [l, r], it moves right by 1, except the leftmost element which wraps to the rightmost.
 * - Type 2 (reverse): If index is in range [l, r], it reflects across the center of the segment.
 * 
 * Time Complexity: O(q * m + n) where q is number of queries, m is number of important indices, n is array size.
 * Space Complexity: O(q + n) for storing queries and array elements.
 */
#include <cstdio>
#include <vector>
int main() {
  long n, q, m;
  scanf("%ld %ld %ld", &n, &q, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> t(q), l(q), r(q);
  for (long p = 0; p < q; p++) {
    scanf("%ld %ld %ld", &t[p], &l[p], &r[p]);
    --l[p];
    --r[p];
  }
  while (m--) {
    long ind;
    scanf("%ld", &ind);
    --ind;
    for (long u = q - 1; u >= 0; u--) {
      if (ind < l[u] || r[u] < ind) {
        continue;
      }
      if (t[u] == 1) {
        // Cyclic shift: if ind is at leftmost, move to rightmost; otherwise move left
        ind = (ind == l[u]) ? r[u] : (ind - 1);
      } else {
        // Reverse: map ind to symmetric position
        ind = l[u] + r[u] - ind;
      }
    }
    printf("%ld ", a[ind]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/