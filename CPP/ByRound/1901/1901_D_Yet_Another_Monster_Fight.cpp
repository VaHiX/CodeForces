// Problem: CF 1901 D - Yet Another Monster Fight
// https://codeforces.com/contest/1901/problem/D

/*
Algorithm: Greedy + Preprocessing
Time Complexity: O(n)
Space Complexity: O(n)

This problem requires finding the minimum initial spell power x such that
all monsters can be killed regardless of the random order of hits (as long as
the adjacency constraint is maintained). The key insight is to:
1. Precompute for each starting position the maximum damage any monster
   could receive in the worst-case scenario (i.e., when the chain is arranged
   to minimize the required power).
2. For each possible first target, we compute the minimum spell power needed
   to ensure all monsters are defeated, considering the worst-case hit order.
3. The worst-case order occurs when we allow the chain to distribute damage
   in the most unfavorable way for the spell's initial power.

The preprocessing steps involve:
- Left-to-right pass: for each position, calculate the worst-case damage
  (max damage a monster at index i can take)
- Right-to-left pass: similar but from the other side
- Then, for each possible first monster, compute the required power and take
  the overall minimum.
*/

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int x = 0; x < n; x++)
    cin >> a[x];
  vector<int> cost(n);
  int now = 0;
  for (int x = 0; x < n; x++)
    cost[x] = max(cost[x], now), now = max(now, a[x] + n - x - 1);
  now = 0;
  for (int x = n - 1; x >= 0; x--)
    cost[x] = max(cost[x], now), now = max(now, a[x] + x);
  int ans = 2e9;
  for (int x = 0; x < n; x++)
    ans = min(ans, max(cost[x], a[x]));
  cout << ans << endl;
}
int main() {
  int t = 1;
  while (t--)
    solve();
}

// https://github.com/VaHiX/CodeForces/