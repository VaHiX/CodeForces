// Problem: CF 1746 D - Paths on the Tree
// https://codeforces.com/contest/1746/problem/D

/*
 * Problem: D. Paths on the Tree
 * 
 * Algorithm/Technique: 
 * - Tree DFS with greedy assignment of paths to maximize score.
 * - For each node in the tree, we compute how many paths go through it.
 * - At each node, we process all children, recursively computing their contribution.
 * - We balance path counts among siblings to satisfy the constraint |c_u - c_v| <= 1.
 * 
 * Time Complexity: O(n log n) per test case due to sorting of child contributions.
 * Space Complexity: O(n) for storing the tree and recursion stack.
 * 
 * The solution uses a depth-first search (DFS) traversal of the tree starting from the root.
 * At every node, we calculate the optimal distribution of paths among its children such that
 * the constraint on adjacent vertices' path counts is satisfied, and the total score is maximized.
 */

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
enum { N = 200009 };
basic_string<int> e[N];
int s[N], o;
long long ans;
int dfs(int x, int y) {
  // Add the contribution of the current node to the answer.
  ans += s[x] * 1ll * y;
  // If node is a leaf, no more paths can go through it further.
  if (e[x].empty())
    return s[x];
  // Collect contributions from all children.
  basic_string<int> w;
  for (int o : e[x]) {
    w += dfs(o, y / e[x].size());
  }
  // Sort child contributions in descending order to prioritize higher values.
  sort(begin(w), end(w), greater<int>());
  // Determine how many children will get one extra path.
  int p = y % e[x].size();
  // Add the extra path values to the result.
  for (int i = 0; i < p; ++i)
    ans += w[i];
  // Return the total contribution of this node considering paths going through it.
  return s[x] + w[p];
}
int main() {
  int T, n, i, j, k;
  for (cin >> T; T--;) {
    cin >> n >> o;
    ans = 0;
    // Initialize the adjacency list.
    for (i = 1; i <= n; ++i)
      e[i] = {};
    // Build the tree from parent information.
    for (i = 2; i <= n; ++i)
      cin >> j, e[j] += i;
    // Read scores for each node.
    for (i = 1; i <= n; ++i)
      cin >> s[i];
    // Start DFS from the root node.
    dfs(1, o);
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/