// Problem: CF 1914 E2 - Game with Marbles (Hard Version)
// https://codeforces.com/contest/1914/problem/E2

/*
E2. Game with Marbles (Hard Version)
Algorithms/Techniques: Greedy algorithm, sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing vectors and pairs

The problem simulates a game where Alice and Bob take turns removing marbles of the same color.
Alice wants to maximize the score (difference between her remaining marbles and Bob's), 
while Bob wants to minimize it. Both players play optimally.

Key idea:
- For each color, compute the sum a[i] + b[i] to prioritize which colors are most valuable for the game.
- Sort colors in descending order of this sum.
- Alice plays on even turns (0, 2, 4, ...) and Bob plays on odd turns (1, 3, 5, ...).
- Each player removes one marble from a color they choose, then removes all marbles 
  of that color from their opponent.
- The score is calculated as the difference between Alice's and Bob's total remaining marbles.
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {         // Read Alice's marbles
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {         // Read Bob's marbles
      scanf("%lld", &b[p]);
    }
    std::vector<std::pair<ll, ll>> s(n); // Store sum of a[i] + b[i] and index
    for (long p = 0; p < n; p++) {
      s[p].first = a[p] + b[p];          // Sum of marbles of color i
      s[p].second = p;                   // Original index
    }
    sort(s.rbegin(), s.rend());          // Sort in descending order of sum
    
    ll res(0);
    for (long p = 0; p < n; p++) {
      long idx = s[p].second;            // Get original color index
      if (p % 2) {                       // Bob's turn (odd indices)
        res -= (b[idx] - 1);             // Bob removes his marble, and Alice loses all her marbles of this color
      } else {                           // Alice's turn (even indices)
        res += a[idx] - 1;               // Alice removes her marble, and Bob loses all his marbles of this color
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/