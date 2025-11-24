// Problem: CF 701 A - Cards
// https://codeforces.com/contest/701/problem/A

/*
Algorithm/Technique: Greedy approach with sorting
Approach:
1. Read all cards and store them as pairs of (value, index)
2. Sort the cards based on their values
3. Pair the smallest with the largest, second smallest with second largest, etc.
   This ensures that the sum of each pair is as balanced as possible

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the vector of pairs
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<std::pair<long, long>> v(n);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    v[p] = std::make_pair(x, p + 1); // Store value and 1-based index
  }
  sort(v.begin(), v.end()); // Sort by card values
  for (long p = 0; p < n / 2; p++) {
    printf("%ld %ld\n", v[p].second, v[n - 1 - p].second); // Pair smallest with largest
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/