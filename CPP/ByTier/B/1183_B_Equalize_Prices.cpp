// Problem: CF 1183 B - Equalize Prices
// https://codeforces.com/contest/1183/problem/B

/*
B. Equalize Prices
Algorithm: Find maximum possible equal price B such that |a_i - B| <= k for all products.
Approach:
- For each product, determine the valid range of prices [a_i - k, a_i + k]
- Find intersection of all these ranges
- If intersection exists, maximum B is the upper bound of intersection
- If no intersection exists, return -1

Time Complexity: O(n) per query
Space Complexity: O(1)
*/

#include <stdio.h>
#include <iostream>

int t, n, k, M, m, e;
int main() {
  for (std::cin >> t; t--; printf("%d\n", m + k >= M - k ? m + k : -1))
    for (M = 0, m = 1e9, std::cin >> n >> k; n--;
         e > m ?: m = e, e < M ?: M = e)
      std::cin >> e;
}


// https://github.com/VaHiX/codeForces/