// Problem: CF 1749 A - Cowardly Rooks
// https://codeforces.com/contest/1749/problem/A

/*
Problem: Cowardly Rooks
Algorithm/Techniques: Simulation with constraint checking
Time Complexity: O(t * m * n) where t is number of test cases, m is number of rooks, and n is the board size
Space Complexity: O(1) - only using a constant amount of extra space

The problem asks whether we can move exactly one rook to a different cell such that 
no two rooks attack each other after the move. Since rooks attack in rows and columns,
we need to check if any rook has at least one valid move (a cell in its row or column 
that is not occupied by another rook).
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int t, n, m, tt;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
      cin >> tt >> tt; // Read rook positions but ignore them since we don't need to store them
    if (n > m) // If board size is greater than number of rooks, at least one row/column is empty
      puts("YES");
    else
      puts("NO");
  }
}


// https://github.com/VaHiX/codeForces/