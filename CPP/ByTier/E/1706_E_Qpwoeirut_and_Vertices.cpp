// Problem: CF 1706 E - Qpwoeirut and Vertices
// https://codeforces.com/contest/1706/problem/E

/*
Algorithm:
- This code uses a Union-Find (Disjoint Set Union) data structure with path
compression to manage connected components.
- It also uses a sparse table (ST) to quickly answer range maximum queries for
the minimum number of edges required to connect vertices in a range.
- The solution preprocesses edge additions and calculates for each vertex pair
in a range the minimum number of edges needed to connect them.

Time Complexity: O(n * log n + m * alpha(n) + q * log n)
Space Complexity: O(n * log n)

Where:
- n is the number of vertices
- m is the number of edges
- q is the number of queries
- alpha(n) is the inverse Ackermann function (nearly constant)
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>

using namespace std;

long long t, n, m, q, f[100005], st[100005][17], g[100005];
set<long long> s[100005];

// Find function with path compression for Union-Find
long long find(long long x) {
  if (f[x] == x)
    return x;
  return f[x] = find(f[x]);
}

int main() {
  // Precompute log values for sparse table
  for (int b = 1; b <= 100000; b++) {
    g[b] = g[b - 1];
    if (b == (1 << g[b] + 1))
      g[b]++;
  }

  cin >> t;

  while (t--) {
    cin >> n >> m >> q;

    // Initialize Union-Find and sets for each vertex
    for (int b = 1; b <= n; b++) {
      s[b].clear();
      f[b] = b;
      s[b].insert(b);
    }

    // Process edges and build component information
    for (int b = 1; b <= m; b++) {
      long long x, y;
      cin >> x >> y;
      long long f1 = find(x), f2 = find(y);
      if (f1 != f2) {
        // If f1 has more elements than f2, swap them to keep smaller set
        if (s[f1].size() > s[f2].size())
          swap(f1, f2);

        // For each element in the smaller set, update edge thresholds
        for (auto it = s[f1].begin(); it != s[f1].end(); it++) {
          auto x = s[f2].lower_bound(*it);
          // Check previous element in f2
          if (x != s[f2].begin() && *prev(x) == *it - 1)
            st[*it - 1][0] = b;
          // Check next element in f2
          if (x != s[f2].end() && *x == *it + 1)
            st[*it][0] = b;
        }

        // Merge smaller set into larger set
        for (auto it = s[f1].begin(); it != s[f1].end(); it++)
          s[f2].insert(*it);
        f[f1] = f2;
      }
    }

    // Build sparse table for range maximum queries
    for (int b = n - 1; b >= 1; b--)
      for (int c = 1; b + (1 << c) <= n; c++)
        st[b][c] = max(st[b][c - 1], st[b + (1 << c - 1)][c - 1]);

    // Process queries
    for (int b = 1; b <= q; b++) {
      long long l, r;
      cin >> l >> r;
      if (l == r)
        cout << "0 ";
      else
        // Use sparse table to find max edge required for the range [l, r]
        cout << max(st[l][g[r - l]], st[r - (1 << g[r - l])][g[r - l]]) << " ";
    }
    cout << "\n";
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/