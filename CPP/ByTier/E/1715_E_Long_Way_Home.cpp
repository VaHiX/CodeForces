// Problem: CF 1715 E - Long Way Home
// https://codeforces.com/contest/1715/problem/E

/*
 * Problem: E. Long Way Home
 * 
 * Approach:
 * - This problem combines Dijkstra's shortest path algorithm with a technique for 
 *   optimizing the cost of using flights (which cost (u - v)^2).
 * - The key insight is to use a convex hull optimization (or more precisely, 
 *   a "sweep" based on slopes) to efficiently compute the best flight path from 
 *   previous state to current state.
 * - We perform Dijkstra for each iteration to find the shortest paths using only 
 *   roads, then use a convex hull trick to determine optimal flights.
 * 
 * Time Complexity: O((m + n) * log n + n * k) where k <= 20
 * Space Complexity: O(n + m)
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <utility>

#define N 100005
using namespace std;
int n, m, k, head[N], tot, v[N], s[N], top;
long long d[N], dn[N];
struct edge {
  int to, nxt, val;
} e[N << 1];
void add(int x, int y, int z) { e[++tot] = {y, head[x], z}, head[x] = tot; }
void dijkstra() {
  memset(v, 0, sizeof v);
  priority_queue<pair<int, int>> q;
  for (int i = 1; i <= n; i++)
    q.push({-d[i], i});
  while (q.size()) {
    int x = q.top().second;
    q.pop();
    if (v[x])
      continue;
    v[x] = 1;
    for (int i = head[x], y; y = e[i].to, i; i = e[i].nxt)
      if (d[y] > d[x] + e[i].val)
        d[y] = d[x] + e[i].val, q.push({-d[y], y});
  }
}
double slope(int x, int y) {
  return (1.0 * x * x + d[x] - 1.0 * y * y - d[y]) / (x - y);
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, x, y, z; i <= m; i++)
    scanf("%d%d%d", &x, &y, &z), add(x, y, z), add(y, x, z);
  memset(d, 0x3f, sizeof d);
  d[1] = 0, dijkstra(); // Initial Dijkstra without any flights
  while (k--) {
    top = 0;
    for (int i = 1; i <= n; i++) {
      // Maintain a convex hull by removing points that have worse slopes
      while (top > 1 && slope(s[top - 1], i) < slope(s[top - 1], s[top]))
        top--;
      s[++top] = i;
    }
    for (int i = 1, j = 1; i <= n; i++) {
      // Sweep the convex hull to find the optimal line for current city
      while (j < top && slope(s[j], s[j + 1]) < 2.0 * i)
        j++;
      dn[i] = d[s[j]] + 1ll * (i - s[j]) * (i - s[j]);
    }
    for (int i = 1; i <= n; i++)
      d[i] = min(d[i], dn[i]); // Update distances with possible flight use
    dijkstra(); // Reprocess shortest paths after considering flights
  }
  for (int i = 1; i <= n; i++)
    printf("%lld ", d[i]);
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/