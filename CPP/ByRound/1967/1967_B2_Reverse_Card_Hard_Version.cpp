// Problem: CF 1967 B2 - Reverse Card (Hard Version)
// https://codeforces.com/contest/1967/problem/B2

/*
Algorithm: Number Theoretic Approach with Optimization
Time Complexity: O(n^(3/2)) in worst case, but optimized to O(n^(3/2) * log(n)) due to gcd precomputation
Space Complexity: O(n^2) for the visited array

Approach:
1. For each pair (a, b), we need to check if b * gcd(a, b) is divisible by (a + b).
2. This condition can be rewritten as: (a + b) | (b * gcd(a, b)).
3. Let g = gcd(a, b). Then a = g * a', b = g * b' where gcd(a', b') = 1.
4. Substituting: (g * a' + g * b') | (g * b' * g) => g * (a' + b') | g^2 * b'
5. Simplifying: (a' + b') | g * b'
6. This gives us a condition to iterate over possible values efficiently by considering divisors and gcd.

Optimization:
- We precompute and mark all pairs (a, b) where gcd(a, b) > 1 using sieve-like approach.
- Then we iterate over all possible a' and b' (where gcd(a', b') = 1) and count valid pairs.

In this implementation:
- We use a visited array to mark pairs where gcd > 1.
- Then for valid pairs, we compute how many multiples satisfy the condition.
*/

#include <time.h>
#include <algorithm>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>
using namespace std;

int n, m;
bool vis[2005][2005];
void solve() {
  cin >> n >> m;
  for (int g = 2; g * g <= min(n, m); g++) {
    for (int a = g; a * a <= n; a += g) {
      for (int b = g; b * b <= m; b += g) {
        vis[a][b] = true;
      }
    }
  }
  int res = 0;
  for (int i = 1; i * i <= n; i++) {
    for (int j = 1; j * j <= m; j++) {
      if (vis[i][j])
        continue;
      res += min(n / i / (i + j), m / j / (i + j));
    }
  }
  cout << res << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int testcase = 1;
  cin >> testcase;
  while (testcase--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/