// Problem: CF 1720 D2 - Xor-Subsequence (hard version)
// https://codeforces.com/contest/1720/problem/D2

/*
Code Purpose:
This code solves the "Xor-Subsequence (hard version)" problem by finding the longest beautiful subsequence in an array.
A beautiful subsequence satisfies the condition: for any two consecutive elements in the subsequence,
a[b_p] XOR b_{p+1} < a[b_{p+1}] XOR b_p.
The algorithm uses a trie data structure to efficiently compute the maximum length of such a subsequence.

Algorithms/Techniques:
- Trie-based dynamic programming
- Bitwise operations and XOR comparisons
- Efficient storage and querying using trie nodes

Time Complexity: O(30 * n) per test case, where 30 is the number of bits (32-bit integers)
Space Complexity: O(n * 30) for the trie structure
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 3e5 + 5, M = N * 30;
int T, n, a[N], t = 1, tr[M][2], ans, s[M][2];
void Main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    int v = (a[i] ^ i), u = 1, x = 0;
    // Traverse the trie to find the maximum length subsequence ending at current element
    for (int j = 29; ~j; j--) {
      int k = ((v >> j) & 1);  // Get j-th bit of v
      // Query the trie for the best previous element that satisfies the beautiful condition
      x = max(x, s[tr[u][!k]][!((a[i] >> j) & 1)]);
      u = tr[u][k];  // Move to next node in trie based on bit k
    }
    x++;  // Increment for current element
    ans = max(ans, x);  // Update global maximum
    u = 1;
    // Insert current element into the trie
    for (int j = 29; ~j; j--) {
      int k = ((v >> j) & 1);  // Get j-th bit of v
      if (!tr[u][k])  // Create new node if not exists
        tr[u][k] = ++t;
      u = tr[u][k];
      k = ((i >> j) & 1);  // Get j-th bit of i (index)
      s[u][k] = max(s[u][k], x);  // Store maximum length at this node
    }
  }
  printf("%d\n", ans);
  // Reset trie and auxiliary arrays for next test case
  for (int i = 1; i <= t; i++)
    tr[i][0] = tr[i][1] = s[i][0] = s[i][1] = 0;
  t = 1;
  ans = 0;
}
int main() {
  for (scanf("%d", &T); T--; Main())
    ;
  return 0;
}


// https://github.com/VaHiX/CodeForces/