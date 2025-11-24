// Problem: CF 1408 A - Circle Coloring
// https://codeforces.com/contest/1408/problem/A

/*
Purpose: 
This code solves the "Circle Coloring" problem where we need to select values from three sequences a, b, c such that 
no two adjacent elements in the resulting sequence are equal, and the sequence forms a cycle (last element connects to first).

Algorithm:
- For each position, we try to pick a value that is different from the previous selected value.
- We use a greedy approach: 
  1. Start by selecting the first element from 'a'.
  2. For each subsequent element, try to select from a, b, c in order, choosing the one that is not equal to the previously selected value.
  3. For the last element, make sure it's not equal to both the first and the previous selected value to ensure the circular constraint.

Time Complexity: O(n) - We iterate through the list once.
Space Complexity: O(n) - We store three vectors of size n.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    std::vector<long> c(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &c[p]);
    }
    long cur(0), prev(a[0]); // prev stores the previously selected value
    printf("%ld ", prev);     // Start by selecting first element from 'a'
    for (long p = 1; p + 1 < n; p++) { // Process elements from index 1 to n-2
      long cur(0);
      if (a[p] != prev) {
        cur = a[p];  // Choose a[p] if it's different from previous
      } else if (b[p] != prev) {
        cur = b[p];  // Choose b[p] if it's different from previous
      } else if (c[p] != prev) {
        cur = c[p];  // Choose c[p] if it's different from previous
      }
      printf("%ld ", cur);
      prev = cur; // update previous value
    }
    // Handle the last element ensuring it doesn't conflict with first or previous
    if (a.back() != a[0] && a.back() != prev) {
      cur = a.back();
    } else if (b.back() != a[0] && b.back() != prev) {
      cur = b.back();
    } else if (c.back() != a[0] && c.back() != prev) {
      cur = c.back();
    }
    printf("%ld\n", cur);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/