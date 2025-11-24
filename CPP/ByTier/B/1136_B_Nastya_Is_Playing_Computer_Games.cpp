// Problem: CF 1136 B - Nastya Is Playing Computer Games
// https://codeforces.com/contest/1136/problem/B

/*
B. Nastya Is Playing Computer Games
Algorithms/Techniques: Greedy approach, mathematical optimization

Time Complexity: O(1)
Space Complexity: O(1)

Problem Description:
Nastya needs to collect coins from n manholes arranged in a line. Initially,
she stands at position k and there is one stone on each manhole. She can:
1. Throw a stone from her current position to any other manhole (if there's a stone)
2. Move to an adjacent manhole
3. Open a manhole (only if no stones are present) to collect the coin

The goal is to find the minimum number of moves to collect all coins.
*/

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  // Calculate the maximum number of stones that can be thrown
  // to minimize the total number of moves needed
  long x = (2 * k <= n + 1) ? (k - 1) : (n - k);
  // Compute the minimum moves using derived formula based on optimal strategy
  long ans = 3 * n + x;
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/