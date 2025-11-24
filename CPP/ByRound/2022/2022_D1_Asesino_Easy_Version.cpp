// Problem: CF 2022 D1 - Asesino (Easy Version)
// https://codeforces.com/contest/2022/problem/D1

/*
Algorithm: 
The solution uses a pairing strategy to identify the impostor among n players.
It pairs consecutive players (1,2), (3,4), ..., and queries each pair to see if they think each other is a knight.
If the responses differ (x1 != x2), then one of the two players must be the impostor.
In that case, it queries one more player to determine who the impostor is.
The algorithm ensures that it never exceeds n+69 queries.

Time Complexity: O(n) - We process each pair of players once and perform a constant number of queries per pair.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/
#include <iostream>

using namespace std;
#define int long long
void solve() {
  int n;
  cin >> n;
  // Iterate through pairs of players
  for (int i = 1; i < n; i += 2) {
    // Ask player i if player i+1 is a knight
    cout << "? " << i << " " << i + 1 << endl;
    int x1;
    cin >> x1;
    // Ask player i+1 if player i is a knight
    cout << "? " << i + 1 << " " << i << endl;
    int x2;
    cin >> x2;
    // If the responses are different, one of them is the impostor
    if (x1 != x2) {
      int u;
      // Select a reference player (either n or 1) to test against the current pair
      if (i == 1)
        u = n;
      else
        u = 1;
      // Ask player i if player u is a knight  
      cout << "? " << i << " " << u << endl;
      int y1;
      cin >> y1;
      // Ask player u if player i is a knight
      cout << "? " << u << " " << i << endl;
      int y2;
      cin >> y2;
      // Determine the impostor based on consistent responses
      if (y1 == y2)
        cout << "! " << i + 1 << endl;
      else
        cout << "! " << i << endl;
      return;
    }
  }
  // If all pairs responded consistently, the impostor must be the last player
  cout << "! " << n << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/