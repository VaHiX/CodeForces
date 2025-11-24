// Problem: CF 2164 H - PalindromePalindrome (enhanced file)
// https://codeforces.com/problemset/problem/2164/H
//
// Overview:
// This implementation builds an eertree (palindromic tree) over the input
// string and uses a combination of data structures (Fenwick tree + two
// segment trees) to answer queries about longest palindromic substrings that
// intersect a given interval. The code is optimized for large constraints
// (n, q up to 5e5) and uses low-level memory management for speed.
//
// Main ideas:
// - Eertree (palindromic tree) stores all distinct palindromic substrings and
//   links between them. Nodes represent palindromes and have lengths len[i].
// - DFS numbering (ta/tb) is used to map subtree ranges for subtree queries.
// - Fenwick tree (ft) keeps maximum palindrome lengths ending at positions.
// - A point segment tree (st1) stores, for each node, the latest position where
//   a palindrome from that node was seen.
// - A range-update segment tree (st2) stores heavy periodic contributions for
//   long palindromes with arithmetic progression of centers.
//
// Complexity: roughly O(n log n + q log n) amortized across updates and
// queries; low-level optimizations and small K constant handle periodic parts.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 500000
#define Q 500000
#define N_ (1 << 19)
#define A 26
#define K 4

// small inline for max (used heavily)
int max(int a, int b) { return a > b ? a : b; }

// input string (0-indexed) and its length
char cc[N + 1];
int n;
void append(int **ej, int *eo, int i, int j) {
  // Dynamic append to adjacency-like list ej[i]
  // ej: array of int* (each points to a dynamically sized list)
  // eo: array of sizes (current next index)
  int o = eo[i]++;
  // If capacity reached (o is power of two and >=2) double allocation
  if (o >= 2 && (o & o - 1) == 0)
    ej[i] = (int *)realloc(ej[i], o * 2 * sizeof *ej[i]);
  ej[i][o] = j; // store new element
}
int tt[N + 2][A], fff[N + 2][A], ff[N + 2], ff_[N + 2], len[N + 2];
int *ev[N + 2], eo[N + 2], ta[N + 2], tb[N + 2];
int node(int l) {
  static int _;
  len[_] = l;
  ev[_] = (int *)malloc(2 * sizeof *ev[_]);
  return _++;
}
void dfs(int u) {
  static int t_;
  int o;
  ta[u] = t_++;
  for (o = eo[u]; o--;) {
    int v = ev[u][o];
    dfs(v);
  }
  tb[u] = t_;
}
int uu[N + 1];
// Build palindromic tree (eertree) for the string in cc[0..n-1]
// Nodes are allocated using node(len) and stored in arrays tt/fff/ff/ff_/len
// ev/e o arrays form a parent->children adjacency used for DFS ordering
// uu[pos] stores the node corresponding to the longest suffix-palindrome
// ending at position pos-1 (1-based pos in uu)
void eertree() {
  int i, a, u;
  // create two root nodes: node 0 with length 0, node 1 with length -1
  node(0), node(-1);
  // initialize suffix-links base cases
  for (a = 0; a < A; a++)
    fff[0][a] = fff[1][a] = 1;
  ff[0] = ff_[0] = 1;
  // attach node 0 as child of node 1 to make a rooted tree at node 1
  append(ev, eo, 1, 0);
  uu[0] = u = 0;

  // iterate characters and extend eertree
  for (i = 0; i < n; i++) {
    a = cc[i] - 'a';
    // follow suffix links until we can extend by cc[i]
    if (i <= len[u] || cc[i - 1 - len[u]] != a + 'a')
      u = fff[u][a];
    if (!tt[u][a]) {
      // create new node for palindrome of length len[u]+2
      int v = node(len[u] + 2), f = tt[fff[u][a]][a];
      ff[v] = f;
      // ff_ stores special link used for fast jumps on equal-period palindromes
      ff_[v] = f == 0 || len[v] - len[f] != len[f] - len[ff[f]] ? f : ff_[f];
      // copy transition table from suffix f and update one entry
      memcpy(fff[v], fff[f], sizeof fff[f]);
      fff[v][cc[i - len[f]] - 'a'] = f;
      // add as child of f for later DFS traversal
      append(ev, eo, f, v);
      tt[u][a] = v;
    }
    // record node corresponding to longest suffix palindrome at position i+1
    uu[i + 1] = u = tt[u][a];
  }
  // compute DFS tin/tout on tree rooted at node 1
  dfs(1);
}
int ft[N];
void ft_update(int i, int x) {
  // Fenwick-like update that stores prefix maximums for queries by index
  // Here ft[] is used with a custom update rule to propagate maximum values
  while (i < n) {
    ft[i] = max(ft[i], x);
    i |= i + 1; // move to next index covering range
  }
}
int ft_query(int i) {
  // Query the maximum value in prefix [0..i]
  int x = -1;
  while (i >= 0) {
    x = max(x, ft[i]);
    i &= i + 1, i--;
  }
  return x;
}
int st1[N_ * 2], st2[N_ * 2], n_;
void build() {
  // Initialize Fenwick-like array and segment trees
  memset(ft, 0, n * sizeof *ft);
  // Build power-of-two size for segment tree base
  n_ = 1;
  while (n_ < n + 2)
    n_ <<= 1;
  // st1: point segment tree for max queries (stores latest index per node)
  // st2: range-assignment segment tree (lazy-less) storing max over intervals
  memset(st1, -1, n_ * 2 * sizeof *st1);
  memset(st2, -1, n_ * 2 * sizeof *st2);
}
void st1_pul(int i) { st1[i] = max(st1[i << 1 | 0], st1[i << 1 | 1]); }
void st1_update(int i, int x) {
  // Point-update: set st1[pos] = max(st1[pos], x)
  i += n_;
  st1[i] = max(st1[i], x);
  while (i > 1)
    st1_pul(i >>= 1);
}
int st1_query(int l, int r) {
  // Range max query on st1 in interval [l,r]
  int x = -1;
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
    if ((l & 1) == 1)
      x = max(x, st1[l++]);
    if ((r & 1) == 0)
      x = max(x, st1[r--]);
  }
  return x;
}
void st2_update(int l, int r, int x) {
  // Range assign-max on st2 for interval [l,r]
  // This is implemented as storing max values on covering segment tree nodes
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
    if ((l & 1) == 1) {
      st2[l] = max(st2[l], x);
      l++;
    }
    if ((r & 1) == 0) {
      st2[r] = max(st2[r], x);
      r--;
    }
  }
}
int st2_query(int i) {
  // Query maximum assigned value affecting position i
  int x = -1;
  for (i += n_; i > 0; i >>= 1)
    x = max(x, st2[i]);
  return x;
}
int main() {
  static int *eh[N], eo[N], ii[Q], ans[Q];
  int q, h, i, i_, j, j_, k, o, u, v, w, d, x;
  scanf("%d%d%s", &n, &q, cc);
  for (j = 0; j < n; j++)
    eh[j] = (int *)malloc(2 * sizeof *eh[j]);
  for (h = 0; h < q; h++) {
    scanf("%d%d", &i, &j), i--, j--;
    ii[h] = i;
    append(eh, eo, j, h);
  }
  eertree();
  build();
  for (j = 0; j < n; j++) {
    u = uu[j + 1];
    if (u) {
      i = st1_query(ta[u], tb[u] - 1);
      if (i != -1)
        ft_update(n - 1 - (i - len[u] + 1), len[u]);
    }
    v = u;
    while (v) {
      ft_update(n - 1 - (j - len[v] + 1), len[ff[v]]);
      w = ff_[v], d = len[v] - len[ff[v]];
      if (w) {
        i = st1_query(ta[w], tb[w] - 1);
        if (i != -1)
          ft_update(n - 1 - (i - len[w] + 1), len[w]);
      }
      for (k = 1; k <= K && len[w] + d * k <= len[v]; k++) {
        i = j - len[w] - d * k + 1;
        ft_update(n - 1 - i, len[w] + d * (k - 1));
      }
      if (len[v] - len[w] >= d * K) {
        i = j - len[w] - d * K + 1;
        st2_update(j - len[v] + 2, i, j);
      }
      v = w;
    }
    // After processing contributions for position j, register it in st1
    u = uu[j + 1];
    st1_update(ta[u], j);

    // Answer all queries that end at position j (eh[j] contains query indices)
    for (o = eo[j]; o--;) {
      h = eh[j][o], i = ii[h];
      // current best from Fenwick (max palindrome length starting <= i)
      x = ft_query(n - 1 - i);
      // j_ is the latest position contributing via st2's range updates
      j_ = st2_query(i);
      if (j_ != -1 && j_ >= i) {
        // We found a heavy contribution; need to compute exact overlap
        u = uu[j_ + 1];
        // climb using ff_ so that palindrome at u covers position i
        while (j_ - len[ff_[u]] + 1 < i)
          u = ff_[u];
        d = len[u] - len[ff[u]];
        i_ = j_ - len[u] + 1;
        // align i_ to the arithmetic progression of centers
        i_ += (i - i_ + d - 1) / d * d;
        x = max(x, j_ - i_ + 1 - d);
        if (i_ > i)
          x = max(x, j_ - i_ - (d - i_ + i) * 2 + 1);
      }
      ans[h] = x; // store answer for query h
    }
  }
  for (h = 0; h < q; h++)
    printf("%d\n", ans[h]);
  return 0;
}

// https://github.com/VaHiX/CodeForces/