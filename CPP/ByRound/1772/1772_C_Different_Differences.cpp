// Problem: CF 1772 C - Different Differences
// https://codeforces.com/contest/1772/problem/C

/*
 * Purpose: Construct a strictly increasing array of k integers from 1 to n
 *          such that the number of distinct differences between consecutive
 *          elements (characteristic) is maximized.
 *
 * Algorithm:
 * - Start with the first element as 1.
 * - Use a greedy approach to select the next elements, trying to increment
 *   the difference at each step to maximize distinct differences.
 * - When it's no longer possible to maintain distinct differences without
 *   exceeding n, fall back to incrementing by 1.
 *
 * Time Complexity: O(k) per test case, as we iterate through k elements once.
 * Space Complexity: O(k) for storing the array a.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k, n;
    scanf("%ld %ld", &k, &n);
    std::vector<long> a(k + 1); // 1-indexed array to store the sequence
    a[1] = 1; // First element is always 1
    long d(1); // Current difference to use, starts at 1
    for (long p = 2; p <= k; p++) {
      if (d < 0) {
        // If we've switched to decrementing differences, just increment by 1
        a[p] = a[p - 1] + 1;
        continue;
      }
      long x = a[p - 1] + d; // Calculate the next element based on current difference
      if (n - x < k - p) {
        // If there aren't enough numbers left to continue with this difference,
        // switch to incrementing by 1 and set d to -1 to indicate this state
        a[p] = a[p - 1] + 1;
        d = -1;
      } else {
        // Otherwise, proceed with the current difference
        a[p] = x;
        ++d; // Increase difference for the next step to ensure distinct values
      }
    }
    for (long p = 1; p <= k; p++) {
      printf("%ld ", a[p]);
    }
    puts(""); // Print newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/