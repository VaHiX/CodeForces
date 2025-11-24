// Problem: CF 1699 E - Three Days Grace
// https://codeforces.com/contest/1699/problem/E

/*
Code Purpose:
This code solves the problem of minimizing the balance (max - min) in a multiset after performing operations
to split elements into their factors. The key idea is to use a sieve-like approach to track the smallest
prime factor of each number and iteratively find the optimal way to reduce the balance.

Algorithms/Techniques:
- Sieve of smallest prime factors (SPF)
- Two-pointer approach for minimizing balance
- Dynamic tracking of min and max values during factorization

Time Complexity: O(m * sqrt(m) + n)
Space Complexity: O(m)

*/
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;
const int N = 5e6 + 10;
int T_T, n, m, ans, l, r, i, j, f[N], g[N], buc[N];
int main() {
  for (scanf("%d", &T_T); T_T--;) {
    // Initialize arrays for each test case
    for (scanf("%d%d", &n, &m), i = 1; i <= m; ++i)
      buc[i] = f[i] = 0, g[i] = i;
    
    // Find initial min and max values in the multiset
    for (l = 1e9, r = 0, i = 1; i <= n; ++i)
      scanf("%d", &j), l = min(l, j), r = max(r, j), f[j] = buc[j] = 1;
    
    // Initialize answer with initial balance
    ans = r - l;
    
    // Process from sqrt(m) down to 1 using sieve-like approach
    for (i = sqrt(m); i; --i) {
      // For each multiple of i, update the sieve
      for (j = i; j <= m; j += i) {
        // If j is present in multiset, decrease its count in bucket
        if (f[j])
          buc[g[j]]--;
        
        // Update the minimum prime factor of j
        if (g[j / i] >= i)
          g[j] = min(g[j], g[j / i]);
        
        // If j is present in multiset, increase its count in bucket
        if (f[j])
          buc[g[j]]++;
      }
      
      // Update right pointer to the largest value with non-zero count
      while (!buc[r])
        r--;
      
      // Update minimum balance considering current i as the minimum value
      ans = min(ans, r - min(l, i));
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/