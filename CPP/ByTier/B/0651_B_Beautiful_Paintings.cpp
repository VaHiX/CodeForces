// Problem: CF 651 B - Beautiful Paintings
// https://codeforces.com/contest/651/problem/B

/*
 * Problem: Beautiful Paintings
 * Algorithm: Greedy + Sorting
 * 
 * Approach:
 * To maximize the number of times a visitor becomes happy (i.e., the number of 
 * increasing adjacent pairs), we should arrange the paintings such that the 
 * largest possible number of elements form an increasing sequence.
 * 
 * Key insight:
 * If we sort the array, the best arrangement is to group equal elements together
 * and interleave them, which maximizes the number of increasing transitions.
 * The number of transitions is reduced only by the largest group of equal elements.
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(1) if we ignore the space used by the input vector
 */

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
  int n;
  std::cin >> n;
  std::vector<int> beauty(n, 0);
  for (int p = 0; p < n; p++) {
    std::cin >> beauty[p];
  }
  sort(beauty.begin(), beauty.end()); // Sort the array to facilitate grouping
  int count(1), maxCount(1);
  for (int p = 1; p < n; p++) {
    if (beauty[p] == beauty[p - 1]) {
      ++count; // Increment count if current element equals previous one
    } else {
      count = 1; // Reset count when element changes
    }
    maxCount = (count > maxCount) ? count : maxCount; // Track maximum group size
  }
  std::cout << (n - maxCount) << std::endl; // Result is total elements minus max group size
  return 0;
}


// https://github.com/VaHiX/CodeForces/