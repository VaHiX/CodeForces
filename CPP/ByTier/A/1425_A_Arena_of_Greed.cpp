// Problem: CF 1425 A - Arena of Greed
// https://codeforces.com/contest/1425/problem/A

/*
 * Problem: Arena of Greed
 * Algorithms/Techniques: Greedy approach with optimal strategy simulation
 *
 * Time Complexity: O(log N) per test case, since we halve the number of coins approximately in each step
 * Space Complexity: O(1), only using a few variables for computation
 *
 * Description:
 * Two players (Mr. Chanek and his opponent) play optimally to maximize their own coin count.
 * Each turn, a player can either take 1 coin or half the coins (if even).
 * Mr. Chanek moves first.
 * This solution simulates the optimal play using greedy logic.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(0);  // Result: number of coins Mr. Chanek collects
    
    while (n > 0) {
      // If n is even and not 2, or if n equals 4, prefer taking half
      if (n % 4 == 2 || n == 4) {
        res += n / 2;
        n /= 2;
      } else {
        // Otherwise take one coin
        ++res;
        --n;
      }
      
      // Check again after the move to determine next player's turn
      if (n <= 0) {
        break;
      }
      
      // Opponent's move: try taking half if possible, otherwise take one
      if (n % 4 == 2 || n == 4) {
        n /= 2;
      } else {
        --n;
      }
    }
    
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/