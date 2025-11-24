// Problem: CF 2171 D - Rae Taylor and Trees (easy version)
// https://codeforces.com/contest/2171/problem/D

/*
Algorithm: 
The solution checks if a tree can be constructed such that for every edge (u, v), u appears before v in the permutation p.
This is true if and only if for each position i in the permutation, all elements to the right (after i) are greater than or equal to the minimum element seen so far from the beginning up to position i.
This condition is checked using prefix minimums and suffix maximums.

Time Complexity: O(n) per test case, as we do three passes through the array (prefix min, suffix max, and final check).
Space Complexity: O(n) for storing the arrays pre and suf.

Techniques used:
- Prefix minimum calculation
- Suffix maximum calculation
- Greedy validation based on comparisons between prefix and suffix arrays
*/

#include <stdio.h>
#include <algorithm>

#define int long long
using namespace std;
int pre[200005], suf[200005], t, n, a[200005];

void solve() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld", a + i), pre[i] = suf[i] = a[i];
  
  // Precompute prefix minimums: pre[i] = min(a[1], a[2], ..., a[i])
  for (int i = 2; i <= n; i++)
    pre[i] = min(pre[i], pre[i - 1]);
  
  // Precompute suffix maximums: suf[i] = max(a[i], a[i+1], ..., a[n])
  for (int i = n - 1; i >= 1; i--)
    suf[i] = max(suf[i], suf[i + 1]);
  
  // For each position i, check if the minimum value before i is less than or equal to 
  // the maximum value after i. If not, it's impossible to construct such a tree.
  for (int i = 1; i < n; i++)
    if (suf[i + 1] < pre[i]) {
      puts("No");
      return;
    }
  puts("Yes");
  return;
}

signed main() {
  scanf("%lld", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/