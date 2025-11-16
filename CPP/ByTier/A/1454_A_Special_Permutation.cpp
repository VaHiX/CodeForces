// Problem: CF 1454 A - Special Permutation
// https://codeforces.com/contest/1454/problem/A

/*
Code Purpose:
This program generates a special permutation for each test case such that no element appears at its corresponding index (i.e., p[i] != i for all i).
The algorithm uses a cyclic shift approach where each element is mapped to the next position in a circular manner.

Algorithms/Techniques:
- Cyclic permutation technique
- Modular arithmetic for index mapping

Time Complexity: O(n) for each test case, where n is the length of the permutation
Space Complexity: O(1) additional space (excluding input/output)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      // For each position p, map it to (p + 1) % n + 1 to create a cycle
      // This ensures no element remains at its original index
      printf("%ld ", 1 + (p + 1) % n);
    }
    puts(""); // Print newline after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/