// Problem: CF 937 D - Sleepy Game
// https://codeforces.com/contest/937/problem/D

/*
 * Purpose: Determine the outcome of a game where two players (Petya and Vasya) 
 *          take turns moving a chip on a directed graph. Petya goes first and 
 *          can make both his and Vasya's moves. The game ends when a player can't move,
 *          or after 10^6 moves (draw). 
 *          
 * Algorithm:
 * - Build a directed graph from input.
 * - Use DFS to detect cycles starting from the initial vertex to determine if a draw is possible.
 * - Use recursive DFS with memoization to find a winning path for Petya.
 * - A winning path is a sequence where Petya's turn (odd number of moves) ends in a leaf node.
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 * 
 * Techniques:
 * - DFS for cycle detection and path finding.
 * - Memoization to avoid recomputation.
 * - Backtracking to construct the winning path.
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
bool win, draw;
#define pb push_back
vector<int> v[100005], ans;
int vis[100005];             // Visited array for cycle detection
int view[100005][2];         // Memoization for path search: [vertex][turn parity]

// Function to detect a cycle starting from vertex n
bool iscycle(int n) {
  vis[n] = 1;  // Mark node as being visited
  for (int i = 0; i < v[n].size(); i++) {
    if (vis[v[n][i]] == 1)
      return true;  // Found a cycle
    else if (!vis[v[n][i]] && iscycle(v[n][i]))
      return true;  // Recursively check if a cycle exists in subtree
  }
  vis[n] = 2;  // Mark node as completely processed (no cycle through this node)
  return false;
}

// Recursive function to find a winning path
// x: current vertex, odd: whether it's Petya's turn (odd number of moves)
bool run(int x, bool odd) {
  view[x][odd]++;  // Mark this state as visited to avoid recomputation
  bool ok = 1;
  // If it's Petya's turn and we are at a leaf node, then Petya has won
  if (v[x].size() == 0 && odd) {
    return 1;
  }
  // Try all moves from current vertex
  for (int i = 0; i < v[x].size(); i++) {
    // If opponent hasn't visited this vertex in their turn, try this move
    if (!view[v[x][i]][!odd] && run(v[x][i], !odd)) {
      ans.pb(v[x][i]);  // Add move to path
      return 1;
    }
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  win = draw = false;
  int x, n, m, y;
  cin >> n >> m;
  // Read the graph edges
  for (int i = 1; i <= n; i++) {
    cin >> x;
    while (x--) {
      cin >> y;
      v[i].pb(y);  // Add edge from i to y
    }
  }
  cin >> x;  // Read initial position
  // Try to find a winning path for Petya
  if (run(x, 0)) {
    cout << "Win\n";
    ans.pb(x);  // Add initial vertex to path
    reverse(ans.begin(), ans.end());  // Reverse to get path from start to end
    for (int i : ans)
      cout << i << " ";
  } else if (iscycle(x))  // If there's a cycle and no winning path, it's a draw
    cout << "Draw";
  else
    cout << "Lose";  // If no winning path and no cycle, Petya loses
}


// https://github.com/VaHiX/CodeForces/