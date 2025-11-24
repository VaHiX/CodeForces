// Problem: CF 1917 F - Construct Tree
// https://codeforces.com/contest/1917/problem/F

/*
Code Purpose:
This code determines whether a tree can be constructed with n+1 nodes, such that:
1. Each of the n edges has a specified length from the input.
2. The weighted diameter of the tree equals a given value d.

It uses dynamic programming for initial checks and a BFS-based approach for more complex cases.

Algorithms/Techniques:
- Dynamic Programming: To check if a subset of edges sums up to a specific value (used in initial check)
- BFS (Breadth-First Search): For exploring possible configurations in a tree structure
- Sorting and Preprocessing: To optimize processing order

Time Complexity: O(n * d + 2^d) where n is the number of edges and d is the diameter.
Space Complexity: O(n * d + d^2) for DP table and auxiliary data structures.
*/

#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
#define fore(i, a, b) for (int i = a; i <= b; ++i)
#define pi pair<int, int>
const int N = 2e3 + 2;
struct Node {
  int p1, p2, id;
  Node(const int &a, const int &b, const int &c) { p1 = a, p2 = b, id = c; }
  const bool operator<(const Node &obj) const { return p1 < obj.p1; }
};
int n, d, curlen, nlen, flag, ri, a[N], pre[N], sufs[N];
bitset<N> dp[N];
bool Bfs() {
  priority_queue<Node> q;
  q.emplace(0, 0, 0);
  bitset<N> mark[N / 2];
  while (!q.empty()) {
    Node t = q.top();
    q.pop();
    curlen = t.p1 + t.p2;
    flag = 0;
    for (int i = n; i != 0; i = pre[i]) {
      if (flag)
        break;
      ri = pre[i] + 1;
      if (ri <= t.id && a[t.id] == a[ri])
        ri = t.id + 1, flag = 1;
      nlen = curlen + a[ri];
      if (nlen > d)
        break;
      if (!dp[ri + 1][d - nlen] || nlen + sufs[ri + 1] < d)
        continue;
      if (nlen == d) {
        if (max(t.p1 + a[ri], t.p2) + a[1] <= d)
          return 1;
        break;
      }
      Node v = Node(t.p1 + a[ri], t.p2, ri);
      if (v.p1 > v.p2)
        swap(v.p1, v.p2);
      auto update = [&]() {
        if (v.p2 + a[1] <= d && !mark[v.p1][v.p2])
          q.push(v), mark[v.p1][v.p2] = 1;
      };
      update();
      if (t.p1 != t.p2) {
        v = Node(t.p1, t.p2 + a[ri], ri);
        update();
      }
    }
  }
  return 0;
}
void solve() {
  cin >> n >> d;
  fore(i, 1, n) cin >> a[i];
  sort(a + 1, a + n + 1, greater<int>()); // Sort in descending order
  if (a[1] + a[2] > d) {      // If two largest edges exceed diameter, impossible
    cout << "No\n";
    return;
  }
  sufs[n + 1] = 0;
  for (int i = n; i >= 1; --i)  // Precompute suffix sums
    sufs[i] = sufs[i + 1] + a[i];
  fore(i, 1, n) pre[i] = (a[i] == a[i - 1] ? pre[i - 1] : i - 1); // Precompute previous index for same value
  for (int j = 0; j <= d; ++j)
    dp[n + 1][j] = 0;      // Initialize DP table
  dp[n + 1][0] = 1;
  for (int i = n; i >= 1; --i) {    // DP transitions
    for (int j = 0; j <= d; ++j)
      dp[i][j] = dp[i + 1][j];
    for (int j = a[i]; j <= d; ++j)
      dp[i][j] = dp[i][j] | dp[i + 1][j - a[i]];
  }
  if (dp[2][d - a[1]]) {            // Check if the tree can achieve diameter d
    cout << "Yes\n";
    return;
  }
  cout << (Bfs() ? "Yes" : "No") << "\n"; // BFS for edge cases
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/