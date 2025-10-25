// Problem: CF 2068 K - Amusement Park Rides
// https://codeforces.com/contest/2068/problem/K

/*
K. Amusement Park Rides
Algorithm: Greedy with Priority Queue and DFS-based Matching
Time Complexity: O(n log n + n^2)
Space Complexity: O(n)

This problem involves scheduling n attractions, each operating at intervals a_i,
where the i-th attraction operates at minutes a_i, 2*a_i, 3*a_i, ...
Each minute, 3 friends can either ride one attraction or wait.
We want to minimize the time to finish all attractions.

Approach:
- Group attractions by their interval values (a_i).
- Use a greedy approach with priority queue:
    - Process attractions grouped by the same interval in batches.
    - For each batch, use a max flow-like matching to assign attractions to friends.
    - If assignment is possible, update the time and add new attractions back.
- The solution uses a variant of maximum matching in bipartite graph.

Implementation Details:
- cap[i]: capacity (number of attractions) for group i
- match[i]: list of attractions matched to group i
- dfs(): performs depth-first search to find augmenting paths for matching
- pq: priority queue to process attractions in descending order of interval values
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
int cap[2020], rev[2020];
vector<int> match[2020];
bool vis[2020];
vector<int> e[4040];
map<int, int> cnt;
priority_queue<pll> pq;
vector<int> cand;

// DFS to find augmenting path for matching
bool dfs(int now) {
  for (auto nxt : e[now]) {
    if (vis[nxt])
      continue;
    vis[nxt] = 1;
    // If there's capacity, assign
    if (cap[nxt] > match[nxt].size()) {
      match[nxt].push_back(now);
      return 1;
    } else
      // Try to reassign an existing match
      for (int i = 0; i < match[nxt].size(); i++)
        if (dfs(match[nxt][i])) {
          match[nxt][i] = now;
          return 1;
        }
  }
  return 0;
}

// Initialize all data structures for a new test case
void init(int n) {
  for (int i = 1; i <= n; i++) {
    cap[i] = rev[i] = 0;
    match[i].clear();
  }
  for (int i = 1; i <= 2 * n; i++)
    e[i].clear();
  cnt.clear();
  while (pq.size())
    pq.pop();
  cand.clear();
}

void solve() {
  int n;
  cin >> n;
  int IDX = 0;
  init(n);
  // Count occurrences of each interval value
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    cnt[a]++;
  }
  // Assign group IDs and populate capacity and reverse mapping
  for (auto &[key, val] : cnt) {
    cap[++IDX] = val;
    rev[IDX] = key;
    pq.push({-key, IDX});
  }
  ll ans = 0;
  int iidx = 0;
  while (pq.size()) {
    ll tmp = pq.top().first;
    iidx++;
    // Process all attractions with same interval
    while (pq.size() && pq.top().first == tmp) {
      cand.push_back(pq.top().second);
      pq.pop();
      e[iidx].push_back(cand.back());
    }
    memset(vis, 0, sizeof(vis));
    // Try to match these attractions
    if (dfs(iidx)) {
      ans = tmp;
      // Add back modified attractions with updated times
      for (auto i : cand)
        pq.push({tmp - rev[i], i});
    }
    cand.clear();
  }
  cout << -ans << '\n';
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/