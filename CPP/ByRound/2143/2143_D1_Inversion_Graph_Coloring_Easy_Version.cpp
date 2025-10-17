// Problem: CF 2143 D1 - Inversion Graph Coloring (Easy Version)
// https://codeforces.com/contest/2143/problem/D1

/*
D1. Inversion Graph Coloring (Easy Version)
Algorithms/Techniques: Dynamic Programming, Inversion Graphs
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This problem asks for counting the number of "good" subsequences in a given array.
A subsequence is good if we can color its elements red or blue such that:
- For every pair of indices i < j with b_i > b_j, colors assigned to i and j are different.
This is equivalent to saying: there's no inversion (i,j) where i<j and b_i > b_j in the subsequence,
such that both elements have the same color — hence it's a valid 2-coloring of an inversion graph.

We use dynamic programming with state f[i][j] which represents the number of ways to assign colors
to the first i elements such that element at index j is colored red (or blue in a sense). But here, 
we're redefining to represent valid colorings by keeping track of how many good subsequences end
at a particular position and satisfy conditions based on previous choices.

The recurrence considers all pairs (j,k) for current element i:
- If a[i] >= a[j], we add contributions from f[j][k]
- Else if a[i] >= a[k], we update f[j][i]

Finally, the answer is the sum of all f[i][j].
*/ 

#include <iostream>

using namespace std;
const int N = 3e2 + 10, mod = 1e9 + 7;
typedef long long LL;
int n, T;
int a[N];
int f[N][N];
inline void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      f[i][j] = 0;
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < i; k++) {
        if (a[i] >= a[j])
          (f[i][k] += f[j][k]) %= mod;
        else if (a[i] >= a[k])
          (f[j][i] += f[j][k]) %= mod;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      (ans += f[i][j]) %= mod;
  cout << ans << '\n';
  return;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/