// Problem: CF 1918 F - Caterpillar on a Tree
// https://codeforces.com/contest/1918/problem/F

/*
 * Problem: F. Caterpillar on a Tree
 * 
 * Algorithm/Technique:
 * - Tree DFS traversal to calculate the depth of each subtree
 * - Identify the longest path from root in each subtree
 * - Sort these longest paths in descending order
 * - Use at most k teleports to reduce the total time by removing the longest paths
 * 
 * Time Complexity: O(n log n) due to sorting the subtree depths
 * Space Complexity: O(n) for storing the tree and auxiliary arrays
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define all(v) begin(v), end(v)
#define ff first
#define ss second
const char nl = '\n';
const int inf = 1e9 + 9;
const long long INF = 1e18 + 18;
const int N = 200010;
vector<int> g[N]; // adjacency list for the tree
vector<int> a;    // stores the depths of subtrees
int dfs(int u, int d) {
  int h = 0; // h stores the maximum depth of subtree rooted at u
  for (int v : g[u]) {
    int h2 = dfs(v, d + 1) + 1; // recursively compute depth of child v
    if (h2 > h) {
      swap(h2, h); // keep h as the maximum, h2 as second max
    }
    if (h2 > d)
      a.push_back(h2 - d); // store the extra distance beyond current depth
  }
  return h;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt = 1;
  while (tt--) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
      int p;
      cin >> p;
      p--; // convert to 0-based indexing
      g[p].push_back(i); // build adjacency list
    }
    a.push_back(dfs(0, 0)); // start DFS from root (0)
    sort(a.rbegin(), a.rend()); // sort in descending order
    int ans = 2 * (n - 1); // initial time assuming no teleporting
    for (int i = 0; i < (int)a.size() && i < k + 1; i++) {
      ans -= a[i]; // subtract the longest paths we can save via teleporting
    }
    cout << ans;
  }
}


// https://github.com/VaHiX/CodeForces/