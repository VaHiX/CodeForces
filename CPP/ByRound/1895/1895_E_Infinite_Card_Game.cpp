// Problem: CF 1895 E - Infinite Card Game
// https://codeforces.com/contest/1895/problem/E

/*
Purpose: Solve the Infinite Card Game problem where two players (Monocarp and Bicarp) play optimally,
         and we need to determine for each of Monocarp's starting moves:
         - How many lead to a win for Monocarp
         - How many lead to a draw
         - How many lead to a win for Bicarp

Algorithms/Techniques:
- Graph-based approach with DFS to determine winning/losing states
- Preprocessing attack and defense values for efficient comparison
- Sorting + reverse to process cards in descending order of attack
- Binary search-like logic using two pointers to find valid card matchups

Time Complexity: O(n log n + m log m + n + m)
Space Complexity: O(n + m)

The game is modeled as a directed graph where each node represents a state:
- Nodes 1 to n: Monocarp's cards (0-indexed in the original input)
- Nodes n+1 to n+m: Bicarp's cards (0-indexed in the original input)
- Special nodes: 
  - Node n+m+1: Start state for Monocarp
  - Node n+m+2: Start state for Bicarp

The DFS traversal from these special nodes determines if Monocarp or Bicarp can guarantee a win from that starting position.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
const int sz = 7e5 + 5;
int n, m, ca[sz], cb[sz];
pair<int, int> a[sz], b[sz];
vector<int> g[sz];
bool done[sz];
int dfs(int u) {
  done[u] = 1;
  int res = u <= n; // If u <= n, then it's a Monocarp card, mark as win for Monocarp
  for (int v : g[u])
    if (!done[v]) {
      res += dfs(v); // Recursively traverse the graph, accumulating wins
    }
  return res;
}
void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i].second); // Read attack values
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i].first);  // Read defense values
  scanf("%d", &m);
  for (int i = 0; i < m; i++)
    scanf("%d", &b[i].second); // Read attack values
  for (int i = 0; i < m; i++)
    scanf("%d", &b[i].first);  // Read defense values
  sort(a, a + n);           // Sort Monocarp's cards in ascending order
  sort(b, b + m);           // Sort Bicarp's cards in ascending order
  reverse(a, a + n);        // Reverse to get descending order of attack
  reverse(b, b + m);        // Reverse to get descending order of attack
  ca[0] = a[0].second;
  for (int i = 1; i < n; i++)
    ca[i] = max(ca[i - 1], a[i].second); // Precomputed max defense in prefix for Monocarp's cards
  cb[0] = b[0].second;
  for (int i = 1; i < m; i++)
    cb[i] = max(cb[i - 1], b[i].second); // Precomputed max defense in prefix for Bicarp's cards
  for (int i = 0; i <= n + m + 5; i++)
    done[i] = 0, g[i].clear(); // Reset the graph and visited flags
  for (int i = n - 1, j = 0; i >= 0; i--) {
    int def = a[i].first; // Current Monocarp card's defense
    while (j < m and cb[j] <= def) // Find the first Bicarp card with higher defense
      j++;
    int u = i + 1, v = j + 1; // Convert to 1-based indexing
    g[n + 1 + v].push_back(u); // Add edge from Bicarp's card to Monocarp's card
  }
  for (int i = m - 1, j = 0; i >= 0; i--) {
    int def = b[i].first; // Current Bicarp card's defense
    while (j < n and ca[j] <= def) // Find the first Monocarp card with higher defense
      j++;
    int u = i + 1, v = j + 1; // Convert to 1-based indexing
    g[v].push_back(n + 1 + u); // Add edge from Monocarp's card to Bicarp's card
  }
  int win = dfs(n + m + 2);    // Traverse from node n+m+2 (Bicarp's start state)
  int lose = dfs(n + 1);      // Traverse from node n+1 (Monocarp's start state)
  int draw = n - win - lose;  // Remaining cards go to draw
  printf("%d %d %d\n", win, draw, lose);
}
int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/