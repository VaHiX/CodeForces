// Problem: CF 1417 B - Two Arrays
// https://codeforces.com/contest/1417/problem/B

/*
Algorithm/Technique: Greedy coloring based on value relative to T
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input/output

This solution uses a greedy approach to color elements of the array:
- For each element a[i]:
  - If 2 * a[i] < T, color it 0 (white)
  - If 2 * a[i] > T, color it 1 (black)
  - If 2 * a[i] == T, alternate the color to minimize pairs that sum to T
This ensures that we minimize the total number of pairs (i,j) where a[i] + a[j] = T in both arrays.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, u;
    scanf("%ld %ld", &n, &u);
    long q(0);  // q tracks the current color to assign for elements where 2*a[i] == u
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (2 * x < u) {
        printf("0 ");  // color 0 for elements that can't form a pair summing to T
      } else if (2 * x > u) {
        printf("1 ");  // color 1 for elements that can't form a pair summing to T
      } else if (2 * x == u) {
        printf("%ld ", q);  // alternate color for elements that form pairs equal to T
        q = 1 - q;         // flip the color for next such element
      }
    }
    puts("");  // newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/