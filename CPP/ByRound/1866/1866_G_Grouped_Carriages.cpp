// Problem: CF 1866 G - Grouped Carriages
// https://codeforces.com/contest/1866/problem/G

/*
Algorithm: Binary search on answer + Greedy with Union-Find (Disjoint Set Union)
Purpose: Find the minimum possible maximum number of passengers in any carriage after redistribution.

Approach:
1. For each carriage i, determine the range [l, r] where passengers from carriage i can distribute.
   l = max(1, i - d[i]), r = min(n, i + d[i])
2. Sort intervals by their right endpoint.
3. Binary search on the answer (the value of Z).
4. For a given Z, use a greedy approach with Union-Find to simulate redistribution of passengers:
   - Use Union-Find to efficiently manage which carriages are available for redistribution.
   - Process intervals in order from left to right.
   - For each interval, greedily assign passengers to carriages with capacity < Z.

Time Complexity: O(N log N + N log(max_value))
Space Complexity: O(N)

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 3e5 + 10;
int a[N], d[N];
struct itv {
  int l, r, cnt;
  bool operator<(const itv &that) const { return r < that.r; } // Sort by right endpoint
} itvs[N];
int fa[N]; // Union-Find parent array
int findFa(int x) { return x == fa[x] ? x : fa[x] = findFa(fa[x]); } // Find with path compression
void del(int x) { fa[x] = x + 1; } // Mark a node as "deleted" (used for Union-Find)
int n;
int b[N]; // Current passenger count in each carriage during simulation
bool check(int k) {
  for (int i = 0; i <= n + 1; i++)
    fa[i] = i, b[i] = 0; // Initialize Union-Find and buffer
  for (int pos = 0; pos < n; pos++) {
    int cnt = itvs[pos].cnt, id;
    while (cnt && (id = findFa(itvs[pos].l)) <= itvs[pos].r) {
      int d = min(cnt, k - b[id]); // Determine how many passengers to move
      cnt -= d;
      b[id] += d;
      if (b[id] == k)
        del(id); // If full, mark as unavailable
    }
    if (cnt) // If some passengers were not moved, this k is not sufficient
      return false;
  }
  return true;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &d[i]);
  for (int i = 1; i <= n; i++) {
    itvs[i - 1] = {i - d[i], i + d[i], a[i]};
    if (itvs[i - 1].l < 1)
      itvs[i - 1].l = 1;
    if (itvs[i - 1].r > n)
      itvs[i - 1].r = n;
  }
  sort(itvs, itvs + n); // Sort intervals by right endpoint
  int lh = 0, rh = 1e9 + 10, ans = rh;
  while (lh <= rh) {
    int mid = (rh - lh) / 2 + lh;
    if (check(mid)) {
      ans = mid;
      rh = mid - 1;
    } else {
      lh = mid + 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/