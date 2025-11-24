// Problem: CF 1790 C - Premutation
// https://codeforces.com/contest/1790/problem/C

/*
C. Permutation
Algorithm: Reconstruction of a permutation from n sequences of length n-1,
each missing one element of the original permutation.
Time Complexity: O(n^2) per test case due to nested loops for finding the first element and reconstructing.
Space Complexity: O(n^2) for storing the sequences.

The approach:
1. Read all n sequences of length n-1.
2. Identify the first element of the original permutation by checking which value appears in multiple 
   positions across different sequences.
3. Use this first element to deduce the complete permutation by finding a sequence that starts with it,
   and then filling in the rest.

Techniques:
- Vector-based storage for sequences
- Iterative reconstruction based on overlap between sequences
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::vector<long>> m(n, std::vector<long>(n - 1, 0));
    for (long row = 0; row < n; row++) {
      for (long col = 0; col + 1 < n; col++) {
        scanf("%ld", &m[row][col]);
      }
    }
    long a(m[0][0]), b(0), first(0);
    for (long row = 1; !first && row < n; row++) {
      long x = m[row][0];
      if (a == x) {
        first = a;
        break;
      } else if (b == x) {
        first = b;
        break;
      } else {
        b = x;
      }
    }
    printf("%ld ", first);
    for (long row = 0; row < n; row++) {
      if (m[row][0] == first) {
        continue;
      }
      for (long col = 0; col + 1 < n; col++) {
        printf("%ld ", m[row][col]);
      }
      break;
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/