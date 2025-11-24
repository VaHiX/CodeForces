// Problem: CF 1537 C - Challenging Cliffs
// https://codeforces.com/contest/1537/problem/C

/*
C. Challenging Cliffs
Purpose: Arrange mountain heights to minimize the absolute difference between first and last mountain,
         while maximizing the number of uphill steps (difficulty score).
Algorithms/Techniques: Sorting, greedy arrangement based on minimal difference and maximum difficulty.
Time Complexity: O(n log n) per test case due to sorting; overall is O(sum(n) * log(sum(n)))
Space Complexity: O(n) for storing the heights vector
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
    std::vector<long> h(n); // Store mountain heights
    for (long p = 0; p < n; p++) {
      scanf("%ld", &h[p]);
    }
    sort(h.begin(), h.end()); // Sort heights to find minimal difference efficiently
    long mindiff(1e9 + 7), pos(-1), left(-1), right(-1);
    for (long p = 1; p < n; p++) {
      long diff = h[p] - h[p - 1]; // Calculate difference between adjacent sorted heights
      if (diff < mindiff) {
        mindiff = diff;
        pos = p;
        left = h[p - 1];
        right = h[p];
      }
    }
    printf("%ld ", left); // Print the left element of the minimal difference pair
    for (long p = pos + 1; p < n; p++) {
      printf("%ld ", h[p]); // Print remaining elements after the pair
    }
    for (long p = 0; p < pos - 1; p++) {
      printf("%ld ", h[p]); // Print elements before the pair
    }
    printf("%ld\n", right); // Print the right element of the minimal difference pair
  }
}


// https://github.com/VaHiX/codeForces/