// Problem: CF 1611 E2 - Escape The Maze (hard version)
// https://codeforces.com/contest/1611/problem/E2

/*
 * Problem: E2. Escape The Maze (hard version)
 * 
 * Algorithm: Tree Dynamic Programming with DFS
 * 
 * Time Complexity: O(n) for each test case, where n is the number of rooms
 * Space Complexity: O(n) for storing the tree and auxiliary arrays
 * 
 * Approach:
 * - Build a tree from the input corridors
 * - Mark positions of friends in the tree
 * - Perform DFS from root (room 1) to determine if Vlad can win or not
 * - Return the minimum number of friends needed to catch Vlad,
 *   or -1 if Vlad always wins
 * 
 * Key Idea:
 * - For each node, we calculate the minimum distance to a friend
 * - If Vlad can reach a leaf with only one corridor, he wins
 * - Friends at distance 0 from their positions are marked
 * - DFS computes whether Vlad can get to a leaf before any friend catches him
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
vector<int> arr[200005]; // Adjacency list for the tree
int flag[200005]; // Distance to nearest friend for each node
int f(int now, int dis, int par) {
  bool cek = true; // Flag indicating if current node can be caught
  int has = 0; // Number of friends in subtree
  for (auto &x : arr[now]) { // Iterate through neighbors
    if (x == par) // Skip parent to avoid going back
      continue;
    int tmp = f(x, dis + 1, now); // Recurse on child
    if (tmp < 0) // If child can't be caught
      cek = false;
    flag[now] = min(flag[now], flag[x] + 1); // Update distance to nearest friend
    has += tmp; // Add friends in subtree
  }
  if (flag[now] <= dis) // If we're at a friend's position or closer
    return 1;
  if (has == 0 || !cek) // If no friends in subtree or subtree can't be caught
    return -1;
  return has;
}
void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    flag[i] = n + 5, arr[i].clear(); // Initialize arrays
  for (int i = 1; i <= k; i++) {
    int x;
    cin >> x;
    flag[x] = 0; // Mark friend positions
  }
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    arr[a].push_back(b); // Build adjacency list
    arr[b].push_back(a);
  }
  cout << f(1, 0, -1) << endl; // Start DFS from root
}
int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/