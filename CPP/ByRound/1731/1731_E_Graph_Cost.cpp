// Problem: CF 1731 E - Graph Cost
// https://codeforces.com/contest/1731/problem/E

/*
Algorithm: 
The problem involves constructing a graph with minimum cost using a specific operation where we can add k edges of weight (k+1) at a cost of (k+1). For each weight w, we need to count how many edges of that weight can be formed using gcd(u, v) = w.

Key Insight:
- For a given weight w, there are exactly phi(w) * (n/w)^2 edges of weight w in a complete graph with n vertices, where phi is Euler's totient function
- However, our approach computes this using inclusion-exclusion, counting all pairs of vertices that have gcd equal to a certain value.

Approach:
1. Use inclusion-exclusion principle to compute how many edges of gcd = i exist.
2. Process from largest to smallest weights, greedily taking as many edges as needed.
3. For each edge weight w, we can take k edges of cost (k + 1) in total, with k edges of weight w.

Time Complexity: O(n log n) 
Space Complexity: O(n)

*/
#include <stdio.h>
#include <iosfwd>

using namespace std;
#define int long long
int t, n, m;
int num[1000060];
void solve() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; i++)
    num[i] = 0;
  int ans = 0;
  for (int i = n; i >= 2; i--) {
    // Count how many edges have gcd = i using inclusion-exclusion
    num[i] = (n / i) * (n / i - 1) / 2;
    for (int j = 2; i * j <= n; j++)
      num[i] -= num[i * j];
    int k = i - 1;
    // Calculate number of complete packs of k edges we can take
    int add = (num[i] / k) * k;
    // If we don't need that many edges, we adjust
    if (add > m)
      add = (m / k) * k;
    m -= add, ans += (add / k) * i;
    if (m == 0)
      break;
  }
  if (m > 0)
    printf("-1\n");
  else
    printf("%lld\n", ans);
}
signed main() {
  scanf("%lld", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/