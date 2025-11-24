// Problem: CF 1956 F - Nene and the Passing Game
// https://codeforces.com/contest/1956/problem/F

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
const double eps = 1e-10;
const int mod = 1000000007;
const int kMaxN = 2e6;
int nxt[kMaxN], last_connected[kMaxN];
class DSU {
public:
  explicit DSU(int n) : parent(n), rank(n) {
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }
  int Find(int k) {
    for (; parent[k] != k; k = parent[k]) {
    }
    return k;
  }
  bool Union(int k, int l) {
    k = Find(k);
    l = Find(l);
    if (k == l)
      return false;
    if (rank[k] > rank[l])
      parent[l] = k;
    else {
      parent[k] = l;
      rank[l] = max(rank[l], rank[k] + 1);
    }
    return true;
  }

private:
  vector<int> parent;
  vector<int> rank;
};
// Function to find the last connected node in a range for a given node.
// This uses Union-Find structure to maintain connectivity between nodes.
int FindLastConnected(int l, int r, int n, DSU &dsu) {
  int nl = max(last_connected[l], nxt[l]);
  if (nl > r)
    return l;
  dsu.Union(n + l, n + nl);
  return last_connected[l] = FindLastConnected(nl, r, n, dsu);
}
void Solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> left_ints(n), right_ints(n);
  vector<int> elb(n), ele(n), erb(n), ere(n);
  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    // Compute the left intervals for i based on l and r
    if (i - l >= 0) {
      int il = max(0, i - r), ir = i - l;
      left_ints[i] = {il, ir};
      ++elb[il];
      ++ele[ir];
    };
    // Compute the right intervals for i based on l and r
    if (i + l <= n - 1) {
      int il = i + l, ir = min(n - 1, i + r);
      right_ints[i] = {il, ir};
      ++erb[il];
      ++ere[ir];
    };
  }
  vector<bool> used(n);
  int cnt_left = 0, cnt_right = 0;
  // Determine if each player can be used in a pass based on overlapping intervals
  for (int i = 0; i < n; ++i) {
    cnt_left += elb[i];
    cnt_right += erb[i];
    used[i] = cnt_left > 0 && cnt_right > 0;
    cnt_left -= ele[i];
    cnt_right -= ere[i];
  }
  elb.clear();
  ele.clear();
  erb.clear();
  ere.clear();
  DSU dsu(2 * n);
  int cur = n;
  // Precompute next valid index for each player
  for (int i = n - 1; i >= 0; --i) {
    nxt[i] = cur;
    if (used[i])
      cur = i;
  }
  for (int i = 0; i < n; ++i)
    last_connected[i] = i;
  // Process left intervals and connect relevant nodes in DSU
  for (int i = 0; i < n; ++i) {
    auto [l, r] = left_ints[i];
    if (!used[l])
      l = nxt[l];
    if (l <= r) {
      dsu.Union(i, n + l);
      FindLastConnected(l, r, n, dsu);
    }
  }
  // Process right intervals and connect relevant nodes in DSU
  for (int i = 0; i < n; ++i) {
    auto [l, r] = right_ints[i];
    if (!used[l])
      l = nxt[l];
    if (l <= r) {
      dsu.Union(i, n + l);
      FindLastConnected(l, r, n, dsu);
    }
  }
  // Count unique components (rounds needed) in DSU
  set<int> all;
  for (int i = 0; i < n; ++i)
    all.insert(dsu.Find(i));
  cout << all.size() << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
    Solve();
  return 0;
}

// https://github.com/VaHiX/CodeForces/