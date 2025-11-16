// Problem: CF 1998 D - Determine Winning Islands in Race
// https://codeforces.com/contest/1998/problem/D

/*
Algorithm/Technique: Dynamic Programming + Difference Array + Game Theory
Time Complexity: O(n + m) per test case
Space Complexity: O(n + m) for storing the graph and auxiliary arrays

This solution determines for each starting position of Bessie whether she can win
the race against Elsie. It uses dynamic programming to compute minimum steps
to reach each island, and then uses a difference array technique to efficiently
mark positions where Bessie wins.

The key insight is that:
- Bessie can only use main bridges (i -> i+1)
- Elsie can use both main and alternative bridges
- The race alternates turns, with Bessie going first
- When a cow moves, the island collapses, and any bridge from that island is removed
- If both cows are on the same island, both are eliminated
- The first cow to reach island n wins

We model this using DP to compute how many steps Elsie needs to reach each island,
and use a difference array to mark which starting positions give Bessie a winning advantage.
*/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
#define Mxdt 100000
char pp[Mxdt], *p1 = pp, *p2 = pp;
#define nc()                                                                   \
  (p1 == p2 && (p2 = pp + fread(p1 = pp, 1, 100000, stdin), p1 == p2) ? -1     \
                                                                      : *p1++)
int read() {
  int x = 0;
  char c = 0;
  while (c != '-' && (c < '0' || c > '9'))
    c = nc();
  if (c == '-') {
    for (c = nc(); c >= '0' && c <= '9'; c = nc())
      x = (x << 3) + (x << 1) + (c ^ 48);
    return -x;
  }
  for (; c >= '0' && c <= '9'; c = nc())
    x = (x << 3) + (x << 1) + (c ^ 48);
  return x;
}
char Buf[Mxdt], *b1 = Buf, *b2 = Buf + Mxdt;
#define pu(a) ((*b1++ = (a)) && b1 == b2 && fwrite(b1 = Buf, 1, Mxdt, stdout))
const int MAXN = 2e5 + 5;
vector<int> v[MAXN]; // Adjacency list for alternative bridges
int u[MAXN], ans[MAXN]; // u[i] = min steps to reach island i for Elsie, ans array for difference array technique
int main() {
#ifdef BENDI
  freopen("a.in", "r", stdin);
#endif
  int t = read();
  while (t--) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
      v[i].clear(); // Clear adjacency list for each test case
      u[i] = 0x7fffffff; // Initialize to large value
      ans[i] = 0; // Clear answer array
    }
    for (int i = 1; i <= m; i++) {
      int x = read(), y = read();
      v[x].push_back(y); // Add alternative bridge from x to y
    }
    u[1] = 0; // Base case: Elsie starts at island 1, requires 0 steps
    for (int i = 1; i <= n; i++) {
      u[i] = min(u[i], u[i - 1] + 1); // Propagate minimum steps for main bridges (1->2->3->...->n)
      for (int j : v[i])
        u[j] = min(u[j], u[i] + 1); // Update minimum steps using alternative bridges
    }
    for (int i = 1; i <= n; i++) {
      for (int j : v[i]) {
        if (j - (u[i] + 1) > i) {
          // Use difference array to mark ranges for Bessie's advantage
          ans[i + 1]++; // Increment at start of range
          ans[j - (u[i] + 1)]--; // Decrement at end of range (exclusive)
        }
      }
    }
    for (int i = 1; i < n; i++) {
      ans[i] += ans[i - 1]; // Apply difference array prefix sum
      pu(ans[i] ? '0' : '1'); // Output 1 if Bessie wins, 0 otherwise
    }
    pu('\n'); // New line after each test case
  }
  fwrite(Buf, 1, b1 - Buf, stdout);
  return 0;
}


// https://github.com/VaHiX/CodeForces/