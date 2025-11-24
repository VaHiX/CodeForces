// Problem: CF 1847 A - The Man who became a God 
// https://codeforces.com/contest/1847/problem/A

/*
 * Problem: A. The Man who became a God
 *
 * Task: Split n villagers into exactly k contiguous subgroups such that the sum of their "power" is minimized.
 * Power of a group from l to r is defined as: f(l,r) = |a[l] - a[l+1]| + |a[l+1] - a[l+2]| + ... + |a[r-1] - a[r]|
 *
 * Algorithm:
 * 1. For each test case, compute differences between adjacent elements.
 * 2. Sort these differences in descending order.
 * 3. Select the smallest (n - k) differences to exclude from total sum.
 *
 * Time Complexity: O(n log n) per test case due to sorting of differences.
 * Space Complexity: O(n) for storing the differences.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v; // Vector to store absolute differences between adjacent elements
    long cur;
    scanf("%ld", &cur); // Read first element
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x); // Read next element
      long diff = cur - x; // Compute difference
      diff = (diff > 0) ? diff : -diff; // Take absolute value
      v.push_back(diff); // Store absolute difference
      cur = x; // Update current element
    }
    sort(v.rbegin(), v.rend()); // Sort differences in descending order
    long res(0); // Result to store minimum sum of power
    for (long p = k - 1; p < v.size(); p++) {
      res += v[p]; // Add the smallest (n - k) differences to result
    }
    printf("%ld\n", res); // Print result
  }
}


// https://github.com/VaHiX/codeForces/