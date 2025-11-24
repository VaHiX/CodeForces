// Problem: CF 1016 B - Segment Occurrences
// https://codeforces.com/contest/1016/problem/B

/*
B. Segment Occurrences
Algorithm: Preprocessing with prefix sums to answer range queries efficiently.

Time Complexity: O(n*m + q*n) where n is length of string s, m is length of string t, and q is number of queries.
Space Complexity: O(n) for the cnt array.

Techniques:
- String matching using substr()
- Prefix sum array for efficient range query processing
- Using cin.sync_with_stdio(0); for fast I/O

The solution works by:
1. Preprocessing all occurrences of t in s using a prefix sum array.
2. For each query, compute how many occurrences of t exist in the given range
   by using the precomputed prefix sums.
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
int cnt[1005], n, m, q; // cnt: prefix sum array for occurrences, n,m,q: input sizes
string s, t;            // s: main string, t: pattern string

int main() {
  cin.sync_with_stdio(0);   // Optimize I/O speed by disabling synchronization with C stdio
  cin.tie(0);               // Untie cin from cout for further speed boost
  cin >> n >> m >> q >> s >> t; // Read input: lengths, strings

  // Preprocessing phase: build prefix sum array cnt[]
  // cnt[i] stores number of occurrences of t in s[0..i-1]
  for (int i = 0; i <= n - m; ++i)
    cnt[i + 1] = cnt[i] + (s.substr(i, m) == t); // Check if substring matches t and update count

  while (q--) { // Process each query
    int l, r;
    cin >> l >> r; // Read query range [l,r]
    
    if (r - l + 1 < m) // If length of substring less than pattern length
      puts("0");       // No possible match
    else
      printf("%d\n", cnt[r - m + 1] - cnt[l - 1]); // Use prefix sums to find count in range [l,r]
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/