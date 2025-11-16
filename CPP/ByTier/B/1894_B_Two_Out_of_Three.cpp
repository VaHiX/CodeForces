// Problem: CF 1894 B - Two Out of Three
// https://codeforces.com/contest/1894/problem/B

#include <cstdio>
#include <vector>
/*
 * Problem: B. Two Out of Three
 *
 * Purpose:
 *   Given an array of integers, assign each element a value from {1, 2, 3}
 *   such that exactly two of the three conditions are satisfied:
 *     1. There exist i,j such that a[i] == a[j], b[i] == 1, b[j] == 2
 *     2. There exist i,j such that a[i] == a[j], b[i] == 1, b[j] == 3
 *     3. There exist i,j such that a[i] == a[j], b[i] == 2, b[j] == 3
 *
 * Algorithm:
 *   1. Count how many distinct values appear at least twice in input array.
 *   2. For each such value, assign two indices with different values from {2,3} (in alternating fashion).
 *   3. For other elements, assign value 1.
 *   4. This guarantees that we have at least 2 pairs satisfying condition 1.
 *   5. We use a greedy approach to choose the combinations to enforce exactly 2 of 3 conditions.
 *
 * Time Complexity: O(n + B), where B is the maximum possible value in input (107).
 * Space Complexity: O(n + B), for storing input and auxiliary arrays.
 */
int main() {
  const int B = 107; // Maximum possible value in the input array
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::vector<int>> m(B, std::vector<int>()); // Group indices by value
    std::vector<long> a(n), b(n, 1); // Input array and output array (default 1)
    long dupes(0); // Count of distinct values appearing at least twice
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      m[a[p]].push_back(p);
      if (m[a[p]].size() == 2) {
        ++dupes; // Increment if this is the first time we find a duplicate value
      }
    }
    if (dupes < 2) {
      puts("-1"); // Not enough duplicate values to form two valid pairs
      continue;
    }
    int cur(0); // Alternate between 0 and 1 to assign 2 or 3
    for (long p = 0; p < B; p++) {
      if (m[p].size() < 2) {
        continue; // Skip values that don't appear at least twice
      }
      b[m[p][0]] = 2 + cur; // Assign first occurrence one of {2,3}
      cur = 1 - cur; // Toggle between 0 and 1
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", b[p]); // Output results
    }
    puts(""); // Newline after output
  }
}

// https://github.com/VaHiX/CodeForces/