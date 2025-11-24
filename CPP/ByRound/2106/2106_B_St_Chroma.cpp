// Problem: CF 2106 B - St. Chroma
// https://codeforces.com/contest/2106/problem/B

/*
B. St. Chroma
Algorithms/Techniques: Greedy construction
Time complexity: O(n) per test case
Space complexity: O(n) for output array

Given a permutation p of length n containing every integer from 0 to n-1,
we paint cells of a strip based on MEX(p[0], p[1], ..., p[i]).
The goal is to maximize the number of cells painted with color x.

Approach:
To maximize the number of times color x appears, we want to ensure that
the MEX of prefixes equals x as often as possible. This means avoiding
the value x in early positions, then inserting it strategically so that
MEX = x at certain points and increases gradually.

Strategy:
1. For the first n - 1 elements, place all values from 0 to n-2 (except x).
2. Then place x last.
3. When x < n, insert x at the end; otherwise, output any valid permutation.
This ensures that the MEX reaches x many times, but not unnecessarily.

Sample Input:
7
4 2
4 0
5 0
1 1
3 3
1 0
4 3

Sample Output:
1 0 3 2
2 3 1 0
3 2 4 1 0
0
0 2 1
0
1 2 0 3
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    for (size_t p = 0; p < n; p++) {
      // Skip x when it's in the range [0, n)
      if (p != x) {
        printf("%ld ", p);
      }
    }
    // If x is valid (less than n), append it to ensure MEX can reach it
    if (x < n) {
      printf("%ld", x);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/