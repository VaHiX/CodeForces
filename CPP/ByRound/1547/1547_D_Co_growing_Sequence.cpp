// Problem: CF 1547 D - Co-growing Sequence
// https://codeforces.com/contest/1547/problem/D

/*
D. Co-growing Sequence

Algorithm:
This problem asks to find a lexicographically minimal sequence y such that the sequence x[i] ^ y[i] is "growing".
A sequence is growing if for all i, x[i] & x[i+1] == x[i]. This means each number in the sequence must have all bits set 
in the previous number.

Approach:
We process elements one by one and construct the answer y greedily.
For the first element, we can set y[0] = 0 because a single element is always growing.
For subsequent elements:
- Let prev be the value of (x[i-1] ^ y[i-1]) computed so far
- To make current element x[i] ^ y[i] compatible with prev (i.e. it's a growing sequence), we set:
    - y[i] = prev & (~x[i]) 
    - And update prev = x[i] ^ y[i] for next iteration

Time Complexity: O(n)
Space Complexity: O(1)
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    printf("0 "); // First y[0] is always 0 to minimize lexicographically
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // Compute y[p] such that (x[p] ^ y[p]) maintains the growing property
      long y = prev & (~x); // Mask to preserve only bits set in prev but not in x
      prev = x ^ y;         // Update prev for next iteration
      printf("%ld ", y);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/