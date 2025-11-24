// Problem: CF 2045 M - Mirror Maze
// https://codeforces.com/contest/2045/problem/M

/*
M. Mirror Maze
Algorithms/Techniques: Simulation with reflection handling, BFS-like traversal in a grid to simulate light path.

Time Complexity: O(R * C * (R + C)) - For each of 2*(R+C) possible starting positions, we simulate the light path 
which can take up to R*C steps in worst case.
Space Complexity: O(R * C) - For storing the maze and auxiliary arrays.

This code determines all valid laser starting positions such that a beam of light from that position hits every mirror
in the grid. It simulates light paths from all possible edges, handling reflections based on mirror types ('/' and '\').
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define FOR(i, l, r) for (int i = l; i <= r; ++i)
#define el '\n'
using namespace std;
vector<vector<char>> m;
int R, C, mir = 0, id = 0;
vector<string> v;
int kt[210][210];

// Function to simulate light beam starting from (x,y) with direction (u,v)
// Returns true if all mirrors are hit
bool sol(int u, int v, int x, int y) {
  int cnt = 0;
  while (true) {
    // If out of bounds, return false
    if (x < 1 || x > R || y < 1 || y > C)
      return false;
    
    // If current cell is a mirror
    if (m[x][y] != '.') {
      // Swap directions for reflection (as in the problem description) 
      swap(u, v);
      
      // Count mirror if not visited before
      if (kt[x][y] != id)
        ++cnt, kt[x][y] = id;
      
      // Apply reflection logic based on mirror type
      if (m[x][y] == '/')
        u = -u, v = -v; // Type 1 mirror reflection
    }
    
    // If we've hit all mirrors, return true
    if (cnt == mir)
      return true;
    
    // Move to next position
    x += u;
    y += v;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  cin >> R >> C;
  m.resize(R + 1, vector<char>(C + 1));
  memset(kt, 0, sizeof(kt));
  
  // Read input and count total mirrors
  FOR(i, 1, R)
    FOR(j, 1, C) {
      cin >> m[i][j];
      if (m[i][j] != '.')
        ++mir;
    }
  
  // Try starting from north edge
  FOR(j, 1, C) {
    id++;
    if (sol(1, 0, 1, j))
      v.push_back("N" + to_string(j));
    id++;
    if (sol(-1, 0, R, j))
      v.push_back("S" + to_string(j));
  }
  
  // Try starting from west edge
  FOR(i, 1, R) {
    id++;
    if (sol(0, 1, i, 1))
      v.push_back("W" + to_string(i));
    id++;
    if (sol(0, -1, i, C))
      v.push_back("E" + to_string(i));
  }
  
  cout << v.size() << el;
  for (auto &e : v)
    cout << e << ' ';
}


// https://github.com/VaHiX/codeForces/