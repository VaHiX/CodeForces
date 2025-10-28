// Problem: CF 2063 F2 - Counting Is Not Fun (Hard Version)
// https://codeforces.com/contest/2063/problem/F2

/*
F2. Counting Is Not Fun (Hard Version)
Algorithms/Techniques: Union-Find, Catalan Numbers, Modular Arithmetic
Time Complexity: O(n log n + n^2) amortized per test case
Space Complexity: O(n)

This problem involves counting the number of valid balanced bracket sequences
that satisfy a given set of good pair constraints. We use Union-Find to manage
connected components and precomputed Catalan numbers to count valid sequences.

We preprocess:
- Factorials and their modular inverses
- Catalan numbers and inverse Catalan numbers

For each query, we process the clues in reverse order (from last to first), keeping track
of which brackets are connected and using Union-Find operations to merge components.
The answer at any step is multiplied by the appropriate Catalan number factor based on component sizes.
*/
#include <algorithm>
#include <initializer_list>
#include <stdio.h>
using namespace std;
#define MOD 998244353
int t, n, x[300005], y[300005], par[600005], si[600005];
long long fac[600005], inv[600005], cat[300005], icat[300005], ans[300005];

// Fast exponentiation for modular arithmetic
long long po(long long b, int p) {
  long long re = 1;
  while (p) {
    if (p % 2)
      re = re * b % MOD;
    b = b * b % MOD;
    p /= 2;
  }
  return re;
}

// Find root with path compression
int find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

int main() {
  // Precompute factorials
  fac[0] = 1;
  for (int i = 1; i < 600005; i++)
    fac[i] = fac[i - 1] * i % MOD;

  // Precompute modular inverses of factorials
  inv[600004] = po(fac[600004], MOD - 2);
  for (int i = 600003; i >= 0; i--)
    inv[i] = inv[i + 1] * (i + 1) % MOD;

  // Precompute Catalan numbers and inverse Catalan numbers
  for (int i = 0; i < 300002; i++) {
    cat[i] = fac[i * 2] * inv[i + 1] % MOD * inv[i] % MOD;
    icat[i] = inv[i * 2] * fac[i + 1] % MOD * fac[i] % MOD;
  }

  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    fill(si, si + n * 2 + 1, 0); // Initialize size array
    for (int i = 0; i <= n * 2; i++)
      par[i] = i; // Each node is initially its own parent
    for (int i = 0; i < n; i++) {
      scanf("%d%d", x + i, y + i);
      int ta = find(x[i] - 1); // Find root of left component
      int tb = find(y[i]);     // Find root of right component
      if (ta != tb)
        par[ta] = tb; // Union the components
    }

    ans[n] = 1; // Base case: no clues given, total configurations is 1
    for (int i = n - 1; i >= 0; i--) {
      ans[i] = ans[i + 1]; // Start with previous value

      int tmp = find(x[i]); // Find the root of x[i]
      ans[i] = ans[i] * icat[si[tmp]] % MOD; // Remove contribution of old size
      si[tmp]++; // Increment size
      ans[i] = ans[i] * cat[si[tmp]] % MOD; // Add contribution of new size

      // Process the two brackets involved in this clue
      for (int j : {x[i], y[i]}) {
        int ta = find(j - 1);   // Left bracket root
        int tb = find(j);       // Right bracket root
        if (ta == tb)           // Skip if already connected to the same component
          continue;
        par[tb] = ta;           // Union them
        ans[i] = ans[i] * icat[si[ta]] % MOD * icat[si[tb]] % MOD; // Remove contribution
        si[ta] += si[tb];       // Merge size
        ans[i] = ans[i] * cat[si[ta]] % MOD; // Add contribution of merged size
      }
    }
    for (int i = 0; i <= n; i++)
      printf("%lld%c", ans[i], " \n"[i == n]);
  }
}


// https://github.com/VaHiX/codeForces/