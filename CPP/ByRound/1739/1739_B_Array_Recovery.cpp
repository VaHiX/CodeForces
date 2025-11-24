// Problem: CF 1739 B - Array Recovery
// https://codeforces.com/contest/1739/problem/B

/*
B. Array Recovery
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

For an array of non-negative integers a of size n, we construct another array d as follows: d1 = a1, di = |ai - ai-1| for 2 ≤ i ≤ n.
Your task is to restore the array a from a given array d, or to report that there are multiple possible arrays.

Algorithm:
- Start with the first element of array a as the first element of d.
- For each subsequent element, calculate a[i] = a[i-1] + d[i].
- If any d[i] is non-zero and less than or equal to the previous cumulative value, then there's ambiguity in solution (multiple valid arrays possible), hence mark as not unique.
- If unique, output the reconstructed array; otherwise print -1.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array a

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    bool unique(true);
    scanf("%ld", &a[0]); // First element of a is same as first element of d
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x && x <= a[p - 1]) { // If x is non-zero and <= previous cumulative sum, solution is not unique
        unique = false;
      }
      a[p] = a[p - 1] + x; // Compute current element of a based on cumulative sum plus d[i]
    }
    if (unique) {
      for (long p = 0; p < n; p++) {
        printf("%ld ", a[p]);
      }
      puts("");
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/