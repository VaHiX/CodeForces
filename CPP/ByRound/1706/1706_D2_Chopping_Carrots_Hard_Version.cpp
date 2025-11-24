// Problem: CF 1706 D2 - Chopping Carrots (Hard Version)
// https://codeforces.com/contest/1706/problem/D2

/*
Code Purpose:
This code solves the problem of finding the minimum cost of an array p such that each element p[i] satisfies 1 <= p[i] <= k,
and the cost is defined as the difference between the maximum and minimum values of floor(a[i]/p[i]) across all elements.
The approach uses a sweep line technique with frequency counting to efficiently compute the minimum cost.

Algorithms/Techniques:
1. Sweep line technique with frequency counting
2. Preprocessing to map floor division results to ranges
3. Efficiently calculating minimum cost by sweeping through the frequency array

Time Complexity:
O(n * sqrt(max(a[i])) + max(a[1])) where n is the number of elements in the array and max(a[i]) is the maximum element.
The dominant factor comes from iterating over possible divisors of elements in the array.

Space Complexity:
O(max(a[1]) + 1) for the frequency array f, which stores the maximum value for each possible floor division result.
*/
#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
int T, n, k, a[100005], f[100005];
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    memset(f, 0, sizeof(f)); // Reset frequency array
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      int y = 1e9, x; // y stores previous quotient, x is current quotient
      // Iterate through all possible quotient values for a[i]
      for (int j = 1; j <= min(k, a[i]); j = (a[i] / x) + 1) {
        x = a[i] / j; // Calculate current floor division result
        f[x + 1] = max(f[x + 1], y); // Update frequency array
        y = x; // Store current quotient for next iteration
      }
      f[0] = max(f[0], y); // Handle case when quotient is 0
    }
    int ans = 1e9, x = 0; // ans tracks minimum cost, x tracks maximum seen so far
    // Sweep through the frequency array to find minimum cost
    for (int i = 0; i <= a[1]; i++) {
      x = max(x, f[i]); // Update maximum value for current range
      ans = min(ans, x - i); // Update minimum cost
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/