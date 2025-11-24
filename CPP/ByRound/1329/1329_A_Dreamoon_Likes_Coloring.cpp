// Problem: CF 1329 A - Dreamoon Likes Coloring
// https://codeforces.com/contest/1329/problem/A

/*
Code Purpose:
This code solves the "Dreamoon Likes Coloring" problem, where we must assign starting positions for coloring operations 
such that all cells are colored and all colors are used at least once. The key idea is to ensure that each operation's range 
fits within the available space and that the total coverage fills the entire row.

Algorithms/Techniques:
- Greedy approach with backward calculation to determine valid starting points.
- Preprocessing to check whether the total length of operations can cover all cells.
- Backward traversal for coloring assignment.

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> v(m);
  for (ll p = 0; p < m; p++) {
    scanf("%lld", &v[p]);
  }
  bool possible(true);
  // Check if any operation's length exceeds the available space
  for (ll p = 0; possible && p < m; p++) {
    if (v[p] + p > n) {
      possible = false;
    }
  }
  std::vector<ll> cs(m);
  // Calculate cumulative sum from right to left (from last operation to first)
  for (ll p = m - 1; possible && p >= 0; p--) {
    cs[p] = (p + 1 < m ? cs[p + 1] : 0) + v[p];
  }
  // Check if total coverage is sufficient to color all cells
  if (cs[0] < n) {
    possible = false;
  }
  if (possible) {
    // Assign start positions greedily from left to right
    for (ll p = 0; p < m; p++) {
      ll tmp = n - cs[p];
      printf("%lld ", 1 + (p > tmp ? p : tmp));
    }
    puts("");
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/