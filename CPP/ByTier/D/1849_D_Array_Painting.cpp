// Problem: CF 1849 D - Array Painting
// https://codeforces.com/contest/1849/problem/D

#include <cstdio>
#include <vector>
// Problem: Array Painting
// Task: Given an array of integers (0, 1, or 2), paint all elements red with minimum coins.
//       Two operations:
//       1. Pay 1 coin to directly paint a blue element red.
//       2. Pay 1 coin to decrease a red element > 0 and paint an adjacent blue element red.
//
// Algorithm: Greedy approach. Iterate from left to right:
//            - If current element is 0, check if we can use a previous red element (if exists) to paint it.
//            - If current element is 1 or 2, try to use it to paint the next blue element if possible.
//            - Otherwise, pay one coin to paint current element directly.
//
// Time Complexity: O(n)
// Space Complexity: O(n)

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read array elements
  }
  long cost(0); // Initialize coin counter
  for (long p = 0; p < n; p++) {
    if (p && a[p - 1]) { // If previous element is red (non-zero), use it to paint current blue
      --a[p - 1]; // Decrease the red element
    } else if (!a[p] && p + 1 < n && a[p + 1]) { // If current is blue and next is red
      --a[p + 1]; // Use next red to paint current blue
    } else {
      ++cost; // Else pay coin to paint current directly
    }
  }
  printf("%ld\n", cost); // Output minimum coins needed
  return 0;
}

// https://github.com/VaHiX/codeForces/