// Problem: CF 2110 A - Fashionable Array
// https://codeforces.com/contest/2110/problem/A

/*
 * Problem: Fashionable Array
 * Algorithms/Techniques: Sorting, Greedy
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for the vector storage
 *
 * Description:
 * An array is fashionable if the sum of its minimum and maximum elements is even.
 * We need to find the minimum number of operations (removing elements) to make the array fashionable.
 *
 * Approach:
 * 1. Sort the array.
 * 2. Check two cases:
 *    - Remove elements from the left (smaller values) until we get an even sum of min and max
 *    - Remove elements from the right (larger values) until we get an even sum of min and max
 * 3. Return the minimum count of removals needed.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort the array to easily access min and max
    long cnt(0);
    for (long p = 0; p < n; p++) {
      if ((v[p] + v.back()) % 2) { // If sum of current element and max is odd
        ++cnt;
      } else {
        break; // Stop when we find an even sum
      }
    }
    long ans(cnt); // Number of removals from left side needed
    cnt = 0;
    for (long p = n - 1; p >= 0; p--) {
      if ((v[0] + v[p]) % 2) { // If sum of min and current element is odd
        ++cnt;
      } else {
        break; // Stop when we find an even sum
      }
    }
    ans = (ans < cnt ? ans : cnt); // Minimum operations from either side
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/