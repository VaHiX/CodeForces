// Problem: CF 668 A - Little Artem and Matrix
// https://codeforces.com/contest/668/problem/A

/*
 * Problem: Little Artem and Matrix
 * 
 * Purpose: Given a sequence of operations on a matrix (row/column shifts and queries),
 * determine an initial matrix that would produce the observed results.
 * 
 * Approach:
 * - Track the positions of the matrix elements through all shifts using a coordinate mapping.
 * - For each query operation, update the answer matrix at the mapped position.
 * 
 * Time Complexity: O(q * (n + m)) where q is the number of operations, n and m are dimensions.
 * Space Complexity: O(n * m) for storing the mapping and answer matrix.
 * 
 * Algorithms/Techniques: Coordinate transformation, simulation of shifts
 */

#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
const int N = 1e2 + 4;
const int inf = 1e9;
const int mod = 1e9 + 7;
int n, m, q;
pair<int, int> lab[N][N]; // tracking positions of elements
int ans[N][N]; // final answer matrix

void go() {
  cin >> n >> m >> q;
  // Initialize coordinate mapping to identity
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      lab[i][j] = {i, j};
  
  while (q--) {
    int t, a, b, c;
    cin >> t >> a;
    if (t == 1) {
      // Shift row a to the left (cyclically)
      for (int j = 1; j < m; j++)
        swap(lab[a][j], lab[a][j + 1]);
    }
    if (t == 2) {
      // Shift column a up (cyclically)
      for (int i = 1; i < n; i++)
        swap(lab[i][a], lab[i + 1][a]);
    }
    if (t == 3) {
      // Query operation: record value at mapped position
      cin >> b >> c;
      ans[lab[a][b].first][lab[a][b].second] = c;
    }
  }
  
  // Output the resulting matrix
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      cout << ans[i][j] << " ";
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  for (int i = 1; i <= T; i++)
    go();
  return 0;
}


// https://github.com/VaHiX/CodeForces/