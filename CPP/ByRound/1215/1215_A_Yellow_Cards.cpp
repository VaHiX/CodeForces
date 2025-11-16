// Problem: CF 1215 A - Yellow Cards
// https://codeforces.com/contest/1215/problem/A

/*
 * Problem: Yellow Cards
 * Purpose: Determine the minimum and maximum number of players that could be sent off
 *          given the total number of yellow cards shown and the rules for each team.
 *
 * Algorithms:
 *   - Greedy approach to compute minimum and maximum players sent off.
 *   - For minimum: calculate the minimum number of players needed to use at least n cards.
 *   - For maximum: distribute cards greedily to maximize player dismissals.
 *
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only using a fixed number of variables.
 */

#include <cstdio>
int main() {
  long a1, a2, k1, k2, n;
  scanf("%ld %ld %ld %ld %ld", &a1, &a2, &k1, &k2, &n);
  
  // Calculate minimum number of players sent off
  // If total cards needed to keep everyone in match is more than n, then 0 players are sent off
  long mn = (n < ((k1 - 1) * a1 + (k2 - 1) * a2))
                ? 0
                : (n - (k1 - 1) * a1 - (k2 - 1) * a2);
  
  // Determine which team has smaller k value (higher penalty)
  long kx = (k1 < k2) ? k1 : k2;
  long ax = (k1 < k2) ? a1 : a2;
  long ky = (k1 > k2) ? k1 : k2;
  long ay = (k1 > k2) ? a1 : a2;
  
  // Calculate maximum number of players sent off
  long mx(0);
  if (n > ax * kx) {  // If we have more cards than what the team with smaller k can use
    mx += ax;         // Send off all players from the team with smaller k
    n -= ax * kx;     // Subtract the cards used
    mx += n / ky;     // Distribute remaining cards among the other team (maximum possible)
  } else {
    mx = n / kx;      // Otherwise, just distribute cards greedily among the first team
  }
  
  printf("%ld %ld\n", mn, mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/