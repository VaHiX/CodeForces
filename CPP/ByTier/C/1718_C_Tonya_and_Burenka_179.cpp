// Problem: CF 1718 C - Tonya and Burenka-179
// https://codeforces.com/contest/1718/problem/C

/*
Code Purpose:
This program solves the problem of finding the maximum "usefulness" of a robotic program "Burenka-179" that traverses a cyclic array.
The key idea is to precompute the best movement patterns by exploiting the periodic nature of the traversal for divisors of n,
and then answer queries about changes to the array efficiently.

Algorithms/Techniques:
- Preprocessing using divisors of n to compute sums for cyclic steps
- Efficient update of sums when elements change
- Using multiset to track current maximum usefulness

Time Complexity: O(n * sqrt(n) + q * sqrt(n) * log(sqrt(n)))
Space Complexity: O(n * sqrt(n))
*/

#include <cstdio>
#include <set>
#include <iterator>

using namespace std;
const int o = 2e5 + 10;
int T, n, q, a[o], st[o], tp, bl[o][10];
long long sm[10][o];
bool vis[o];
multiset<long long> s;

int main() {
  for (scanf("%d", &T); T--; tp = 0, s.clear()) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    // Sieve-like process to mark composite numbers
    for (int i = 2; i <= n; ++i)
      for (int j = 2 * i; j <= n; j += i)
        vis[j] = 1;
    
    // For each prime divisor of n
    for (int i = 2; i <= n; ++i)
      if (!vis[i] && n % i == 0) {
        st[++tp] = i; // Store prime divisor
        // Initialize sum array for this divisor
        for (int j = 0; j < n / i; ++j)
          sm[tp][j] = 0;
        // Compute sum for each group
        for (int j = 1; j <= n; ++j)
          sm[tp][bl[j][tp] = j % (n / i)] += a[j];
        // Add all possible sums to multiset
        for (int j = 0; j < n / i; ++j)
          s.insert(sm[tp][j] * (n / i));
      }
    
    // Print initial maximum usefulness
    printf("%lld\n", *s.rbegin());
    
    // Process queries
    for (int p, x; q--; printf("%lld\n", *s.rbegin())) {
      scanf("%d%d", &p, &x);
      // Update all relevant sums when element at p changes
      for (int i = 1; i <= tp; ++i)
        s.erase(s.find(sm[i][bl[p][i]] * (n / st[i]))),  // Remove old contribution
            s.insert((sm[i][bl[p][i]] += x - a[p]) * (n / st[i]));  // Add new contribution
      a[p] = x; // Update array
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/