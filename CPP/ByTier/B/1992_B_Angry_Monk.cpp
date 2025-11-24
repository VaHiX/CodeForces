// Problem: CF 1992 B - Angry Monk
// https://codeforces.com/contest/1992/problem/B

/*
B. Angry Monk
Purpose: Given a casserole of length n cut into k pieces, find the minimum number of operations to merge all pieces into one.
Operations:
1. Split a piece of length >= 2 into two pieces of lengths 1 and (a_i - 1).
2. Merge a piece of length > 1 with a piece of length 1 into a single piece of length (a_i + 1).

Algorithm: 
- For each test case, scan all k pieces.
- Keep track of the maximum piece size and total sum of all piece sizes.
- Initially, assume we need to split all pieces (total = 2 * x - 1 for each piece).
- Subtract the contribution of the largest piece, since it does not require splitting when merged with smaller ones.

Time Complexity: O(k) per test case.
Space Complexity: O(1).

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long total(0), mx(0); // total stores cumulative operations, mx tracks max piece
    for (long p = 0; p < k; p++) {
      long x;
      scanf("%ld", &x);
      mx = (mx > x ? mx : x); // update maximum piece size
      total += (2 * x - 1);   // each piece contributes 2*x - 1 operations if split entirely
    }
    total -= (2 * mx - 1);    // subtract overcounted operations due to max piece
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/