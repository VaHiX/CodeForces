// Problem: CF 1113 A - Sasha and His Trip
// https://codeforces.com/contest/1113/problem/A

/*
 * Problem: A. Sasha and His Trip
 * Purpose: Find the minimum cost to travel from city 1 to city n with a car of capacity v,
 *          where each city has a fuel price equal to the city number.
 * Algorithms/Techniques: Greedy approach with optimal refueling strategy.
 * Time Complexity: O(1) - constant time calculation.
 * Space Complexity: O(1) - only using a few variables.
 */

#include <cstdio>
int main() {
  long n, v;
  scanf("%ld %ld", &n, &v);
  long ans = (v - 1) + (n - v) * (n - v + 1) / 2;  // Calculate initial answer based on strategy
  if (v >= n) {  // If tank capacity is enough to reach destination in one go
    ans = n - 1;  // Then minimum cost is just the sum of all prices from city 1 to n-1
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/