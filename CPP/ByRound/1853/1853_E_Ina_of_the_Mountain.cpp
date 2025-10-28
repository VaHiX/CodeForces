// Problem: CF 1853 E - Ina of the Mountain
// https://codeforces.com/contest/1853/problem/E

/*
E. Ina of the Mountain
Algorithm: Greedy + Priority Queue
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem is about minimizing the number of boulders to make all octopuses have health k.
Each boulder reduces health of a range by 1, and any octopus with health 0 regenerates to k.

Approach:
- Process octopuses from left to right.
- For each octopus, if current health is greater than previous, we need to apply a boulder to cover the difference.
- Use a min-heap to keep track of required boulders and their coverage ranges.
- The key idea is that when health increases from prev to curr, we add (curr - prev) to our answer.
  When it decreases, we calculate how many boulders are needed for wraparound.

We model this as applying operations to make all values equal to k by greedily choosing 
the minimal number of operations based on difference in health values.
*/

#include <functional>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;
#define ll long long

void solve() {
  int n, k, x, pre, i, j;
  ll ans;
  scanf("%d %d", &n, &k);
  priority_queue<int, vector<int>, greater<int>> q; // min-heap to store required boulder counts
  ans = 0, pre = 0;
  for (i = 1; i <= n; i++) {
    scanf("%d", &x);
    x %= k; // Reduce to equivalent health in [0, k)
    if (x > pre) {
      // If current health is higher than previous, we need to use the smallest boulder
      q.push(x - pre); // Push difference, i.e., number of boulders needed from this jump
      ans += q.top();  // Add minimum number of boulders used so far
      q.pop();         // Remove used boulder count since we already accounted for it
    } else {
      // If current health is lower than previous (wrap around), we need to take all the way from pre to k,
      // then from 0 to x.
      q.push(k + x - pre);  // Wraparound case: boulders covering transition through k
    }
    pre = x; // Update previous health value for next iteration
  }
  printf("%lld\n", ans);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/