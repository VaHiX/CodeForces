// Problem: CF 1848 B - Vika and the Bridge
// https://codeforces.com/contest/1848/problem/B

/*
B. Vika and the Bridge
Algorithm: For each color, we track the maximum gap between consecutive occurrences of that color,
and also handle the trailing gap from the last occurrence to the end of the bridge.
We consider repainting one plank to minimize the maximum gap.
Time Complexity: O(n) per test case
Space Complexity: O(k) per test case
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> last(k + 1, 0);             // Tracks last occurrence of each color
    std::vector<long> first(k + 1, 0);            // Tracks the largest gap for each color
    std::vector<long> second(k + 1, 0);           // Tracks the second largest gap for each color
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      long dist = p - last[x] - 1;                // Distance from previous occurrence of same color
      last[x] = p;
      if (dist >= first[x]) {
        second[x] = first[x];
        first[x] = dist;
      } else if (dist >= second[x]) {
        second[x] = dist;
      }
    }
    for (long p = 1; p <= k; p++) {
      long dist = n - last[p];                    // Distance from last occurrence to end of bridge
      if (dist >= first[p]) {
        second[p] = first[p];
        first[p] = dist;
      } else if (dist >= second[p]) {
        second[p] = dist;
      }
    }
    long ans(n);                                  // Initialize answer with n (worst case)
    for (long p = 1; p <= k; p++) {
      long cur = second[p];                       // Current second max gap
      if (cur <= first[p] / 2) {
        cur = first[p] / 2;                       // If second is <= half of first, use half of first
      }
      ans = (ans < cur) ? ans : cur;              // Take minimum among all colors
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/