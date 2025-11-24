// Problem: CF 1823 A - A-characteristic
// https://codeforces.com/contest/1823/problem/A

#include <cstdio>
// Purpose: Given array length n and target A-characteristic k, find an array of 1s and -1s
//          such that the number of pairs (i,j) with i<j and a[i]*a[j]=1 equals k.
//          A-characteristic counts pairs of elements with the same sign (both 1 or both -1).
//
// Algorithm:
//   - For an array with p 1s and (n-p) -1s:
//     - Pairs of 1s: p*(p-1)/2
//     - Pairs of -1s: (n-p)*(n-p-1)/2
//     - Total A-characteristic = p*(p-1)/2 + (n-p)*(n-p-1)/2
//   - Enumerate all possible p values from 0 to n/2 and check if the formula gives k.
//   - If yes, output an array with p 1s followed by (n-p) -1s.
//
// Time Complexity: O(n^2) in worst case due to nested loop over p.
// Space Complexity: O(1), only using a few variables.
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long same(-1);
    for (long p = 0; 2 * p <= n; p++) {
      long tst = p * (p - 1) / 2 + (n - p) * (n - p - 1) / 2;
      if (tst == k) {
        same = p;
        break;
      }
    }
    if (same < 0) {
      puts("NO");
    } else {
      puts("YES");
      for (long p = 0; p < n; p++) {
        printf("%d ", p < same ? 1 : -1);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/