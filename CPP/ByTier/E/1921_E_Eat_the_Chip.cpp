// Problem: CF 1921 E - Eat the Chip
// https://codeforces.com/contest/1921/problem/E

/*
Algorithm/Technique: Game Theory, Mathematical Analysis, Range Intersection
Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem involves a game between Alice and Bob on a grid where they move chips towards each other.
Alice moves down, Bob moves up. The key insight is to analyze the possible positions each player can reach
at each turn and determine if one can catch the other.

The solution works by:
1. Calculating the relative vertical distance (t = x2 - x1) between the players.
2. For each player, computing the range of columns they can possibly reach after 't' moves.
3. Based on the parity of 't', checking if Alice or Bob can position themselves to catch the opponent.
4. If Alice can reach a column range that completely encompasses Bob's possible range (for odd t) or vice versa (for even t), she wins.
5. Otherwise, if the ranges don't allow a win, the game is a draw.

Key idea:
- Alice moves down, Bob up: their relative movement is towards each other.
- The number of turns is determined by vertical distance.
- At each turn, the number of columns a player can cover increases.
- The outcome depends on whether one player's reach is sufficient to overlap with the opponent's.
*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

void solve() {
  int h, w, x1, y1, x2, y2;
  cin >> h >> w >> x1 >> y1 >> x2 >> y2;
  int t = x2 - x1; // number of turns needed for Alice to catch up to Bob
  if (t < 0)
    cout << "Draw" << '\n'; // if Alice is already below Bob, impossible to catch
  else {
    // Alice's possible column range after 't' moves
    int l1 = max(1, y1 - (t + 1) / 2), r1 = min(w, y1 + (t + 1) / 2);
    // Bob's possible column range after 't' moves  
    int l2 = max(1, y2 - t / 2), r2 = min(w, y2 + t / 2);
    // For odd t, Alice has advantage, so check if her range can contain Bob's
    if (t % 2 == 1)
      cout << (l1 <= l2 && r1 >= r2 ? "Alice" : "Draw") << '\n';
    else {
      // For even t, Bob has advantage, so check if his range can contain Alice's
      cout << (l2 <= l1 && r2 >= r1 ? "Bob" : "Draw") << '\n';
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/