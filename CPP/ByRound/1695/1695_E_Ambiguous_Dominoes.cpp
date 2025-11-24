// Problem: CF 1695 E - Ambiguous Dominoes
// https://codeforces.com/contest/1695/problem/E

/*
Code Purpose:
This solution reconstructs a grid and two distinct domino placements for a puzzle,
where two players (Polycarp and Monocarp) have different valid solutions using the same set of dominoes.
The approach uses graph traversal (DFS) to identify cycles in the domino connection graph,
and then constructs a valid 2xN grid with distinct placements for each player.

Algorithms/Techniques:
- Graph representation using adjacency lists
- Depth-First Search (DFS) for cycle detection and traversal
- Construction of alternating domino placements based on cycle lengths
- Pattern construction for grid positions using direction strings

Time Complexity: O(n)
Space Complexity: O(n)

The main idea is to model dominoes as a graph where connected components represent valid placements,
and cycles imply constraints on how dominoes can be arranged.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
constexpr int N = 600600;
int n, vis[N], vvs[N];
vector<int> s, ans[2], v[N];
string pos[4];
void dfs(int x, int f) {
  s.push_back(x);
  if (vis[x])
    return;
  vis[x] = 1;
  for (auto i : v[x])
    if (i != f && ((!vis[i]) || vvs[i] || i == x))
      dfs(i, x), s.push_back(x);
  vvs[x] = 1;
}
signed main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d%d", &x, &y);
    v[x].push_back(y);
    if (x != y)
      v[y].push_back(x);
  }
  for (int i = 1; i <= n * 2; i++) {
    if (vis[i])
      continue;
    s.clear();
    dfs(i, 0);
    s.pop_back();
    if (s.size() == 2)
      printf("-1\n"), exit(0);
    if (s.size() == 0)
      continue;
    int sum = s.size(), res = sum / 2;
    while (res--)
      ans[1].push_back(s.back()), s.pop_back();
    for (auto x : s)
      ans[0].push_back(x);
    sum /= 2;
    if (sum & 1) { // If sum is odd
      pos[0] += 'U';
      pos[1] += 'D';
      for (int x = 1; x <= (sum - 1) / 2; x++)
        for (int k = 0; k < 4; k++)
          pos[k] += "LR";
      pos[2] += 'U';
      pos[3] += 'D';
    } else { // If sum is even
      pos[0] += 'U';
      pos[1] += 'D';
      for (int x = 1; x <= (sum - 2) / 2; x++)
        for (int k = 0; k < 4; k++)
          pos[k] += "LR";
      pos[2] += "LR";
      pos[3] += "LR";
      pos[0] += 'U';
      pos[1] += 'D';
    }
  }
  printf("2 %d\n\n", n);
  for (auto i : ans[0])
    printf("%d ", i);
  printf("\n");
  for (auto i : ans[1])
    printf("%d ", i);
  printf("\n\n");
  cout << pos[0] << endl << pos[1] << endl << endl;
  cout << pos[2] << endl << pos[3] << endl;
}


// https://github.com/VaHiX/CodeForces/