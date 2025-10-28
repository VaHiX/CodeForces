// Problem: CF 2045 G - X Aura
// https://codeforces.com/contest/2045/problem/G

/*
G. X Aura
Purpose:
  This program solves a grid-based path finding problem with a penalty calculation that depends on the difference in heights and a fixed odd exponent X.
  It uses prefix sums for efficient querying of penalties and detects cycles (invalid scenarios) by checking consistency across the grid.
Algorithms/Techniques:
  - Prefix Sum technique to preprocess costs for efficient range queries
  - Cycle detection using row/column consistency checks
Time Complexity:
  - Preprocessing: O(R * C)
  - Each query: O(1)
  - Total for Q queries: O(Q)
Space Complexity:
  - O(R * C) for storing the prefix sum matrix
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Computes a^X using iterative multiplication
int ipow(int a, int X) {
  int b = 1;
  while (X--)
    b *= a;
  return b;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int R, C, X;
  cin >> R >> C >> X;
  vector<string> S(R);
  for (int i = 0; i < R; i++) {
    cin >> S[i];
  }
  using ll = int64_t;
  
  // p[i][j] stores prefix sum of penalties for row i and column j
  vector<vector<ll>> p(R, vector<ll>(C));
  
  // Build prefix sums
  for (int i = 0; i < R; i++) {
    if (i + 1 < R) {
      // Compute cumulative penalty from top to bottom in first column
      p[i + 1][0] = p[i][0] + ipow(int(S[i + 1][0]) - int(S[i][0]), X);
    }
    for (int j = 0; j + 1 < C; j++) {
      // Compute cumulative penalty from left to right in each row
      p[i][j + 1] = p[i][j] + ipow(int(S[i][j + 1]) - int(S[i][j]), X);
    }
  }

  // Check for inconsistencies that indicate a possible cycle
  int bad = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (i + 1 < R) {
        // If the computed value doesn't match manually computed value, there's inconsistency
        if (p[i + 1][j] != p[i][j] + ipow(int(S[i + 1][j]) - int(S[i][j]), X)) {
          bad = 1;
        }
      }
    }
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--;
    c1--;
    r2--;
    c2--;
    
    // If inconsistencies are present, the scenario is invalid
    if (bad) {
      cout << "INVALID" << '\n';
    } else {
      // Query result: difference between prefix sums at destination and start point
      cout << (-p[r2][c2] + p[r1][c1]) << '\n';
    }
  }
}


// https://github.com/VaHiX/codeForces/