// Problem: CF 731 F - Video Cards
// https://codeforces.com/contest/731/problem/F

/*
Code Purpose:
This program solves the problem of finding the maximum total power of video cards 
that can be used together by selecting a leading card and possibly reducing the 
power of other cards such that all secondary card powers are divisible by the 
leading card's power.

Algorithm:
1. Count the frequency of each power value using a vector v.
2. Precompute prefix sums in f where f[p] represents the count of cards with 
   power >= p.
3. For each possible leading card power p (from 1 to N/2):
   - If no cards of that power exist, skip.
   - For each multiple q of p, accumulate the total power (f[q] - f[q + p]) * q
   - Keep track of the maximum total power found.

Time Complexity: O(N log N)
Space Complexity: O(N)

*/
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {
  const long N = 400005;  // Maximum possible power value + 1
  long n;
  scanf("%ld", &n);
  std::vector<long> v(N + 1, 0);  // Frequency count of each power
  while (n--) {
    long x;
    scanf("%ld", &x);
    ++v[x];  // Increment frequency of power x
  }
  std::vector<int64_t> f(N + 1, 0);  // Prefix sum array
  // Build prefix sum from right to left
  for (long p = N - 1; p >= 0; p--) {
    f[p] = f[p + 1] + v[p];
  }
  int64_t max(0);  // Initialize maximum total power
  // Iterate through possible leading card powers
  for (long p = 1; p < N / 2; p++) {
    if (!v[p]) {
      continue;  // Skip if no cards of this power exist
    }
    int64_t total(0);  // Total power for current leading card p
    // For each multiple of p, compute contribution to total
    for (long q = p; q <= N / 2; q += p) {
      total += (f[q] - f[q + p]) * q;  // Add contribution of cards with power q
    }
    max = (total > max) ? total : max;  // Update maximum
  }
  std::cout << max << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/