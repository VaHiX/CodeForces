// Problem: CF 1009 A - Game Shopping
// https://codeforces.com/contest/1009/problem/A

/*
 * Problem: A. Game Shopping
 * Purpose: Maxim buys games in order, using bills from his wallet. 
 *          Each bill can only be used once and is discarded if it's sufficient to buy a game.
 *          The goal is to count how many games he successfully buys.
 *
 * Algorithms/Techniques:
 * - Greedy approach with two pointers: one for games (c), one for bills (a).
 * - Iterate through the games and try to use the cheapest available bill that can cover the cost.
 *
 * Time Complexity: O(n + m), where n is number of games, m is number of bills.
 * Space Complexity: O(n + m), for storing the arrays c and a.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> c(n);  // Vector to store costs of games
  for (long p = 0; p < n; p++) {
    scanf("%ld", &c[p]);   // Read each game cost
  }
  std::vector<long> a(m);  // Vector to store values of bills
  for (long p = 0; p < m; p++) {
    scanf("%ld", &a[p]);   // Read each bill value
  }
  long ind(0);             // Index to track current bill in wallet
  for (long p = 0; p < n && ind < m; p++) {  // Loop through games and bills
    if (c[p] <= a[ind]) {    // If current bill can buy the game
      ++ind;                 // Move to next bill
    }
  }
  printf("%ld\n", ind);    // Output number of games bought
  return 0;
}


// https://github.com/VaHiX/codeForces/