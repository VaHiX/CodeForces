// Problem: CF 2033 B - Sakurako and Water
// https://codeforces.com/contest/2033/problem/B

/*
Problem: B. Sakurako and Water
Purpose: Given an n×n matrix where negative values represent lakes, determine the minimum number of operations 
         needed to eliminate all lakes. Each operation increases the height of elements on a main diagonal 
         of a sub-square by 1.

Algorithms/Techniques:
- Difference array technique applied on diagonal elements.
- For each cell (i,j) with negative value, we calculate how many times we need to apply 
  an operation that affects this position. This is done by considering all possible 
  square submatrices where this cell lies on the main diagonal.

Time Complexity: O(n^2) per test case due to iterating through matrix and updating difference arrays.
Space Complexity: O(n^2) for storing the vector v used for difference array technique.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(2 * n - 1); // Difference array to track operations on diagonals
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        long x;
        scanf("%ld", &x);
        long idx = (n - 1) + row - col; // Calculate diagonal index (shifted to make it positive)
        v[idx] = (v[idx] > -x ? v[idx] : -x); // Update with max of current or required operations
      }
    }
    long total(0);
    for (long p = 0; p < v.size(); p++) {
      total += v[p];
    }
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/