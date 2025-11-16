// Problem: CF 1401 C - Mere Array
// https://codeforces.com/contest/1401/problem/C

/*
C. Mere Array
Purpose: Determine if an array can be made non-decreasing by swapping elements whose GCD equals the minimum element in the array.

Algorithms/Techniques:
- For each test case, find the minimum element in the array.
- Sort a copy of the array to determine the target order.
- For each element that is not in its sorted position:
  - If it's divisible by the minimum element, it can be swapped with some other element.
  - Otherwise, it cannot be moved and the result is impossible.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the array copies.

Input:
- Number of test cases t
- For each test case:
  - Length of array n
  - Array elements a[0], ..., a[n-1]

Output:
- YES if the array can be made non-decreasing using the allowed swaps
- NO otherwise

Example:
Input:
4
1
8
6
4 3 6 6 2 9
4
4 5 6 7
5
7 5 2 2 4

Output:
YES
YES
YES
NO
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
    std::vector<long> a(n), b(n); // a holds original, b holds sorted copy
    long mn(1e9 + 7); // Initialize minimum to large value
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a[p] = x;
      b[p] = x;
      mn = (mn < x) ? mn : x; // Keep track of the minimum element
    }
    sort(b.begin(), b.end()); // Sort copy to determine target order
    bool res(true);
    for (long p = 0; p < n; p++) {
      if (a[p] == b[p]) {
        continue; // Element is already in correct position
      }
      if (a[p] % mn == 0) {
        continue; // Can be swapped with some element because it's divisible by min
      }
      res = false;
      break;
    }
    puts(res ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/