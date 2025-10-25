// Problem: CF 2041 D - Drunken Maze
// https://codeforces.com/contest/2041/problem/D

/*
D. Drunken Maze
Algorithms/Techniques: BFS with state tracking (x, y, last_direction, consecutive_count)
Time Complexity: O(n * m * 4 * 4) = O(n * m)
Space Complexity: O(n * m * 4 * 4) = O(n * m)

You are given a two-dimensional maze with a start and end position. Your task is to find the fastest way to get from the start to the end position.
The fastest way is to make the minimum number of steps where one step is going left, right, up, or down.
Of course, you cannot walk through walls.

There is, however, a catch: If you make more than three steps in the same direction,
you lose balance and fall down. Therefore, it is forbidden to make more than three
consecutive steps in the same direction. It is okay to walk three times to the right,
then one step to the left, and then again three steps to the right.
This has the same effect as taking five steps to the right, but is slower.

Input
The first line contains two numbers n and m, which are the height and width of the maze.
This is followed by an ASCII-representation of the maze where # is a wall, . is an empty space,
and S and T are the start and end positions.

Output
The minimum number of steps to reach the end position from the start position or -1 if that is impossible.
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define ld long double
using VI = vector<int>;
using PI = pair<int, int>;

int n, m, fx[4] = {0, 0, 1, -1}, fy[4] = {1, -1, 0, 0};
int stx, sty, enx, eny;

struct node {
  int x, y, lst, dep, cnt; // x, y: current position; lst: last direction; dep: depth (steps); cnt: consecutive steps in last dir
};

queue<node> q;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  char c[n + 1][m + 1];
  bool vis[n + 1][m + 1][4][4]; // visited array to track (x, y, last_direction, consecutive_steps)
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= m; j++) {
      c[i][j] = s[j - 1];
      if (s[j - 1] == 'S') {
        q.push({i, j, 0, 0}); // Start BFS from S with no previous direction and 0 steps
        stx = i;
        sty = j;
        c[i][j] = '#'; // Mark start as wall to prevent revisiting
      }
      if (s[j - 1] == 'T') {
        enx = i;
        eny = j;
        c[i][j] = '.'; // Mark end as walkable
      }
    }
  }

  while (!q.empty()) {
    node u = q.front();
    q.pop();
    if (u.x == enx && u.y == eny) {
      cout << u.dep;
      return 0;
    }
    for (int i = 0; i < 4; i++) {
      int xx = u.x + fx[i], yy = u.y + fy[i];
      // Check bounds and wall
      if (xx < 1 || xx > n || yy < 1 || yy > m || c[xx][yy] != '.')
        continue;

      // If continuing in same direction
      if (u.lst == i) {
        // Allow up to 4 consecutive steps in the same direction
        if (u.cnt + 1 < 4 && !vis[xx][yy][i][u.cnt + 1]) {
          vis[xx][yy][i][u.cnt + 1] = 1;
          q.push({xx, yy, i, u.dep + 1, u.cnt + 1});
        }
      } else if (!vis[xx][yy][i][1]) { // If changing direction
        vis[xx][yy][i][1] = 1; // Mark new direction with count 1
        q.push({xx, yy, i, u.dep + 1, 1});
      }
    }
  }

  cout << -1;
  return 0;
}


// https://github.com/VaHiX/codeForces/