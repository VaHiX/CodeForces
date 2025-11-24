// Problem: CF 765 C - Table Tennis Game 2
// https://codeforces.com/contest/765/problem/C

/*
 * Purpose: Determine the maximum number of complete table tennis sets played
 *          given the score of two players, k (points to win a set), a (Misha's score),
 *          and b (Vanya's score). Each set is won when a player reaches exactly k points.
 *          
 * Algorithm/Techniques: 
 *   - Calculate total complete sets from full k-points scored by each player
 *   - Check if the remaining points (a % k and b % k) allow for a valid final set
 *   - Handle impossible cases where leftover points exceed k or are inconsistent
 *   
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a few integer variables
 */

#include <cstdio>
int main() {
  long k, a, b;
  scanf("%ld %ld %ld\n", &k, &a, &b);
  long ans(a / k + b / k);  // Count complete sets from full k-point scores
  if ((a % k && b < k) || (b % k && a < k)) {  // Check if remaining points are valid for a final incomplete set
    ans = -1;  // Invalid case: leftover points from one player are not enough to start a new set
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/