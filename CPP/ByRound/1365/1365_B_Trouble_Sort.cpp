// Problem: CF 1365 B - Trouble Sort
// https://codeforces.com/contest/1365/problem/B

/*
B. Trouble Sort
Algorithm: Check if we can sort an array by swapping elements of different types (0 and 1).
Time Complexity: O(n) per test case
Space Complexity: O(1)

The key insight is:
1. If the array is already sorted, return "Yes".
2. Otherwise, check if there exists at least one element of each type (0 and 1). 
   - If yes, we can swap elements between types to adjust positions.
   - If no, then all elements are of same type and we cannot swap to sort.

This works because:
- We can only swap elements with different types.
- If we have at least one element of each type (0 and 1), we can rearrange any
  elements in the array into sorted order by swapping appropriately.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool sorted(true); // Check if array is already sorted
    long prev(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p > 0 && x < prev) { // If current element is smaller than previous, not sorted
        sorted = false;
      };
      prev = x; // Keep track of previous element
    }
    bool a(0), z(0); // a tracks presence of type 1, z tracks presence of type 0
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      a |= (x == 1); // Set a to true if any element is 1
      z |= (x == 0); // Set z to true if any element is 0
    }
    bool res = sorted || (a && z); // If already sorted OR both types present, then possible to sort
    puts(res ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/