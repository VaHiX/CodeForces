// Problem: CF 786 A - Berzerk
// https://codeforces.com/contest/786/problem/A

/*
 * Problem: Berzerk Game
 * 
 * Purpose:
 *   This code solves a game theory problem where two players (Rick and Morty)
 *   play a turn-based game on a circular board of n objects. One of them is a black hole,
 *   and the rest are planets. A monster starts at a random planet. Players take turns moving
 *   the monster using their own set of predefined moves (clockwise), and if the monster
 *   reaches the black hole, the current player wins. The task is to determine for each
 *   initial position and who plays first whether the starter wins, loses, or the game
 *   enters an infinite loop.
 * 
 * Algorithm:
 *   - Use dynamic programming with memoization and a depth-first search (DFS).
 *   - For each player and each possible monster position, we compute:
 *     - Whether the current player can win ("Win")
 *     - Whether the current player will lose ("Lose")
 *     - Whether the game will loop ("Loop")
 *   - The state is tracked using a visited array and a win array to determine outcomes.
 *   - DFS recursively evaluates all possible moves and their consequences.
 *   - For each move, if the opponent is forced into a losing state, we mark it as a win.
 *   - If all moves lead to a loop, we note that the game will not terminate.
 * 
 * Time Complexity: O(n * k1 * k2), where n is the number of objects, k1 and k2 are the sizes of sets for Rick and Morty.
 * Space Complexity: O(n * k1 * k2) for the arrays to store the states.
 * 
 * Techniques:
 *   - Game Theory and Dynamic Programming
 *   - DFS with memoization
 *   - Turn-based game state evaluation
 */

#include <iostream>
#include <string>

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
const int N = 7010;
int n, k[2], a[2][N];
int win[2][N], vis[2][N], cnt[2][N];

// Performs DFS to evaluate game states from a given position and player
void dfs(int per, int xb) {
  if (vis[per][xb])
    return;  // If already visited, skip
  vis[per][xb] = 1;  // Mark as visited
  int u = per ^ 1;  // Switch player (0 <-> 1)
  rep(i, 1, k[u]) {  // Iterate over all moves of the opponent
    int pre = (xb - a[u][i]);  // Calculate new position after move
    if (pre < 1)
      pre += n;  // Handle circular board
    if (pre == 1)
      continue;  // Can't move to black hole
    if (win[per][xb] == 0) {  // If current player has no known win
      win[u][pre] = 1;  // Next player can win
      dfs(u, pre);  // Recursively check
    } else if (++cnt[u][pre] == k[u]) {  // If all moves exhausted
      win[u][pre] = 0;  // Next player loses
      dfs(u, pre);  // Recursively check
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n;
  cin >> k[0];
  rep(i, 1, k[0]) cin >> a[0][i];
  cin >> k[1];
  rep(i, 1, k[1]) cin >> a[1][i];
  dfs(0, 1);  // Start DFS for Rick (player 0)
  dfs(1, 1);  // Start DFS for Morty (player 1)
  string s[4];
  s[1] = "Win", s[2] = "Lose", s[3] = "Loop";  // Outcome strings
  rep(i, 0, 1) {  // For both players
    rep(j, 2, n) cout << (vis[i][j] ? win[i][j] ? s[1] : s[2] : s[3]) << " ";  // Output result
    cout << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/