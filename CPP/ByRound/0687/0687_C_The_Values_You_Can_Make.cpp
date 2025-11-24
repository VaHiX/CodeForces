// Problem: CF 687 C - The Values You Can Make
// https://codeforces.com/contest/687/problem/C

/*
Algorithm: Dynamic Programming with Bitset Optimization
Purpose: Given n coins and a target sum k, find all possible sums x that can be made using a subset of coins that sum to exactly k.

Time Complexity: O(n * k^2)
Space Complexity: O(k^2)

This solution uses a 2D bitset `f[v]` where each bit represents whether a certain sum is achievable.
For each coin, we update the bitsets from high to low to avoid using updated values in the same iteration.
The final result for all sums x that can be made using a subset that sums to k is determined by the bits in f[k].
*/

#include <bitset>
#include <cstdio>
int main() {
  const int N = 501;
  const int K = 501;
  int n, k;
  scanf("%d %d", &n, &k);
  std::bitset<N> f[K];  // f[v] stores all possible sums that can be made with coins summing to v
  f[0][0] = 1;  // Base case: sum 0 can be made with empty set
  for (int p = 0; p < n; p++) {
    int a;
    scanf("%d", &a);
    for (int v = k; v >= a; v--) {
      // Update f[v] with all sums achievable by adding coin 'a' to previous sums
      f[v] |= (f[v - a] | (f[v - a] << a));
    }
  }
  printf("%zu\n", f[k].count());  // Count how many values x can be made using coins that sum to k
  for (int p = 0; p <= k; p++) {
    if (f[k][p]) {  // If value p can be made using a subset of coins summing to k
      printf("%d ", p);
    }
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/