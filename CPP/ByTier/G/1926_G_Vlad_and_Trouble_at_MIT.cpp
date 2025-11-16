// Problem: CF 1926 G - Vlad and Trouble at MIT
// https://codeforces.com/contest/1926/problem/G

/*
Purpose: This program solves the problem of placing the minimum number of thick walls in a tree-shaped dormitory
to ensure that party students (P) can play music without disturbing silent students (S). 
The solution uses dynamic programming on trees to compute the minimum number of edges to block.

Algorithms/Techniques:
- Tree dynamic programming (DP)
- DFS traversal of the tree
- State DP: For each node, track two values:
    dp1[v]: minimum thick walls needed if we don't block the edge from parent to v
    dp2[v]: minimum thick walls needed if we do block the edge from parent to v

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n) for storing the tree and DP arrays.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
#define int long long
#define ff first
#define ss second
#define pb push_back
const int mod = 998244353;
const int N = 1e5 + 10;
const int inf = 1e6;
vector<int> a[N]; // adjacency list for the tree
string s;
vector<int> dp1(N), dp2(N); // dp1: no block edge; dp2: block edge

// Function to calculate DP values for each node
void find(int x = 0) {
  dp1[x] = 0;  // Initially, we assume no thick wall is needed
  dp2[x] = 0;  // Initially, we assume we will place a thick wall

  // Traverse all children
  for (auto i : a[x]) {
    find(i);  // Recursively process child
    // Transition: if we don't block edge to child, we can choose best between blocking or not
    dp1[x] += min(dp2[i] + 1, dp1[i]); 
    // Transition: if we block edge to child, child's state must be consistent with having a wall
    dp2[x] += min(dp2[i], dp1[i] + 1);  
  }

  // If node is a sleep student (S), it's impossible to allow sound through it
  if (s[x] == 'S')
    dp1[x] = inf; // Mark that not allowing sound is invalid for S node
  else if (s[x] == 'P')
    dp2[x] = inf; // Mark that allowing sound through P node is invalid
}

// Main function to process a test case
void solve(unordered_map<int, int> &mp) {
  cin >> s;
  find(0);  // Start DP from root (node 0)
  int ans = min(dp2[0], dp1[0]);  // Answer is minimum of including or excluding the root edge
  cout << ans << "\n";
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    // Clear adjacency list for current test case
    for (int i = 0; i < n; i++) {
      a[i].clear();
      // Build tree from parent information
      if (i != 0) {
        int x;
        cin >> x;
        a[x - 1].pb(i);  // Connect x-1 to i (0-indexed)
      }
    }
    unordered_map<int, int> mp;
    solve(mp);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/