// Problem: CF 1785 A - Monsters (easy version)
// https://codeforces.com/contest/1785/problem/A

/*
A. Monsters (easy version)
Algorithms/Techniques: Greedy algorithm with sorting

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing monster health points

The problem is about minimizing the number of Type 1 spells (single target damage)
by optimally using one Type 2 spell (all-target damage) that can trigger repetitions.

Strategy:
- Sort monster health in ascending order.
- Use greedy approach to determine how many Type 1 spells are needed.
- When we encounter a monster whose health is greater than the current "target"
  (tp), we need to use Type 1 spells to reduce it to tp+1, then we increment tp.
- The difference (a[i] - tp - 1) represents the number of Type 1 spells needed
  for this transition.
*/

#include <algorithm>
#include <cstdio>
using namespace std;
int T, n, a[200005];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    sort(a + 1, a + n + 1); // Sort health values in ascending order
    long long ans = 0ll;
    int tp = 0; // 'tp' represents the target health value we want to reach for next monster
    for (int i = 1; i <= n; i++) {
      if (a[i] <= tp)
        continue; // If current monster's health is already <= target, skip
      ans += (a[i] - tp - 1); // Number of Type 1 spells needed to bring this monster to tp+1
      tp++; // Increment the target for next monster
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/