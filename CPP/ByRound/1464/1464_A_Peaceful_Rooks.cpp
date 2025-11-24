// Problem: CF 1464 A - Peaceful Rooks
// https://codeforces.com/contest/1464/problem/A

/*
Algorithm: Union-Find (Disjoint Set Union)
Technique: Connected components to track which rooks are in the same row/column.

Time Complexity: O(m * α(n)) where α is the inverse Ackermann function, nearly constant.
Space Complexity: O(n)

Problem: Peaceful Rooks
Given an n×n chessboard with m rooks placed such that none attack each other,
find the minimum number of moves to place all rooks on the main diagonal (i,i).
Each move allows a rook to move any number of cells horizontally or vertically,
as long as it doesn't attack any other rook after moving.
*/

#include <cstdio>
#include <iosfwd>

#define maxn 100005
using namespace std;
int T, n, m, i, j, k, fa[maxn], a[maxn][2];
int find(int x) { return (fa[x] == x) ? x : fa[x] = find(fa[x]); } // Find with path compression
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
      fa[i] = i;
    int ans = m;
    for (i = 1; i <= m; i++) {
      scanf("%d%d", &j, &k);
      if (j == k)
        ans--; // Rook already on diagonal, no move needed
      else if (find(j) == find(k))
        ans++; // Rooks in same row/column, adding a move to separate them
      else
        fa[find(j)] = find(k); // Union rows and columns of rooks
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/