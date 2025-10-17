// Problem: CF 1928 B - Equalize
// https://codeforces.com/contest/1928/problem/B

/*
 * Problem: B. Equalize
 *
 * Purpose:
 *   Given an array of integers, we can add a permutation of numbers 1 to n to the array,
 *   such that each element `a[i]` becomes `a[i] + p[i]`. After this operation, we want
 *   to maximize the frequency of the most frequently occurring number in the resulting array.
 *
 * Algorithm:
 *   - For each unique element in the original array, create a list of those elements.
 *   - Sort the unique elements.
 *   - Use a sliding window technique:
 *     * For each starting element `v[p]`, find the maximum number of elements that can
 *       be covered by adding values from 1 to n such that all resulting sums are within
 *       range `[v[p], v[p] + n)`.
 *   - The time complexity is O(n log n) per test case due to sorting and sliding window.
 *   - Space complexity is O(n) for storing the unique elements.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v;         // Vector to store unique elements of the array
    std::set<long> s;            // Set to track which elements we've already added to vector
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (s.count(x)) {          // Skip duplicates
        continue;
      }
      v.push_back(x);            // Add unique element to vector
      s.insert(x);               // Mark as seen
    }
    sort(v.begin(), v.end());    // Sort the unique elements

    long idx(0);                 // Right pointer for sliding window
    long ans(0);                 // Maximum count found so far
    for (long p = 0; p < v.size(); p++) {
      // Move idx forward while next element is less than v[p] + n
      while (idx + 1 < v.size() && v[idx + 1] < v[p] + n) {
        ++idx;
      }
      long len = idx - p + 1;    // Length of current window
      ans = (ans > len) ? ans : len; // Update maximum length
      if (idx + 1 == v.size()) {
        break;                   // End of array
      }
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/