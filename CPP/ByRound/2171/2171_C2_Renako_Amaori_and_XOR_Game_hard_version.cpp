// Problem: CF 2171 C2 - Renako Amaori and XOR Game (hard version)
// https://codeforces.com/contest/2171/problem/C2

/*
Purpose: Solve the XOR Game between Ajisai and Mai where players can swap elements at specific indices to maximize their own score.
          The game is played over n turns, with Ajisai swapping odd indices and Mai swapping even indices.
          Players aim to maximize their XOR score (a1^a2^...^an for Ajisai, b1^b2^...^bn for Mai).
          The result is determined based on which player has a higher score with optimal play.

Algorithm:
- For each test case, compute the initial XORs of arrays a and b.
- If both scores are equal, it's a tie.
- Otherwise, find the most significant bit (MSB) where the XOR of scores differs.
- Then, starting from the last index, check if there's a swap that could change the outcome.
- The first such swap determines the winner based on whose turn it is.

Time Complexity: O(n) per test case.
Space Complexity: O(n) due to input arrays.

*/
#include <iostream>

using namespace std;
const int mxn = 5e5 + 5;
int n, a[mxn], b[mxn];
void solve() {
  cin >> n;
  int ca = 0, cb = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], ca ^= a[i];  // Compute XOR of array a
  for (int i = 1; i <= n; i++)
    cin >> b[i], cb ^= b[i];  // Compute XOR of array b
  if (ca == cb)
    cout << "Tie\n";  // If XORs are equal, it's a tie
  else {
    int t = 31 - __builtin_clz(ca ^ cb);  // Find MSB where ca and cb differ
    for (int i = n; i; --i) {            // Iterate from last element
      if ((a[i] ^ b[i]) & (1 << t)) {    // If swapping at index i affects the MSB
        if (i % 2 == 1)                  // If index is odd (Ajisai's turn)
          cout << "Ajisai\n";
        else                             // If index is even (Mai's turn)
          cout << "Mai\n";
        return;  // Game ends here
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  for (; T--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/