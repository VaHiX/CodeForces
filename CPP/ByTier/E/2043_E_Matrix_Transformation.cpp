// Problem: CF 2043 E - Matrix Transformation
// https://codeforces.com/contest/2043/problem/E

/*
E. Matrix Transformation

Purpose:
This code determines whether it is possible to transform matrix A into matrix B using two types of operations:
- Bitwise AND operation on a row (A[i][j] &= x)
- Bitwise OR operation on a column (A[i][j] |= x)

The approach processes the matrices bit by bit, checking for each bit position whether it's possible to achieve the target values in B from A using these operations.
It uses a reduction to a graph problem where each row/column is treated as a node and constraints between them define edges. Using a topological sort approach with DFS to detect cycles, we verify consistency across bit positions.

Algorithms/Techniques:
- Bit manipulation
- Graph theory (topological ordering using DFS)
- Binary search on bits (process one bit at a time)

Time Complexity: O(30 * n * m), where 30 is the number of bits for integers.
Space Complexity: O(n + m), due to graph representation and auxiliary vectors.

*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define lc f << 1
#define rc f << 1 | 1
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define lowbit(x) x & -x
#define gcd(x, y) __gcd(abs(x), abs(y))
const ll inf = LONG_LONG_MAX, mod = 998244353;
const int N = 1e7 + 10, inff = INT_MAX;
const double eps = 1e-9;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> x(n + 1, vector<int>(m + 1, 0)), // matrix A
      y(n + 1, vector<int>(m + 1, 0)); // matrix B
  vector<vector<int>> a(n + 1, vector<int>(m + 1, 0)),
      b(n + 1, vector<int>(m + 1, 0)); // bit representations of A and B
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> x[i][j]; // input matrix A
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> y[i][j]; // input matrix B
  bool f = 1; // flag to continue processing bits

  auto check = [&]() -> bool {
    vector<vector<int>> e(n + m + 1); // graph edges (n rows + m columns)
    vector<bool> v(n + m + 1, 0), in(n + m + 1, 0), vis(n + m + 1, 0); // v: marks if node is a constraint node; in: dfs recursion stack; vis: visited flag
    auto dfs = [&](int s, auto &dfs) -> bool {
      if (in[s]) // cycle detected
        return 0;
      in[s] = 1; // mark as being in DFS traversal
      for (auto it : e[s])
        if (!vis[it] && !dfs(it, dfs)) 
          return 0;
      in[s] = 0; // remove from recursion stack
      vis[s] = 1; // mark visited
      return 1;
    };
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (b[i][j]) // if b[i][j] is 1, then it requires that a[i][j] must be at least 1 after some operation
          e[i].push_back(j + n); // add constraint from row node i to column node j+n
        else
          e[j + n].push_back(i); // add reverse constraint if b[i][j] is 0, then a[i][j] should be 0 or less
        if (a[i][j] && !b[i][j]) // if bit in A is 1 but B has 0, this means we must prevent that
          v[i] = 1; // mark row as constrained
        if (!a[i][j] && b[i][j]) // if A is 0 but B has 1, column constraint needed
          v[j + n] = 1; // mark column as constrained
      }
    for (int i = 1; i <= n + m; i++) // check constraints
      if (v[i] && !dfs(i, dfs)) // if a node is marked as violated and not acyclic
        return 0;
    return 1;
  };

  while (f) {
    f = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        a[i][j] = x[i][j] % 2; // extract bit from A
        x[i][j] /= 2; // shift right to process next bit
        if (x[i][j])
          f = 1;
      }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        b[i][j] = y[i][j] % 2; // extract bit from B
        y[i][j] /= 2; // shift right to process next bit
        if (y[i][j])
          f = 1;
      }
    if (!check()) { // check consistency of current bit level
      cout << "No\n";
      return;
    }
  }
  cout << "Yes\n"; // all bits are consistent, transformation possible
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/