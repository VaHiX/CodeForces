// Problem: CF 1945 G - Cook and Porridge
// https://codeforces.com/contest/1945/problem/G

/*
 * Problem: G. Cook and Porridge
 * 
 * Purpose: Simulate a queue system where schoolchildren are served porridge
 *          with different priorities and eating times. The task is to find
 *          the minimum time each child receives at least one portion within D minutes.
 *          Children return to the queue after eating, with priority-based ordering.
 * 
 * Algorithms/Techniques:
 *   - Priority queues to manage children being served and those waiting to return
 *   - Preprocessing to compute maximum priority from current position to end
 *   - Simulation over time steps up to D minutes
 * 
 * Time Complexity: O(n * log n + D * log n)
 *   - Preprocessing: O(n)
 *   - Simulation per minute: O(log n) per operation due to priority queue
 *   - Total: O(n + D * log n)
 * 
 * Space Complexity: O(n)
 *   - Storage for children data, queues, and max_v array
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <functional>

struct child {
  int indice, t, w, s;
  bool operator>(const child &c) const { return t > c.t; }
  bool operator<(const child &c) const {
    if (w == c.w) {
      if (t == c.t)
        return s > c.s;
      return t > c.t;
    }
    return w < c.w;
  }
};

void solve() {
  int n, d;
  std::scanf("%d %d", &n, &d);
  int v[n + 1], s[n + 1], max_v[n + 1];
  std::memset(max_v, 0, sizeof(max_v));
  for (int i = 1; i <= n; ++i) {
    std::scanf("%d %d", &v[i], &s[i]);
  }
  // Preprocessing to calculate max priority from right to left
  max_v[n] = v[n];
  for (int i = n - 1; i >= 1; --i) {
    max_v[i] = std::max(max_v[i + 1], v[i]);
  }
  // Q1: Queue of children ready to return to the line (waiting to rejoin)
  // Q2: Queue of children currently being served or ready to be served
  std::priority_queue<child, std::vector<child>, std::greater<child>> Q1;
  std::priority_queue<child, std::vector<child>, std::less<child>> Q2;
  int pos = 1, ans;
  // Simulation over D minutes
  for (ans = 1; ans <= d; ++ans) {
    // Move any children who have finished eating back to Q1
    while (!Q1.empty() && Q1.top().t <= ans) {
      Q2.push(Q1.top());
      Q1.pop();
    }
    // If Q2 is empty or if the next child to serve has lower priority than max_v[pos],
    // serve the next child in original order
    if (Q2.empty() || Q2.top().w <= max_v[pos]) {
      Q1.push({pos, ans + s[pos] + 1, v[pos], s[pos]});
      pos++;
    } else {
      // Otherwise, serve the child from Q2 based on priority
      child temp = Q2.top();
      Q2.pop();
      Q1.push({temp.indice, ans + s[temp.indice] + 1, v[temp.indice],
               s[temp.indice]});
    }
    if (pos == n + 1)
      break;  // All children have been served at least once
  }
  if (ans <= d)
    std::printf("%d\n", ans);
  else
    std::printf("%d\n", -1);
}

int main() {
  int t;
  std::scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/