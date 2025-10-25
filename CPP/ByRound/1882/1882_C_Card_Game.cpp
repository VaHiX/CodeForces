// Problem: CF 1882 C - Card Game
// https://codeforces.com/contest/1882/problem/C

/*
 * Problem: Card Game
 * 
 * Algorithm/Technique: Greedy
 * 
 * Time Complexity: O(n), where n is the number of cards
 * Space Complexity: O(1), only using a constant amount of extra space
 * 
 * Approach:
 * The key idea is to determine when to take cards (odd i) vs when to skip cards (even i).
 * We process cards from left to right:
 *   - For the first card, if it's positive, we take it.
 *   - For the second card, if it's positive, we consider taking it together with the first.
 *   - From then on, we take all positive cards we encounter.
 * 
 * The logic handles initial cases where we can potentially gain by combining first few cards
 * with even moves, then proceeds to collect positive values.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
int t, n;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    ll x;
    bool o = false;  // Flag to indicate if we have taken at least one card
    ll res = 0;      // Resulting score
    ll mx = -1000000001;  // Not actually used in current logic, likely a leftover
    ll y;            // Stores the value of the first card
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &x);
      if (o) {
        // If we have already taken some card(s), just add positive values
        if (x >= 0)
          res += x;
      } else {
        // First turn logic
        if (i == 1) {
          y = x;  // Store first card value
          if (x >= 0) {
            res += x;  // Take first card if positive
            o = true;  // Mark that we have taken a card
          }
        }
        if (i == 2) {
          // Second card: decide whether combining with first card is beneficial
          if (x >= 0) {
            if (x + y >= 0)
              res += x + y;  // Take both cards if total is non-negative
          }
          o = true;  // Mark that we have taken cards or decided not to
        }
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/