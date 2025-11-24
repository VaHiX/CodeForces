// Problem: CF 476 D - Dreamoon and Sets
// https://codeforces.com/contest/476/problem/D

/*
D. Dreamoon and Sets

Purpose:
This program constructs n sets of four distinct positive integers each, such that:
- Each set has rank k (i.e., gcd of any two elements in the set is exactly k).
- All integers used are between 1 and m.
- The total number of distinct integers used (m) is minimized.

Approach:
The key idea is to construct sets using multiples of k. For a set of rank k, we ensure that:
- Every element is divisible by k.
- GCD of any two distinct elements in the set equals k.
To achieve this, we take 4 consecutive integers (not divisible by k), multiply them all by k,
and ensure the base integers are chosen so their pairwise GCDs are 1.

Algorithm:
- For each set, start with index p and generate four numbers: 6*p+1, 6*p+2, 6*p+3, 6*p+5.
- Multiply these by k to make them valid for rank k.
- The largest number used is k * (6*n - 1).

Time Complexity:
O(n) - We iterate through n sets and print 4 numbers per set.

Space Complexity:
O(1) - No extra space used except for variables.

*/
#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld\n", &n, &k);
  printf("%ld\n", k * (6 * n - 1)); // Minimum m needed
  for (long p = 0; p < n; p++) {
    // Generate 4 numbers in the form: k*(6*p+1), k*(6*p+2), k*(6*p+3), k*(6*p+5)
    printf("%ld %ld %ld %ld\n", k * (6 * p + 1), k * (6 * p + 2),
           k * (6 * p + 3), k * (6 * p + 5));
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/