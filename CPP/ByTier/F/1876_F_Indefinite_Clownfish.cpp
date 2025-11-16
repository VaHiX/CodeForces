// Problem: CF 1876 F - Indefinite Clownfish
// https://codeforces.com/contest/1876/problem/F

/*
 * Problem: F. Indefinite Clownfish
 * Algorithms/Techniques: Preprocessing, Binary Lifting, DFS on Tree, Two Pointers
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 * 
 * The solution uses preprocessing to find the previous and next occurrences of
 * sizes differing by 1 (which satisfy gender constraints). It then uses binary
 * lifting to efficiently traverse paths and find valid sequences of clownfish.
 * The approach considers all possible ways to select k clownfish such that
 * the mean size of females equals the mean size of males with at least one of
 * each gender.
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define For_down(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
constexpr int n_MAX = 200000 + 5, inf = (1 << 28);
int n, m, Final = (+inf);
int a[n_MAX], prec[n_MAX][3], succ[n_MAX][3], occ[n_MAX];

// Preprocessing step to find nearest occurrences of sizes differing by -1, 0, +1
void preprocess() {
  For(i, 1, n) {
    For(j, -1, 1) prec[i][j + 1] = occ[a[i] + j];
    occ[a[i]] = i;
  }
  memset(occ, 0, (n + 1) << 2);
  For_down(i, n, 1) {
    For(j, -1, 1) succ[i][j + 1] = occ[a[i] + j];
    occ[a[i]] = i;
  }
  memset(occ, 0, (n + 1) << 2);
}

// F[i][j] stores minimum length of sequence ending at i with gender j
pair<int, int> F[n_MAX][2], G[n_MAX][2];

namespace compute_F {
int jump[n_MAX][18];
int Fa[n_MAX];
vector<int> ch[n_MAX];
int anc[n_MAX], cur;
inline int ancestor(const int c) { return anc[max(0, cur - c)]; }

// DFS to compute F values using binary lifting
void DFS(const int i) {
  if (i >= (m + 1)) { // If we have enough clownfish for consideration
    int c = 0, p = i, q = ancestor(m); // c is count of selected fish, p&q are indices
    For_down(k, 17, 0) { // Binary lifting step
      if ((c | (1 << k)) >= (m + 1))
        continue;
      const int mem_p = p, mem_q = q;
      c |= (1 << k), p = jump[p][k], q = ancestor(m - c);
      if ((!q) || (p && (p >= q)))
        continue;
      c ^= (1 << k), p = mem_p, q = mem_q;
    }
    For(j, 0, 1) { // Check both genders for final result
      if (p && q)
        F[i][j] = {i - min(p, q), c};
      ++c, p = prec[p][0], q = ancestor(m - c);
    }
  }
  for (const int j : ch[i])
    anc[++cur] = j, DFS(j), --cur;
}

void main() {
  For(i, 1, n) For(j, 0, 1) F[i][j] = {-1, -1};
  For(i, 1, n) {
    jump[i][0] = prec[i][0];
    For(k, 1, 17) jump[i][k] = jump[jump[i][k - 1]][k - 1];
  }
  For(i, 1, n) {
    Fa[i] = prec[i][2]; // Father is previous occurrence with size difference of 2
    if (Fa[i])
      ch[Fa[i]].push_back(i); // Build adjacency list using parent relationship
  }
  For(i, 1, n) if (!Fa[i]) anc[cur = 1] = i, DFS(i), cur = 0;
}
}; // namespace compute_F

namespace compute_G {
int jump[n_MAX][18];
int Fa[n_MAX];
vector<int> ch[n_MAX];
int anc[n_MAX], cur;
inline int ancestor(const int c) { return anc[max(0, cur - c)]; }

// DFS to compute reverse G values using binary lifting
void DFS(const int i) {
  if (i <= (n - m)) {
    int c = 0, p = i, q = ancestor(m);
    For_down(k, 17, 0) {
      if ((c | (1 << k)) >= (m + 1))
        continue;
      const int mem_p = p, mem_q = q;
      c |= (1 << k), p = jump[p][k], q = ancestor(m - c);
      if ((!q) || (p && (p <= q)))
        continue;
      c ^= (1 << k), p = mem_p, q = mem_q;
    }
    For(j, 0, 1) {
      if (p && q)
        G[i][j] = {max(p, q) - i, c};
      ++c, p = succ[p][2], q = ancestor(m - c);
    }
  }
  for (const int j : ch[i])
    anc[++cur] = j, DFS(j), --cur;
}

void main() {
  For(i, 1, n) For(j, 0, 1) G[i][j] = {-1, -1};
  For_down(i, n, 1) {
    jump[i][0] = succ[i][2];
    For(k, 1, 17) jump[i][k] = jump[jump[i][k - 1]][k - 1];
  }
  For_down(i, n, 1) {
    Fa[i] = succ[i][0]; // Father is next occurrence with size difference of 0
    if (Fa[i])
      ch[Fa[i]].push_back(i);
  }
  For_down(i, n, 1) if (!Fa[i]) anc[cur = 1] = i, DFS(i), cur = 0;
}
}; // namespace compute_G

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  if (m & 1) { // If k is odd, impossible to split equally between genders
    cout << "-1\n";
    return 0;
  }
  m = ((m >> 1) - 1); // Convert to half size for equal gender counting

  For(i, 1, n) cin >> a[i]; // Read the size array
  preprocess(); // Preprocess for faster query answers

  if (!m) { // Special case when only one of each gender to be chosen
    For(i, 1, n) if (succ[i][1]) Final = min(Final, succ[i][1] - i);
    cout << ((Final == (+inf)) ? (-1) : Final) << '\n';
    return 0;
  }

  compute_F::main(); // Precompute F values for forward traversal
  compute_G::main(); // Precompute G values for backward traversal

  // Combine information from F and G to find minimum valid combination
  For(i, 1, n) For(u, 0, 1) For(v, 0, 1) {
    const int j = succ[i][2 - u - v]; // Determine index of compatible fish
    if (!j)
      continue;
    For(x, 0, 1) For(y, 0, 1) {
      if ((F[i][x].first == (-1)) || (G[j][y].first == (-1)))
        continue;
      if ((!u) && (!v) && (F[i][x].second == m) && (G[j][y].second == m))
        continue; // Both are of exact required length
      if (u && v && (!F[i][x].second) && (!G[j][y].second))
        continue; // Neither has more than required count
      Final = min(Final, (j - i) + F[i][x].first + G[j][y].first);
    }
  }
  cout << ((Final == (+inf)) ? (-1) : Final) << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/