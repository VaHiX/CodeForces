// Problem: CF 1831 A - Twin Permutations
// https://codeforces.com/contest/1831/problem/A

/*
Purpose: 
This code solves the problem of constructing a permutation b such that the sums a[0] + b[0], a[1] + b[1], ..., a[n-1] + b[n-1] are in non-decreasing order. 
The approach is to set b[i] = n + 1 - a[i] for each i. This ensures that when we sort the sums, they will be in non-decreasing order due to the properties of the transformation.

Algorithms/Techniques:
- Simple mathematical transformation: For each element a[i], assign b[i] = n + 1 - a[i].
- This guarantees the required order of sums.

Time Complexity: O(n) per test case, where n is the length of the permutation.
Space Complexity: O(1) extra space (not counting input/output storage).

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      printf("%ld ", n + 1 - x); // Assign b[i] = n + 1 - a[i] to ensure ordered sums
    }
    puts(""); // Print new line after each test case
  }
}


// https://github.com/VaHiX/CodeForces/