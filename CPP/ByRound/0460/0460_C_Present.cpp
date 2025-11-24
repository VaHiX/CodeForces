// Problem: CF 460 C - Present
// https://codeforces.com/contest/460/problem/C

#include <cstdio>
#include <vector>
// Flowerbox: 
// Purpose: This program determines the maximum possible height of the smallest flower 
//          after m days of watering, where each day we can water w contiguous flowers.
//          It uses binary search on the answer combined with a greedy approach to 
//          determine if a certain height is achievable.
//
// Algorithms/Techniques: Binary Search + Difference Array (Greedy Watering)
// Time Complexity: O(n * log(max_height)) where max_height ~ 1e9
// Space Complexity: O(n) for the difference array and input vector
bool check(long h, const std::vector<long> &a, long m, long w) {
  const long n = a.size();
  std::vector<long> v(n + w + 1, 0); // Difference array to track watering operations
  long cnt(0), total(0);
  for (long p = 0; p < n; p++) {
    cnt += v[p]; // Current cumulative watering effect
    long diff = h - (a[p] + cnt); // How much more we need to water this flower
    if (diff < 0) {
      continue; // Already sufficient height
    }
    cnt += diff; // Apply watering
    total += diff; // Total watering units used
    if (total > m) {
      return false; // Exceeded allowed watering days
    }
    v[p + w] = -diff; // Mark end of watering effect (difference array technique)
  }
  return true;
}
int main() {
  long n, m, w;
  scanf("%ld %ld %ld", &n, &m, &w);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long left(0), right(1e9 + 1e7), height(0);
  while (left <= right) {
    long mid = (left + right) / 2;
    if (check(mid, a, m, w)) {
      height = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  printf("%ld\n", height);
  return 0;
}


// https://github.com/VaHiX/CodeForces/