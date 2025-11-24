// Problem: CF 1798 C - Candy Store
// https://codeforces.com/contest/1798/problem/C

/*
Purpose: This code solves the problem of minimizing the number of price tags needed to describe the costs of candy packs,
where each pack must contain a specific number of candies of one type, and the cost of a pack is determined by the number
of candies in it multiplied by the cost per candy.

Approach:
- For each candy type, we choose a pack size d_i such that a_i is divisible by d_i.
- The cost of a pack is c_i = b_i * d_i.
- We then need to minimize the number of price tags, where a price tag can cover a continuous segment of packs with the same cost.
- To achieve this optimally, the algorithm uses a greedy approach: 
  for each new segment starting from index i, it tries to extend as far as possible while maintaining consistent divisibility
  conditions and matching cost ratios.
- The key idea involves using GCD to manage how pack sizes change and maintain divisibility constraints efficiently.

Time Complexity: O(n * sqrt(A)) where A is the maximum value of a[i]. Each element may be processed multiple times, but GCD operations and divisions are efficient.
Space Complexity: O(n) for storing arrays a and b.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
using ll = long long;
int a[200009];  // Array to store number of candies for each type
int b[200009];  // Array to store cost per candy for each type
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &a[i], &b[i]);
    }
    int ans = 0;  // Result counter for number of price tags
    for (int i = 0; i < n;) {
      int j = i + 1;
      ll cur_a = a[i];  // Current total candies for segment start
      ll cur_b = b[i];  // Current cost per candy for segment start
      while (j < n) {
        ll g = __gcd(cur_b, (ll)b[j]);  // Calculate GCD of current and next cost
        ll cur_d = b[j] / g;            // Compute candidate d for next pack size
        ll dj = cur_b / g;              // Compute candidate d for current pack size
        // Check if the chosen d values maintain integer divisibility
        if (cur_a % cur_d != 0 || a[j] % dj)
          break;
        // Update the segment's combined candy count and cost
        cur_a = __gcd(cur_a / cur_d, a[j] / dj);
        cur_b = cur_d * dj * g;
        ++j;
      }
      i = j;  // Move to next segment
      ++ans;  // Increment price tag count
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/