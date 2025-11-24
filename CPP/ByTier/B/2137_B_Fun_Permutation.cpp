// Problem: CF 2137 B - Fun Permutation
// https://codeforces.com/contest/2137/problem/B

#include <cstdio>
int n, T, i, p;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
      scanf("%d", &p);
      printf("%d ", n + 1 - p); // Transform permutation: map each element to its reverse position
    }
    printf("\n");
  }
}
/*
B. Fun Permutation

Algorithms/Techniques: Simple permutation transformation

Time Complexity: O(n) per test case, where n is the size of the permutation.
Space Complexity: O(1) additional space (excluding input/output).

The problem asks to find a permutation q such that GCD of sums of adjacent elements in p and q is at least 3.
This can be solved by simply mapping each element p[i] to n+1-p[i], which ensures that the sum of adjacent elements
in the original and transformed permutations has a large enough GCD due to symmetry.
*/

// https://github.com/VaHiX/codeForces/