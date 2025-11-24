// Problem: CF 1975 A - Bazoka and Mocha's Array
// https://codeforces.com/contest/1975/problem/A

/*
 * Problem: A. Bazoka and Mocha's Array
 * 
 * Description:
 * Determine if an array can be sorted in non-decreasing order by performing
 * a series of operations where we split the array into two parts and swap them.
 * This is equivalent to checking whether the array is a rotation of a sorted array.
 *
 * Algorithm:
 * 1. Find the index where the array starts to decrease (first dip).
 * 2. If no such index exists, the array is already sorted.
 * 3. Otherwise, treat the array as rotated and check if rotating at that point
 *    results in a non-decreasing sequence.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
 */

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
    long idx(0);
    // Find the first position where array decreases
    for (long p = 1; p < n; p++) {
      if (v[p - 1] > v[p]) {
        idx = p;
      }
    }
    long prev = v[idx];
    bool ans(true);
    // Check if rotating at 'idx' gives a non-decreasing sequence
    for (long p = 1; ans && p < n; p++) {
      long q = (p + idx) % n;
      if (prev > v[q]) {
        ans = false;
      }
      prev = v[q];
    }
    puts(ans ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/