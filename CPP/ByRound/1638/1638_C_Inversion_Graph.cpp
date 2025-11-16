// Problem: CF 1638 C - Inversion Graph
// https://codeforces.com/contest/1638/problem/C

/*
C. Inversion Graph
Algorithm: For each element in the permutation, we determine if it forms a new connected component by checking whether it's greater than or equal to the maximum element seen so far. If it is, then it starts a new component.
Time Complexity: O(n) per test case, where n is the length of the permutation.
Space Complexity: O(1), only using a few variables.

The problem constructs a graph where an edge exists between indices i and j (i < j) if p_i > p_j. 
This means that for each element, if it's greater than or equal to all previous elements,
it starts a new connected component.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mx(0), cnt(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      mx = (mx > x) ? mx : x;              // Update the maximum element seen so far
      cnt += (mx == p);                    // If current max equals p, it's a new component
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/