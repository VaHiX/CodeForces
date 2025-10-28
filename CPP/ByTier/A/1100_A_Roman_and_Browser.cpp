// Problem: CF 1100 A - Roman and Browser
// https://codeforces.com/contest/1100/problem/A

/*
Problem: Roman and Browser
Purpose:
  Given n tabs numbered 1 to n, each tab is either a test-related tab (1) or social network tab (-1). 
  Roman chooses a starting tab b (0 <= b < k), then closes every k-th tab starting from b.
  The goal is to find the maximum absolute difference between the count of test tabs and social network tabs
  among all possible choices of b.

Algorithm:
  - Try all possible starting points b from 0 to k-1
  - For each b, compute the sum of remaining tabs (excluding those at positions b + i*k)
  - The sign of this sum determines whether we have more test tabs or social network tabs
  - Keep track of maximum absolute value of difference

Time Complexity: O(n * k) where n is number of tabs, k is step size
Space Complexity: O(n) for storing the tab values

Techniques:
  - Brute force over all possible starting positions (b)
  - Modular arithmetic to identify which tabs to skip
*/

#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long mx(0);
  for (long b = 0; b < k; b++) {
    long cur(0);
    for (long p = 0; p < n; p++) {
      if ((p % k) == b) { // Skip tabs that are at position b + i*k
        continue;
      }
      cur += a[p]; // Add the value of the tab (1 for test, -1 for social)
    }
    if (cur < 0) {
      cur = -cur; // Take absolute value to get the magnitude of difference
    }
    mx = (mx > cur) ? mx : cur; // Keep track of maximum absolute difference
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/