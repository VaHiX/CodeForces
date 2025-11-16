// Problem: CF 2048 E - Kevin and Bipartite Graph
// https://codeforces.com/contest/2048/problem/E

// ### Complexity Analysis

// - **Time Complexity**: O(n * m) per test case, where n is the number of vertices in the left part and m is the number of vertices in the right part. This is because we iterate through all 2n rows and m columns to assign colors.

// - **Space Complexity**: O(1) in terms of extra space, excluding the input and output storage. The algorithm uses only a constant amount of additional space for variables and does not rely on any data structures that scale with input size.

// ### Algorithm/Techniques Used
// The solution uses a combinatorial approach to color edges in a bipartite graph such that no monochromatic cycle exists. It leverages a cyclic shifting pattern based on the sum of indices modulo 2n, then maps the result to a color in the range [1, n]. The key insight is derived from the fact that in any complete bipartite graph with more than 2n - 1 edges on the right side, it's unavoidable to form monochromatic cycles under the given constraints.

#include <iostream>

using namespace std;
void radi() {
  int n, m, i, j;
  cin >> n >> m;
  if (m > 2 * n - 1) {
    // If the number of vertices on the right side exceeds 2*n - 1,
    // it's impossible to avoid monochromatic cycles due to the pigeonhole principle
    cout << "NO" << endl;
  } else {
    // Otherwise, a valid coloring exists
    cout << "YES" << endl;
    for (i = 0; i < 2 * n; i++) {
      for (j = 0; j < m; j++) {
        // This formula ensures that no monochromatic cycle is formed
        // by distributing colors in a way that avoids creating cycles of same color
        cout << (((i + j) % (2 * n)) / 2 + 1) << " ";
      }
      cout << endl;
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    radi();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/