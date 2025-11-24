// Problem: CF 1257 D - Yet Another Monster Killing Problem
// https://codeforces.com/contest/1257/problem/D

/*
D. Yet Another Monster Killing Problem

Algorithms/Techniques: Binary search on answer + greedy approach with precomputation

Time Complexity: O(n * log(n) + m * log(n))
Space Complexity: O(n + m)

This problem involves finding the minimum number of days required to defeat all monsters,
where each day exactly one hero is used, and heroes have power and endurance limits.
The solution uses binary search on the answer combined with a greedy check:
- For a given number of days, we determine if it's possible to defeat all monsters.
- A greedy approach checks whether monsters can be defeated using available heroes
  without exceeding their endurance constraints.

*/

#include <stdio.h>
#include <algorithm>

#define MAXN 200005
using namespace std;
int n, m, ans, x, y, T, a[MAXN], c[MAXN];

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    c[0] = ans = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), c[i] = 0; // Read monster powers and initialize cost array
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
      scanf("%d %d", &x, &y), c[y] = max(c[y], x); // Store maximum power needed for endurance y
    for (int i = n - 1; i; i--)
      c[i] = max(c[i + 1], c[i]); // Precompute prefix max: c[i] = max of c[i], c[i+1], ..., c[n]
    for (int i = 1; i <= n && ~ans;) {
      ++ans;
      int j = i, mx = 0;
      while (true) {
        mx = max(mx, a[j]); // Track maximum monster power in current sequence
        if (mx > c[j - i + 1]) // If required power exceeds what's allowed for this length
          break;
        ++j; // Continue with next monster
      }
      if (j == i)
        ans = -1; // No progress made, impossible to proceed
      i = j; // Move to next unprocessed monster
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/