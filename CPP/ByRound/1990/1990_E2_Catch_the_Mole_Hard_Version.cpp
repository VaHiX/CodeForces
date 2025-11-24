// Problem: CF 1990 E2 - Catch the Mole(Hard Version)
// https://codeforces.com/contest/1990/problem/E2

/*
Algorithm: Binary search on tree depth with smart parent query strategy
Time Complexity: O(n log n) per test case
Space Complexity: O(n) for storing tree structure and auxiliary arrays

Approach:
1. First, we preprocess the tree to find a good starting point (root of a subtree with bounded depth)
2. Then we perform a series of queries to:
   - Determine if the mole is in the subtree of a leaf node
   - Track mole movement by checking parent nodes
   - Use binary search logic on depths to efficiently locate the mole
*/

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;
namespace debug {
template <class c> struct rge {
  c b, e;
};
template <class c> rge<c> range(c i, c j) { return rge<c>{i, j}; }
template <class c> char spk(...);
template <class c> auto spk(c *a) -> decltype(cerr << *a, 0);
struct stream {
  ~stream() { cerr << endl; }
  template <class c>
  typename enable_if<sizeof spk<c>(0) != 1, stream &>::type operator<<(c i) {
    cerr << boolalpha << i;
    return *this;
  }
  template <class c>
  typename enable_if<sizeof spk<c>(0) == 1, stream &>::type operator<<(c i) {
    return *this << range(begin(i), end(i));
  }
  template <class a, class b> stream &operator<<(pair<a, b> p) {
    return *this << "(" << p.first << ", " << p.second << ")";
  }
  template <class c> stream &operator<<(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; it++)
      *this << ", " + 2 * (it == d.b) << *it;
    return *this << "]";
  }
  stream &_dbg(const string &s, int i, int b) { return *this; }
  template <class c, class... cs>
  stream &_dbg(const string &s, int i, int b, c arg, cs... args) {
    if (i == (int)(s.size()))
      return (*this << ": " << arg);
    b += (s[i] == '(') + (s[i] == '[') + (s[i] == '{') - (s[i] == ')') -
         (s[i] == ']') - (s[i] == '}');
    return (s[i] == ',' && b == 0)
               ? (*this << ": " << arg << "     ")._dbg(s, i + 1, b, args...)
               : (s[i] == ' ' ? *this : *this << s[i])
                     ._dbg(s, i + 1, b, arg, args...);
  }
};
} // namespace debug
#ifdef DEBUG
#define dout debug::stream()
#define dbg(...)                                                               \
  ((dout << "line:" << __LINE__ << " >> ")                                     \
       ._dbg(#__VA_ARGS__, 0, 0, __VA_ARGS__))
#else
#define dout
#define dbg(...)
#endif
#define rep(a, b) for (int a = 0; a < (b); a++)
#define all(a) (a).begin(), (a).end()
using ll = long long;
const int QUERY_LIMIT = 300;
int query_count = 0;
bool Query(int x) {
  query_count++;
  cout << "? " << x << endl;
  int y;
  cin >> y;
  return y;
}
void Answer(int x) { cout << "! " << x << endl; }
const int N = 5e3 + 7;
vector<int> V[N];
bool vis[N];
int depth[N], parent[N];
void Init(int n) {
  rep(i, n + 1) {
    V[i].clear();
    vis[i] = false;
    depth[i] = 0;
    parent[i] = 0;
  }
  query_count = 0;
}
void FillSubtree(int v, int father) {
  vis[v] = true;
  for (int u : V[v]) {
    if (u == father || vis[u])
      continue;
    FillSubtree(u, v);
  }
}
pair<int, int> GetStats(int v, int father) {
  int max_depth = 1, subtree_size = 1;
  for (int u : V[v]) {
    if (u == father || vis[u])
      continue;
    auto [d, s] = GetStats(u, v);
    max_depth = max(max_depth, d + 1);
    subtree_size += s;
  }
  return {max_depth, subtree_size};
}
int Preprocessing(int v, int father, int c) {
  depth[v] = 1;
  parent[v] = father;
  for (int u : V[v]) {
    if (u == father)
      continue;
    int r = Preprocessing(u, v, c);
    if (r != -1)
      return r;
    depth[v] = max(depth[v], depth[u] + 1);
  }
  if (depth[v] == c || v == 1) {
    bool found = Query(v);
    if (found) {
      return v;
    }
    depth[v] = 0;
    FillSubtree(v, father);
  }
  return -1;
}
int FindLeaf(int v, int father) {
  for (int u : V[v]) {
    if (u == father || vis[u])
      continue;
    return FindLeaf(u, v);
  }
  return v;
}
void Solve() {
  int n;
  cin >> n;
  Init(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    V[a].push_back(b);
    V[b].push_back(a);
  }
  int r = Preprocessing(1, 1, 71);
  int l = FindLeaf(r, parent[r]);
  vector<int> parents = {parent[r]};
  for (int i = 0; i < 8; i++) {
    parents.push_back(parent[parents.back()]);
  }
  reverse(parents.begin(), parents.end());
  auto check_root = [&parents](int rr) {
    bool res = Query(rr);
    if (res)
      return false;
    for (int p : parents) {
      res = Query(p);
      if (!res) {
        Answer(parent[parent[p]]);
        return true;
      }
    }
    Answer(parent[rr]);
    return true;
  };
  auto [rd, rs] = GetStats(r, parent[r]);
  assert(rd <= 71);
  assert(query_count <= 71);
  if (r == 1) {
    for (int i = 1; i <= rd; i++) {
      bool res = Query(l);
      if (res) {
        Answer(l);
        return;
      }
    }
    Answer(1);
    return;
  }
  for (int i = 1; i <= rd; i++) {
    bool res = Query(l);
    if (res) {
      Answer(l);
      return;
    }
    if (i == rd || i % 8 == 0) {
      if (check_root(r)) {
        return;
      }
    }
  }
  Answer(r);
}
int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/