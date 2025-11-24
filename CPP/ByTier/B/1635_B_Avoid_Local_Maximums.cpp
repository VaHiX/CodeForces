// Problem: CF 1635 B - Avoid Local Maximums
// https://codeforces.com/contest/1635/problem/B

/*
Algorithm: Greedy Approach
- We iterate through the array to find local maximums (elements greater than both neighbors).
- When a local maximum is found, we modify the next element to reduce the number of local maximums.
- This greedy strategy ensures optimal operation count.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing the array.

Techniques:
- Single pass through the array.
- Greedy local modification to avoid local maximums.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1);  // Extra space for safety check
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    a[n] = 1e9 + 7;  // Sentinel value to avoid boundary checks
    long cnt(0);     // Counter for operations
    for (long p = 1; p + 1 < n; p++) {  // Skip first and last elements
      if (a[p - 1] < a[p] && a[p] > a[p + 1]) {  // Found a local maximum
        if (p + 2 >= n) {
          // If we are near end, set next element equal to current
          a[p + 1] = a[p];
        } else {
          // Otherwise, set next element to max of current and next next
          a[p + 1] = a[p] > a[p + 2] ? a[p] : a[p + 2];
        }
        ++cnt;  // Increment operation count
      }
    }
    printf("%ld\n", cnt);
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/