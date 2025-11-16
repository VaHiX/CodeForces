// Problem: CF 1339 B - Sorted Adjacent Differences
// https://codeforces.com/contest/1339/problem/B

/*
Algorithm: Sorted Adjacent Differences
Approach:
- Sort the array first.
- Use two pointers: one starting from the middle (left) and one from the middle + 1 (right).
- Alternate picking elements from left and right to construct the result.
- This ensures that differences between adjacent elements are non-decreasing.

Time Complexity: O(n log n) due to sorting; the rest is O(n)
Space Complexity: O(1) additional space excluding the input array
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
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort the array to enable greedy approach
    long left((n - 1) / 2), right((n + 1) / 2); // Initialize pointers to mid points
    while (left >= 0 || right < n) {
      if (left >= 0) {
        printf("%ld ", a[left--]); // Pick element from left pointer and decrement
      }
      if (right < n) {
        printf("%ld ", a[right++]); // Pick element from right pointer and increment
      }
    }
    puts(""); // Print new line after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/