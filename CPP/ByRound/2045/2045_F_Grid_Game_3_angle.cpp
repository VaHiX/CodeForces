// Problem: CF 2045 F - Grid Game 3-angle
// https://codeforces.com/contest/2045/problem/F

/*
F. Grid Game 3-angle

This problem is about a combinatorial game played on a triangular grid where players take turns making moves according to specific rules. The game ends when no more moves can be made, and the last player to make a move wins.

The key insight is to use the Sprague-Grundy theorem (Gale-Shapley), applying XOR operations modulo K+1 to analyze the state of the game.

Algorithms/Techniques:
- Sprague-Grundy theorem for impartial games
- XOR operation and modular arithmetic
- Game theory on triangular grids with specific move constraints

Time Complexity: O(M + K) per test case, where M is the number of initial stones and K is the parameter from input.
Space Complexity: O(K) for storing the array 'a' which tracks XOR values.

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(k + 1); // Array to store XOR values of each modulo class
    for (int i = 0; i < m; i++) {
      int r, c, x;
      cin >> r >> c >> x;
      x %= (k + 1); // Reduce x modulo K+1 to fit in the range [0, K]
      a[r % (k + 1)] ^= x; // XOR operation on the value at index r % (K+1)
    }
    int f = 0;
    for (int i = 0; i < k + 1; i++) {
      if (a[i] != 0) { // If any element in a is non-zero, there's a winning strategy
        f = 1;
      }
    }
    if (!f) { // If all elements are zero, the position is losing for the current player
      cout << "Kamu\n";
    } else {
      cout << "Anda\n"; // Otherwise, current player has winning strategy
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/