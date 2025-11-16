// Problem: CF 1919 G - Tree LGM
// https://codeforces.com/contest/1919/problem/G

/*
 * Code Purpose: This solution determines whether a given n×n matrix of game states 
 * (representing winning and losing positions for each root and initial coin position)
 * can be represented by a valid tree structure in a two-player game played on a tree.
 * It employs a hashing-based approach to efficiently validate and construct such a tree.
 *
 * Algorithms/Techniques:
 * 1. Hashing with bitsets for efficient comparison of game state vectors.
 * 2. Graph construction using node degree matching and binary search logic.
 * 3. Validation of tree structure based on adjacency and game state properties.
 * 4. Sorting and greedy edge addition logic for final tree formation.
 *
 * Time Complexity: O(n^3 + n^2 * log(n)) due to:
 *   - Hashing and comparison of vectors: O(n^2)
 *   - Sorting nodes by degree: O(n * log(n))
 *   - Edge construction and validation: O(n^3) in worst case
 *   - Overall is bounded by constraints (n ≤ 5000)
 *
 * Space Complexity: O(n^2) due to:
 *   - Storage of bitset vectors (n vectors of size n)
 *   - Hash table for storing indices of bitset vectors
 *   - Output storage of edges
*/

#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <random>
#include <vector>

using namespace std;
#define ll long long
#define pb push_back
#define mid ((l + r) / 2)
const int N = 5e3 + 5, MOD = 9999991;
int n, tp, tp1, b[N], w[N], o[N], f[N], nw[N];
char a1[N];
mt19937 rand1;
bitset<N> all, a[N];
vector<int> z0, z1, z2;
int cntH, hd[MOD];
struct Hash {
  int x, nxt;
} hs[N];
struct Node {
  int u, v;
} z[N], ans[N];

// Add value to x with modulo
void W(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}

// Get hash value of bitset
int getH(const bitset<N> &x) {
  int res = 0;
  for (int i = 1; i <= n; ++i)
    if (x[i])
      W(res, w[i]);
  return res;
}

// Insert index into hash table
void ins(int x) {
  int t = getH(a[x]);
  hs[++cntH] = (Hash){x, hd[t]};
  hd[t] = cntH;
}

// Find index of matching bitset
int find(const bitset<N> &x) {
  int t = 0;
  for (int i = hd[getH(x)]; i; i = hs[i].nxt)
    if (x == a[hs[i].x]) {
      ;
      if (t)
        return 0;
      t = i;
    }
  return t;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    all[i] = 1, w[i] = rand1() % MOD;
  for (int i = 1; i <= n; ++i) {
    scanf("%s", a1 + 1);
    for (int j = 1; j <= n; ++j)
      if (a1[j] == '1')
        a[j][i] = 1, o[j] = i;
  }
  for (int i = 1; i <= n; ++i) {
    b[i] = a[i].count();
    ins(i);
    if (b[i] && b[i] < n) {
      if (!a[i][i]) {
        printf("NO\n");
        return 0;
      }
    }
  }
  for (int i = 1, t; i <= n; ++i)
    if (b[i] && b[i] < n) {
      t = find(a[i] ^ all);
      if (!t) {
        printf("NO\n");
        return 0;
      }
      if (b[i] < b[t] || (b[i] == b[t] && a[i][1]))
        z[++tp] = (Node){i, t};
    }
  sort(z + 1, z + tp + 1, [](Node x, Node y) { return b[x.u] > b[y.u]; });
  a[0] = all;
  for (int i = 1, u; i <= tp; ++i) {
    u = z[i].u;
    f[u] = nw[o[u]];
    ans[++tp1] = z[i];
    if ((a[u] & (a[f[u]] ^ all)).any()) {
      printf("NO\n");
      return 0;
    }
    a[f[u]] ^= a[u];
    for (int j = 1; j <= n; ++j)
      if (a[u][j])
        nw[j] = u;
  }
  for (int i = 1, u; i <= tp; ++i) {
    u = z[i].u;
    if (!a[u][u] || !a[f[u]][z[i].v]) {
      printf("NO\n");
      return 0;
    }
  }
  for (int i = 0, u; i <= tp; ++i) {
    u = z[i].u;
    z0.clear();
    z1.clear();
    z2.clear();
    for (int j = 1; j <= n; ++j)
      if (a[u][j]) {
        if (!b[j])
          z0.pb(j);
        else if (b[j] == n)
          z1.pb(j);
        else
          z2.pb(j);
      }
    if (!z1.empty()) {
      if (z0.size() < z1.size() + 1) {
        printf("NO\n");
        return 0;
      }
      for (int j = 0; j < z1.size(); ++j)
        ans[++tp1] = (Node){z0[0], z1[j]},
        ans[++tp1] = (Node){z0[j + 1], z1[j]};
      for (int j = z1.size() + 1; j < z0.size(); ++j)
        ans[++tp1] = (Node){z0[j], z1[0]};
      for (auto j : z2)
        ans[++tp1] = (Node){j, z1[0]};
    } else {
      if (z0.size() == 1 && z2.empty())
        continue;
      if (!z0.empty()) {
        printf("NO\n");
        return 0;
      }
      for (auto j : z2)
        if (j != z2[0])
          ans[++tp1] = (Node){j, z2[0]};
    }
  }
  printf("YES\n");
  for (int i = 1; i <= tp1; ++i)
    printf("%d %d\n", ans[i].u, ans[i].v);
  return 0;
}


// https://github.com/VaHiX/CodeForces/