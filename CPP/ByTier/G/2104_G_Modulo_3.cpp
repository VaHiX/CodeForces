// Problem: CF 2104 G - Modulo 3
// https://codeforces.com/contest/2104/problem/G

/*
G. Modulo 3
Algorithms/Techniques: 
- Functional graph with dynamic updates
- DSU (Disjoint Set Union) with rollback support
- Persistent segment tree for managing updates over time
- Offline processing of queries

Time Complexity: O((n + q) * α(n) * log(q)) where α is the inverse Ackermann function
Space Complexity: O(n * log(q))

*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define mk make_pair
#define For(i, il, ir) for (int i = (il); i <= (ir); ++i)
#define Rof(i, ir, il) for (int i = (ir); i >= (il); --i)
using namespace std;
typedef pair<int, int> pii;
const int maxn = 2e5 + 10;
int n, Q;
int k[maxn];
int pa[maxn], pt[maxn]; // pa: parent array, pt: time stamp when node changed
#define mid (l + r >> 1)
pii opz; // operation value for update
int opx, opy; // operation range x and y
vector<pii> tr[maxn << 2]; // segment tree storing updates per range

void update(int o, int l, int r) {
  if (opx <= l && r <= opy) {
    tr[o].push_back(opz); // add event in current node's segment
    return;
  }
  if (opx <= mid)
    update(o << 1, l, mid);
  if (opy > mid)
    update(o << 1 | 1, mid + 1, r);
}

void update(int l, int r, pii v) {
  opx = l, opy = r, opz = v;
  update(1, 0, Q); // call update on root
}

int tp, ans; // tp: stack pointer for undo; ans: current answer
pii st[maxn]; // stack to store undo info

int fa[maxn], val[maxn], h[maxn]; // DSU arrays: parent, value, height
int fd(int x, int &v) { // find root and calculate accumulated xor value
  v = 0;
  while (x ^ fa[x])
    v ^= val[x], x = fa[x];
  return x;
}

void merge(int x, int y) {
  int vx, vy;
  x = fd(x, vx), y = fd(y, vy);
  if (x == y)
    ans ^= vx ^ vy; // toggle answer when same component
  else {
    if (h[x] > h[y])
      swap(x, y);
    st[++tp] = make_pair(x, h[x] == h[y]); // store rollback info
    fa[x] = y, val[x] = vx ^ vy ^ 1, h[y] += (h[x] == h[y]);
  }
}

void undo(int tar) { // undo operations from the stack to time `tar`
  while (tp > tar) {
    int x = st[tp].first, d = st[tp].second;
    h[fa[x]] -= d, fa[x] = x, val[x] = 0, tp--;
  }
}

int res[maxn]; // stores final result of each query

void dfs(int o, int l, int r) {
  int pretp = tp, preans = ans; // preserve state before processing
  for (pii c : tr[o]) // process all operations added in this segment
    merge(c.first, c.second);
  if (l == r)
    res[l] = ans; // if leaf, store the result
  else {
    dfs(o << 1, l, mid), dfs(o << 1 | 1, mid + 1, r); // proceed to children
  }
  undo(pretp); // rollback to previous state
  ans = preans;
}

signed main() {
  scanf("%d%d", &n, &Q);
  For(i, 1, n) scanf("%d", &pa[i]), fa[i] = i, h[i] = 1; // initialize DSU
  For(i, 1, Q) {
    int x, y;
    scanf("%d%d%d", &x, &y, &k[i]);
    update(pt[x], i - 1, mk(x, pa[x])); // store updates in the segment tree
    pa[x] = y, pt[x] = i;
  }
  For(i, 1, n) update(pt[i], Q, mk(i, pa[i])); // add final parent information
  ans = n & 1; // initialize global answer with parity of n
  dfs(1, 0, Q); // process all queries using DFS on segment tree
  For(i, 1, Q) printf("%d\n", k[i] % 3 ? (res[i] ? k[i] % 3 : 1) : 0);
  return 0;
}


// https://github.com/VaHiX/codeForces/