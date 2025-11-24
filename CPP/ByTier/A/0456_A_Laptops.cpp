// Problem: CF 456 A - Laptops
// https://codeforces.com/contest/456/problem/A

/*
 * Problem: Determine if Alex is correct in claiming that there exists a laptop
 *          with lower price but higher quality than another laptop.
 * 
 * Approach:
 * - Sort laptops by price (ascending).
 * - After sorting, if we find any laptop with higher quality than the next one,
 *   it means Alex is correct.
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the laptop data
 * 
 * Algorithm:
 *   1. Read n laptops with price and quality.
 *   2. Sort by price.
 *   3. Scan through sorted list and check if quality decreases (indicating Alex is right).
 * 
 * Techniques:
 *   - Sorting
 *   - Linear scan after sorting
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<std::pair<long, long>> data(n);
  for (int p = 0; p < n; p++) {
    scanf("%ld %ld\n", &data[p].first, &data[p].second);
  }
  sort(data.begin(), data.end());  // Sort by price (first element of pair)
  bool happyAlex = 0;
  for (int p = 0; p < n - 1; p++) {
    if (data[p].second > data[p + 1].second) {  // Check if quality drops
      happyAlex = 1;
    }
  }
  puts(happyAlex ? "Happy Alex" : "Poor Alex");
  return 0;
}


// https://github.com/VaHiX/CodeForces/