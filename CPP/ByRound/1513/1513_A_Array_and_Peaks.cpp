// Problem: CF 1513 A - Array and Peaks
// https://codeforces.com/contest/1513/problem/A

/*
Purpose: This program constructs a permutation of numbers from 1 to n that contains exactly k peaks.
A peak is an index i such that 1 < i < n and a[i] > a[i-1] and a[i] > a[i+1].

Algorithm:
- First, we check if it's possible to have k peaks in a permutation of size n.
  The maximum number of peaks possible is (n - 1) / 2.
- We place the largest numbers at even indices (2, 4, 6, ...) to create peaks,
  since placing a large number at an even index ensures it can be a peak if neighbors are smaller.
- Then, we fill the remaining positions with the rest of the numbers in descending order.

Time Complexity: O(n)
Space Complexity: O(n)

Techniques:
- Greedy placement of peak values at even indices
- Filling remaining slots in reverse order
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (k > (n - 1) / 2) {
      puts("-1");
      continue;
    }
    std::vector<long> a(n + 1, -1);  // Initialize array with -1
    long idx(n);  // Start filling from the largest number
    for (long p = 2; p <= n && k > 0; p += 2, k--) {
      a[p] = idx--;  // Place largest available numbers at even positions to form peaks
    }
    for (long p = 1; p <= n; p++) {
      if (a[p] < 0) {
        a[p] = idx--;  // Fill the remaining positions with remaining numbers
      }
    }
    for (long p = 1; p <= n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/