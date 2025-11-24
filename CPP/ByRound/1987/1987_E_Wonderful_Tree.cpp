// Problem: CF 1987 E - Wonderful Tree!
// https://codeforces.com/contest/1987/problem/E

/**
 * @brief Problem: Make a tree wonderful by increasing vertex values.
 *        A tree is wonderful if for each node with children, its value is <= sum of children's values.
 *        Goal: Find minimum operations to make tree wonderful by incrementing vertex values.
 * 
 * @details Algorithm: 
 *          1. Build tree from parent array
 *          2. DFS traversal to compute subtree sums and determine required operations
 *          3. For each node, if it violates the condition (node value > sum of children):
 *              - Add it to a priority queue with cost 1
 *              - Otherwise, redistribute excess from children
 *          4. Use greedy approach to minimize operations by combining costs
 * 
 * @time Complexity: O(n log n) - Each node processed once, heap operations take log n time
 * @space Complexity: O(n) - For storing tree, sums, and heap data structures
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

#define sz(x) signed(size(x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define ru(x) (x).resize(unique(begin(x), end(x)) - begin(x))
#define sru(x) sort(all(x)), (x).resize(unique(begin(x), end(x)) - begin(x))
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define Yn(x) ((x) ? "Yes" : "No")
#define YN(x) ((x) ? "YES" : "NO")
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pli = pair<long long, int>;
using pil = pair<int, long long>;
using pll = pair<long long, long long>;
template <typename T, typename U>
istream &operator>>(istream &in, pair<T, U> &pr) {
  in >> pr.first >> pr.second;
  return in;
}
template <typename T, typename U>
ostream &operator<<(ostream &out, pair<T, U> &pr) {
  out << pr.first << ' ' << pr.second;
  return out;
}
template <typename T> using vc = vector<T>;
using vi = vector<int>;
using vll = vector<long long>;
template <typename T> using vvc = vc<vc<T>>;
using vvi = vector<vector<int>>;
using vvll = vector<vector<long long>>;
template <typename T> istream &operator>>(istream &in, vector<T> &v) {
  for (T &i : v)
    in >> i;
  return in;
}
template <typename T> ostream &operator<<(ostream &out, vector<T> &v) {
  if (!v.empty())
    out << v[0];
  for (int i = 1; i < sz(v); ++i)
    out << ' ' << v[i];
  return out;
}
const int mod = 1e9 + 7;
#define endl '\n'
using heap = priority_queue<pii, vector<pii>, greater<pii>>;
ll ans;
void dfs(int cur, vi &a, vll &sum, vc<heap> &hp, const vvi &edges) {
  if (sz(edges[cur]) == 0)
    sum[cur] = 1e18; // Leaf node, set high value to avoid immediate comparison
  else
    for (int nxt : edges[cur]) {
      dfs(nxt, a, sum, hp, edges);
      sum[cur] += a[nxt]; // Calculate sum of all children
    }
  if (sum[cur] > a[cur])
    hp[cur].emplace(1, cur); // If violation, add to heap with cost 1
  else {
    heap tmp;
    for (int nxt : edges[cur])
      while (!hp[nxt].empty()) {
        tmp.emplace(hp[nxt].top().fi, hp[nxt].top().se); // Move all children's operations to tmp heap
        hp[nxt].pop();
      }
    ll lack = a[cur] - sum[cur]; // Calculate how much we need to increase sum to be >= node value
    while (lack > 0) {
      auto [len, id] = tmp.top();
      if (lack >= sum[id] - a[id]) {
        tmp.pop();
        lack -= sum[id] - a[id]; // Deduct what we gain from increasing this node
        ans += 1LL * (sum[id] - a[id]) * len; // Add operations cost to total
        for (int nnxt : edges[id])
          while (!hp[nnxt].empty()) {
            tmp.emplace(len + hp[nnxt].top().fi, hp[nnxt].top().se); // Propagate the increased cost
            hp[nnxt].pop();
          }
      } else {
        a[id] += lack;
        ans += 1LL * lack * len; // Only increase until satisfied
        lack = 0;
      }
    }
    while (!tmp.empty()) {
      hp[cur].emplace(tmp.top().fi + 1, tmp.top().se); // Put back adjusted costs to parent heap
      tmp.pop();
    }
  }
  return;
}
inline void Ac() {
  int n;
  cin >> n;
  vi a(n);
  cin >> a;
  vvi edges(n);
  for (int i = 1, p; i < n; ++i) {
    cin >> p;
    edges[p - 1].eb(i); // Build tree using parent array
  }
  ans = 0;
  vll sum(n);
  vc<heap> hp(n);
  dfs(0, a, sum, hp, edges); // Start DFS from root
  cout << ans << endl;
  return;
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t = 1;
  cin >> t;
  while (t--)
    Ac();
  return 0;
}


// https://github.com/VaHiX/CodeForces/