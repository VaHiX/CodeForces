// Problem: CF 2171 C1 - Renako Amaori and XOR Game (easy version)
// https://codeforces.com/contest/2171/problem/C1

/*
 * Purpose: Determine the winner of a XOR game played between Ajisai and Mai.
 *          Each player can swap elements at their turn index (odd for Ajisai, even for Mai).
 *          The score is the XOR of all elements in their respective arrays.
 *          Game outcome depends on optimal play.
 *
 * Algorithm:
 *   - For each index i, check if a[i] != b[i]. If so, increment counter 'cnt' and store last such index.
 *   - If 'cnt' is even, then the game ends in a tie because both players can mirror each other's moves.
 *   - If 'cnt' is odd, the player who makes the last move wins.
 *   - The last move is made by the player whose turn corresponds to the index 'last':
 *     - If last index is odd, Mai makes the last move → Mai wins
 *     - If last index is even, Ajisai makes the last move → Ajisai wins
 *
 * Time Complexity: O(n) per test case, where n is the length of arrays.
 * Space Complexity: O(n) for storing the input arrays.
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
using namespace std;

signed main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    int cnt = 0, last = 0;
    for (int i = 0; i < n; i++) {
      // If a[i] and b[i] differ, it's a meaningful position that can affect XOR outcome
      if (a[i] ^ b[i]) {  // XOR returns 1 if bits differ
        cnt++;            // Count such positions
        last = i;         // Remember the last differing index
      }
    }
    // If even number of differing positions, result is tie (both players can mirror)
    if (cnt % 2 == 0)
      cout << "Tie\n";
    else
      // If odd, the last differing index determines winner:
      // last % 2 gives 1 for odd index (Mai's turn) or 0 for even index (Ajisai's turn)
      cout << (last % 2 ? "Mai\n" : "Ajisai\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/