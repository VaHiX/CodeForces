// Problem: CF 1761 F1 - Anti-median (Easy Version)
// https://codeforces.com/contest/1761/problem/F1

/*
Code Purpose:
This code solves the "Anti-median" problem by using dynamic programming and checking for invalid subarrays.
It determines how many ways we can fill unknown elements in a permutation such that all odd-length subarrays are not "bad" (i.e., the middle element is not the median after sorting).
The key is to use a DP approach based on valid sequences and track forbidden (bad) subarray patterns.

Algorithm:
1. For each test case, parse input to know which elements are fixed.
2. Use a sequence array to process indices in a specific order (odd indices first, then even).
3. Identify "bad" pairs (i, j) where a subarray from i to j would form a bad array.
4. Use dynamic programming where f[i][j] represents number of ways to construct valid sequences ending at position i and j.
5. Fill unknown positions only if they don't lead to invalid subarrays.
6. Accumulate results from valid final states.

Time Complexity: O(n^3)
Space Complexity: O(n^2)

*/
#include <cstdio>
#include <algorithm>

using namespace std;
const int o = 1010, MOD = 1e9 + 7;
int T, n, p[o], seq[o], cnt, f[o][o], ans;
bool ban[o][o];
inline bool chk(int pos, int v) { return p[pos] == -1 || p[pos] == v; }
int main() {
  for (scanf("%d", &T); T--; printf("%d\n", ans), ans = cnt = 0) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &p[i]);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        f[i][j] = ban[i][j] = 0;
    // Build a specific sequence: odd indices first, then even
    for (int i = 1; i <= n; i += 2)
      seq[++cnt] = i;
    for (int i = n; i; --i)
      if (i % 2 == 0)
        seq[++cnt] = i;
    // Mark bad intervals
    for (int i = 1; i <= n; ++i)
      for (int j = 0, t = i, mn = seq[t], mx = seq[t]; j < n;
           ++j, t = t % n + 1)
        if ((mx = max(mx, seq[t])) - (mn = min(mn, seq[t])) == j &&
            (mn == 1 || mx == n))
          ban[i][t] = 1;
    // Initialize base case: single elements can be filled
    for (int i = 1; i <= n; ++i)
      if (p[seq[i]] < 2)
        f[i][i] = 1;
    // Dynamic Programming for increasing lengths
    for (int len = 1; len < n - 1; ++len)
      for (int i = 1, j, t; i <= n; ++i)
        if (f[i][j = (i + len - 2) % n + 1]) {
          // Check if adding a new element to left or right maintains validity
          if (chk(seq[t = (i + n - 2) % n + 1], len + 1) &&
              (!ban[i][j] || !ban[t][j]))
            f[t][j] = (f[t][j] + f[i][j]) % MOD;
          if (chk(seq[t = j % n + 1], len + 1) && (!ban[i][j] || !ban[i][t]))
            f[i][t] = (f[i][t] + f[i][j]) % MOD;
        }
    // Count valid completions for full array
    for (int i = 1; i <= n; ++i)
      if (chk(seq[i], n))
        ans = (ans + f[i % n + 1][(i + n - 2) % n + 1]) % MOD;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/