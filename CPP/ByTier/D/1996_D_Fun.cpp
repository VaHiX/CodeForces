// Problem: CF 1996 D - Fun
// https://codeforces.com/contest/1996/problem/D

/*
Purpose: 
This code counts the number of ordered triplets (a, b, c) of positive integers such that:
1. ab + ac + bc <= n
2. a + b + c <= x

Algorithms/Techniques:
- Brute-force enumeration with optimizations
- Mathematical optimization to reduce iteration space
- Symmetry handling for cases where a == b

Time Complexity: O(n^(3/2)) in the worst case due to nested loops over square root of n
Space Complexity: O(1), only using a few variables

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, x;
    scanf("%d%d", &n, &x);
    ll ans = 0;
    // Iterate a from 1 to sqrt(n) for optimization
    for (int a = 1; a * a <= n; a++) {
      // Iterate b from a to sqrt(n) to avoid duplicate triplets
      for (int b = a; b * b <= n; b++) {
        // Skip if the remaining constraint cannot be satisfied
        if (n - 2 * a * b - b * b < 0)
          continue;
        // Calculate the maximum possible value for c based on the constraint ab + ac + bc <= n
        int l1 = int((n - 2 * a * b - b * b) / (a + b)) + 1;
        // Calculate the maximum possible value for c based on a + b + c <= x
        int l2 = x - a - 2 * b + 1;
        // Take minimum to satisfy both constraints
        int l = min(l1, l2);
        if (l <= 0)
          continue;
        // If a == b, there are 1 + 3*(l-1) valid permutations
        if (a == b) {
          ans += 1 + 3 * (l - 1);
        } else {
          // If a != b, there are 3 + 6*(l-1) valid permutations
          ans += 3 + 6 * (l - 1);
        }
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/