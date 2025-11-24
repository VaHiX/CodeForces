// Problem: CF 1711 A - Perfect Permutation
// https://codeforces.com/contest/1711/problem/A

/*
Algorithm: Perfect Permutation
Techniques: Simple constructive algorithm

Time Complexity: O(n) per test case, where n is the length of the permutation.
Space Complexity: O(1) extra space (not counting input/output).

This solution constructs a permutation by cyclically shifting elements.
For each index p (0-based), we place (p + 1) % n + 1 at that position.
This ensures that the only valid position where i divides p_i is at index 1 (1-based),
which results in a minimum possible weight of 1 for all n > 1.
For n = 1, the only permutation [1] has weight 1.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      // Construct the permutation using cyclic shift
      printf("%ld ", 1 + ((p + 1) % n));
    }
    puts(""); // Print newline after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/