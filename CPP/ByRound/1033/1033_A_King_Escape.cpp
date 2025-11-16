// Problem: CF 1033 A - King Escape
// https://codeforces.com/contest/1033/problem/A

/*
Problem: King Escape
Algorithms/Techniques: DFS on a grid to find a path avoiding forbidden cells (squares under attack by queen)

Time Complexity: O(n^2) - in worst case, we might visit all cells of the board
Space Complexity: O(n^2) - for storing the board and recursion stack in DFS

This problem involves determining if a king can escape from a queen's attack.
The solution marks all squares under attack by the queen as blocked,
then uses DFS to check whether a path exists from king's start position to target position
while avoiding these blocked cells.
*/
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 1010
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, 1, -1, -1, 1};
int n;
int a[N][N];
void dfs(int r, int c) {
  a[r][c] = 2; // Mark as visited
  for (int i = 0; i < 8; i++) {
    int x = dx[i] + r;
    int y = dy[i] + c;
    if (x > 0 && y > 0 && x <= n && y <= n && !a[x][y]) // If within bounds and not blocked
      dfs(x, y);
  }
}
int main() {
  int i, j, k;
  int m;
  int ax, bx, cx; // Coordinates of queen (ax,ay), king (bx,by), target (cx,cy)
  int ay, by, cy;
  sf(n); // Read board size
  sff(ax, ay); // Read queen position
  sff(bx, by); // Read king position
  sff(cx, cy); // Read target position
  memset(a, 1, sizeof(0)); // Initialize board to all 1s (blocked)
  // Mark rows and columns of queen as blocked
  for (i = 1; i <= n; i++)
    a[i][ay] = 1, a[ax][i] = 1;
  // Mark diagonals of queen as blocked  
  i = ax, j = ay;
  while (i < n && j < n) {
    a[i][j] = 1;
    i++;
    j++;
  }
  i = ax, j = ay;
  while (i > 0 && j < n) {
    a[i][j] = 1;
    i--;
    j++;
  }
  i = ax, j = ay;
  while (i < n && j > 0) {
    a[i][j] = 1;
    i++;
    j--;
  }
  i = ax, j = ay;
  while (i > 0 && j > 0) {
    a[i][j] = 1;
    i--;
    j--;
  }
  dfs(bx, by); // Start DFS from king's position
  if (a[cx][cy] == 2) // If target reached
    pfs("YES\n");
  else
    pfs("NO\n");
  return 0;
}


// https://github.com/VaHiX/codeForces/