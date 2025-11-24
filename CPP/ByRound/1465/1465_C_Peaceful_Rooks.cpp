// Problem: CF 1465 C - Peaceful Rooks
// https://codeforces.com/contest/1465/problem/C

/*
C. Peaceful Rooks
Algorithm: Union Find (Disjoint Set Union)
Time Complexity: O(m * α(n)) where α is the inverse Ackermann function, nearly constant
Space Complexity: O(n)

The problem asks to place m rooks on the main diagonal with minimum moves.
Each rook can only move horizontally or vertically and cannot conflict with other rooks.
We use a union-find data structure to group rows and columns of rooks that are already aligned to the same diagonal row/column.
*/
#include <iosfwd>
#include <stdio.h>
#define LL long long
#define N 100005
using namespace std;
int fa[N]; // Union-Find parent array

// Find root with path compression
int gf(int k) {
  if (fa[k] == k)
    return k;
  fa[k] = gf(fa[k]); // Path compression
  return fa[k];
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
      fa[i] = i; // Initialize each node to be its own parent
    int ans = 0;
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      if (x != y) { // If rook is not already on the diagonal
        ans++; // One move to place it on the diagonal
        if (fa[x] == gf(y)) // If x and y are in same group
          ans++; // Another move for conflict resolution
        fa[x] = fa[y]; // Merge groups of x and y
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/