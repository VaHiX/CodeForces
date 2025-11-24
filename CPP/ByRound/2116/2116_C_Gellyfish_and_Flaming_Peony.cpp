// Problem: CF 2116 C - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2116/problem/C

/*
C. Gellyfish and Flaming Peony
Algorithms/Techniques: Dynamic Programming with GCD properties
Time Complexity: O(N * MAX_A * log(MAX_A)) where N is the number of elements and MAX_A = 5000
Space Complexity: O(MAX_A)

The problem involves reducing an array to all equal elements using operations that replace one element with gcd of itself and another.
This solution uses dynamic programming where f[g] represents the minimum operations needed to make all elements have GCD g.
We process elements in order, updating dp table by considering operations with previously seen values.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 5000 + 5, mod = 998244353, INF = 5000 + 5;
int kase, n, a[N], f[N];

// Function to compute greatest common divisor
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main() {
  scanf("%d", &kase);
  while (kase--) {
    // Initialize dp array with infinity
    memset(f, 0x3f, sizeof(f));
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
      scanf("%d", &a[i]);
      x = a[i];
      // Iterate backwards to avoid using updated values in same iteration
      for (int j = 5000; j >= 1; j--)
        if (f[j] < INF) {
          int g = gcd(x, j);  // Compute GCD of current value and existing GCD
          f[g] = min(f[g], f[j] + 1);  // Update minimum operations needed
        }
      f[x] = 0;  // Base case: element itself needs 0 operations to achieve GCD x
    }
    int res = 0, ans = 0;
    // Find the smallest non-infinite GCD value (starting from 1)
    for (int i = 1; i <= 5000; i++)
      if (f[i] < INF) {
        res = i;
        break;
      }
    if (f[res] == 0) {
      // If result GCD is same as original array's element, count non-matching elements
      for (int i = 1; i <= n; i++)
        if (a[i] != res)
          ans++;
      printf("%d\n", ans);
    } else
      // Otherwise, add operations to make all elements equal to res
      printf("%d\n", f[res] + n - 1);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/