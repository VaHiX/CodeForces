// Problem: CF 1360 B - Honest Coach
// https://codeforces.com/contest/1360/problem/B

/*
B. Honest Coach
Algorithm: Sort the array and find the minimum difference between adjacent elements.
Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the vector of strengths.

The problem asks to split athletes into two teams such that the absolute difference
between the maximum strength in team A and minimum strength in team B is minimized.
By sorting the array, we can check adjacent pairs to find the smallest gap,
which gives us the optimal split since any other split would result in a larger
difference or equal difference at best.
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
    std::vector<long> s(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &s[p]);
    }
    sort(s.begin(), s.end()); // Sort the strengths to check adjacent differences
    long mn(s.back() + 7); // Initialize with a large value
    for (long p = 1; p < n; p++) {
      long diff = s[p] - s[p - 1]; // Compute difference between adjacent elements
      mn = (mn < diff) ? mn : diff; // Keep track of the minimum difference
    }
    printf("%ld\n", mn);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/