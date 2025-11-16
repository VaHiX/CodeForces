// Problem: CF 1759 E - The Humanoid
// https://codeforces.com/contest/1759/problem/E

/*
Algorithm: DFS with memoization to explore all valid actions (absorb, use green, use blue)
Time Complexity: O(n * 2^n) in worst case due to recursive exploration, but optimized by sorting and early pruning
Space Complexity: O(n) for recursion stack and array storage

Approach:
- Sort astronauts by power in ascending order to process them strategically
- Use DFS to try all valid sequences of actions:
  1. Absorb an astronaut if his power is less than humanoid's power
  2. Use green serum (doubles power) if available
  3. Use blue serum (triples power) if available
- Memoization ensures we don't recompute same states
- At each step, we try absorbing and also trying both serums if available
*/

#include <algorithm>
#include <iostream>

using namespace std;
int n, a[200001];
int dfs(long long h, int c, int x, int y) {
  // Base case: all astronauts processed
  if (c == n + 1)
    return 0;
  // If current astronaut can be absorbed
  if (a[c] < h)
    return dfs(h + (a[c] >> 1), c + 1, x, y) + 1;
  // Otherwise try using serums if available
  return max(x ? dfs(h << 1, c, x - 1, y) : 0, y ? dfs(h * 3, c, x, y - 1) : 0);
};
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    long long h;
    cin >> n >> h;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1); // Sort astronauts by power
    cout << dfs(h, 1, 2, 1) << endl; // Start DFS with 2 green and 1 blue serum
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/