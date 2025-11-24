// Problem: CF 1972 F - Long Way to be Non-decreasing
// https://codeforces.com/contest/1972/problem/F

/*
Algorithm: 
This solution uses a graph-based approach to determine the minimum number of magic tricks needed to make an array non-decreasing. It treats each element of the array and the magic transformation as nodes in a directed graph. The key insights are:
1. If we can only transform an element, we can think of it as moving through a cycle in the graph defined by b[i] -> i.
2. The solution applies binary search on the number of tricks, and for each number, it checks if it's feasible to make the array non-decreasing.

Time Complexity: O(m * log(m) + n * log(m))
Space Complexity: O(m + n)

The approach uses the fact that the value of each element evolves over time according to the function b. We build a graph structure to efficiently traverse this evolution, and then determine how many steps of transformation are needed.
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui64 = ull;
#define pii pair<int, int>
#define vi vector<int>
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(x) (x).begin(), (x).end()
#define mp make_pair
#define fs first
#define sc second
#define next hunext
#define prev huprev
#define hash huhash
const int N = 1e6 + 100;
int timer;
bool used[N], in_cyc[N];
int a[N], b[N], h[N], cyc_sz[N], cyc[N], cyc_pos[N], prev_in_cyc[N], tin[N],
    tout[N];
vi g[N];
void dfs(int v, int deep, int cyc_num, int cyc_v) {
  tin[v] = timer++;
  used[v] = true;
  h[v] = deep;
  cyc[v] = cyc_num;
  prev_in_cyc[v] = cyc_v;
  for (int u : g[v]) {
    if (!in_cyc[u]) {
      dfs(u, deep + 1, cyc_num, cyc_v);
    }
  }
  tout[v] = timer++;
}
void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
  }
  for (int i = 1; i <= m; ++i) {
    used[i] = in_cyc[i] = false;
    g[i].clear();
  }
  for (int i = 1; i <= m; ++i) {
    g[b[i]].pb(i);
  }
  int k = 0;
  timer = 0;
  for (int i = 1; i <= m; ++i) {
    if (used[i]) {
      continue;
    }
    int cyc_ver = i;
    while (!used[cyc_ver]) {
      used[cyc_ver] = true;
      cyc_ver = b[cyc_ver];
    }
    int ver = cyc_ver;
    cyc_sz[k] = 0;
    for (;;) {
      in_cyc[ver] = true;
      cyc_pos[ver] = cyc_sz[k]++;
      ver = b[ver];
      if (ver == cyc_ver) {
        break;
      }
    }
    for (;;) {
      dfs(ver, 0, k, ver);
      ver = b[ver];
      if (ver == cyc_ver) {
        break;
      }
    }
    ++k;
  }
  int ans = -1, l = 0, r = m;
  while (l <= r) {
    int mid = (l + r) / 2;
    int x = 1;
    for (int i = 0; i < n; ++i) {
      while (x <= m) {
        if (cyc[x] != cyc[a[i]]) {
          ++x;
          continue;
        }
        int dist = 0;
        if (in_cyc[a[i]]) {
          if (!in_cyc[x]) {
            ++x;
            continue;
          }
          if (cyc_pos[x] >= cyc_pos[a[i]]) {
            dist = cyc_pos[x] - cyc_pos[a[i]];
          } else {
            dist = cyc_sz[cyc[x]] - cyc_pos[a[i]] + cyc_pos[x];
          }
        } else {
          if (in_cyc[x]) {
            int y = prev_in_cyc[a[i]];
            dist += h[a[i]];
            if (cyc_pos[x] >= cyc_pos[y]) {
              dist += cyc_pos[x] - cyc_pos[y];
            } else {
              dist += cyc_sz[cyc[x]] - cyc_pos[y] + cyc_pos[x];
            }
          } else {
            if (tin[x] <= tin[a[i]] && tout[a[i]] <= tout[x]) {
              assert(h[a[i]] >= h[x]);
              dist += h[a[i]] - h[x];
            } else {
              ++x;
              continue;
            }
          }
        }
        if (dist <= mid) {
          break;
        }
        ++x;
      }
      if (x > m) {
        break;
      }
    }
    if (x <= m) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef LOCAL42
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int t = 1;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/