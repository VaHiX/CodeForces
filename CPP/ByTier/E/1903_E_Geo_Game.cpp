// Problem: CF 1903 E - Geo Game
// https://codeforces.com/contest/1903/problem/E

/*
 * Problem: Geo Game
 * 
 * Algorithm: 
 * - The game is about choosing points such that the final sum of squared distances is even.
 * - Key insight: Parity of the sum depends on the parity of the number of odd-distance moves.
 * - Each point has a parity based on (x + y) % 2.
 * - We partition points into black (even parity) and white (odd parity) sets.
 * - The game is about controlling the number of moves that contribute to odd sums.
 * 
 * Time Complexity: O(n log n) - due to set operations (insert and erase)
 * Space Complexity: O(n) - to store points in sets
 */

#include <iostream>
#include <set>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
#define trav(a, x) for (auto &a : x)
#define FOR(i, a, b) for (int i = (a); i <= (signed)(b); i++)
#define ROF(i, a, b) for (int i = (a); i >= (signed)(b); i--)
#define F0R(i, a) for (int i = 0; i < (signed)(a); i++)
#define vi vector<int>
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;
const ll mod = 1e9 + 7, MOD = 998244353;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int sx, sy;
    cin >> sx >> sy;
    int s = (sx + sy) % 2; // parity of starting point
    set<int> black, white; // sets to store indices of black and white points
    F0R(i, n) {
      int u, v;
      cin >> u >> v;
      if ((u + v) % 2) {
        white.insert(i + 1); // insert point index (1-based) into white set
      } else {
        black.insert(i + 1); // insert point index (1-based) into black set
      }
    }
    // Compare sizes of white and black sets to determine optimal strategy
    if (white.size() == black.size()) {
      cout << "First" << endl;
      if (s == 0) {
        int ap = 0;
        while (ap < n) {
          if (ap % 2 == 0) {
            // Player's turn (First player)
            if (white.size() > 0) {
              cout << *white.begin() << endl; // choose smallest index from white
              white.erase(white.begin()); // remove that index
            } else {
              cout << *black.begin() << endl; // choose smallest index from black
              black.erase(black.begin()); // remove that index
            }
          } else {
            // Opponent's turn
            int u;
            cin >> u;
            if (black.count(u))
              black.erase(u); // remove from black if present
            if (white.count(u))
              white.erase(u); // remove from white if present
          }
          ap++;
        }
      } else {
        int ap = 0;
        while (ap < n) {
          if (ap % 2 == 0) {
            // Player's turn (First player)
            if (black.size() > 0) {
              cout << *black.begin() << endl; // choose smallest index from black
              black.erase(black.begin()); // remove that index
            } else {
              cout << *white.begin() << endl; // choose smallest index from white
              white.erase(white.begin()); // remove that index
            }
          } else {
            // Opponent's turn
            int u;
            cin >> u;
            if (black.count(u))
              black.erase(u); // remove from black if present
            if (white.count(u))
              white.erase(u); // remove from white if present
          }
          ap++;
        }
      }
    } else if (white.size() > black.size()) {
      if (s == 1) {
        // If starting point is odd parity and white is larger, play as First player
        cout << "First" << endl;
        int ap = 0;
        while (ap < n) {
          if (ap % 2 == 0) {
            // Player's turn (First player)
            if (black.size() > 0) {
              cout << *black.begin() << endl; // choose smallest index from black
              black.erase(black.begin()); // remove that index
            } else {
              cout << *white.begin() << endl; // choose smallest index from white
              white.erase(white.begin()); // remove that index
            }
          } else {
            // Opponent's turn
            int u;
            cin >> u;
            if (black.count(u))
              black.erase(u); // remove from black if present
            if (white.count(u))
              white.erase(u); // remove from white if present
          }
          ap++;
        }
      }
      if (s == 0) {
        // If starting point is even parity and white is larger, play as Second player
        cout << "Second" << endl;
        int ap = 0;
        while (ap < n) {
          if (ap % 2 == 1) {
            // Player's turn (Second player)
            if (black.size() > 0) {
              cout << *black.begin() << endl; // choose smallest index from black
              black.erase(black.begin()); // remove that index
            } else {
              cout << *white.begin() << endl; // choose smallest index from white
              white.erase(white.begin()); // remove that index
            }
          } else {
            // Opponent's turn
            int u;
            cin >> u;
            if (black.count(u))
              black.erase(u); // remove from black if present
            if (white.count(u))
              white.erase(u); // remove from white if present
          }
          ap++;
        }
      }
    } else if (black.size() > white.size()) {
      if (s == 0) {
        // If starting point is even parity and black is larger, play as First player
        cout << "First" << endl;
        int ap = 0;
        while (ap < n) {
          if (ap % 2 == 0) {
            // Player's turn (First player)
            if (white.size() > 0) {
              cout << *white.begin() << endl; // choose smallest index from white
              white.erase(white.begin()); // remove that index
            } else {
              cout << *black.begin() << endl; // choose smallest index from black
              black.erase(black.begin()); // remove that index
            }
          } else {
            // Opponent's turn
            int u;
            cin >> u;
            if (black.count(u))
              black.erase(u); // remove from black if present
            if (white.count(u))
              white.erase(u); // remove from white if present
          }
          ap++;
        }
      } else {
        // If starting point is odd parity and black is larger, play as Second player
        cout << "Second" << endl;
        int ap = 0;
        while (ap < n) {
          if (ap % 2 == 1) {
            // Player's turn (Second player)
            if (white.size() > 0) {
              cout << *white.begin() << endl; // choose smallest index from white
              white.erase(white.begin()); // remove that index
            } else {
              cout << *black.begin() << endl; // choose smallest index from black
              black.erase(black.begin()); // remove that index
            }
          } else {
            // Opponent's turn
            int u;
            cin >> u;
            if (black.count(u))
              black.erase(u); // remove from black if present
            if (white.count(u))
              white.erase(u); // remove from white if present
          }
          ap++;
        }
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/