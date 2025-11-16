// Problem: CF 1557 A - Ezzat and Two Subsequences
// https://codeforces.com/contest/1557/problem/A

/*
Purpose: This code solves the problem of splitting an array into two non-empty subsequences such that the sum of their averages is maximized.

Algorithm:
- For each possible split, we want to maximize f(a) + f(b), where f(x) is the average of subsequence x.
- The key insight is that to maximize the sum of averages, we should put the maximum element in one subsequence (to maximize its contribution to that average), and the rest in another (to minimize the average of the second subsequence).
- We place the maximum element in a subsequence of size 1 (to keep its value as the average), and the rest in the other subsequence.
- Let 'mx' be the maximum element, 's' be the sum of all elements.
- Then, f(a) = mx (since it's alone in its subsequence), and f(b) = (s - mx) / (n - 1) (average of the rest).
- The maximum value is therefore: mx + (s - mx) / (n - 1).

Time Complexity: O(n) per test case, where n is the number of elements in the array.
Space Complexity: O(1), as we only use a constant amount of additional space.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long double s(0), mx(-1e11); // s = sum of elements, mx = maximum element
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x; // accumulate the sum
      mx = (mx > x) ? mx : x; // keep track of the maximum element
    }
    double res = mx + (s - mx) / (n - 1); // compute the optimal value
    printf("%.10lf\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/