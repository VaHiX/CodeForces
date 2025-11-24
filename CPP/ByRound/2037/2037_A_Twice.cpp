// Problem: CF 2037 A - Twice
// https://codeforces.com/contest/2037/problem/A

/*
 * Problem: Maximum Score from Pairing Equal Elements
 *
 * Description:
 * Given an array of integers, we want to maximize the score by pairing equal elements.
 * Each pair contributes 1 to the score. We can perform this operation any number of times,
 * as long as we select two indices i and j such that a[i] == a[j] and neither index has been used before.
 *
 * Algorithm:
 * - For each test case, count frequency of each element using a map.
 * - For every element with frequency f, we can form f/2 pairs (integer division).
 * - Sum up all such pairs to get the maximum score.
 *
 * Time Complexity: O(n log n) per test case due to map operations.
 * Space Complexity: O(n) for storing frequencies in the map.
 */

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m;  // Map to store frequency of each element
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x];  // Increment frequency count for element x
    }
    long score(0);
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      score += (it->second) / 2;  // Add number of pairs possible from this frequency
    }
    printf("%ld\n", score);
  }
}


// https://github.com/VaHiX/codeForces/