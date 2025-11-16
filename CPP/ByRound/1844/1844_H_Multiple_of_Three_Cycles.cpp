// Problem: CF 1844 H - Multiple of Three Cycles
// https://codeforces.com/contest/1844/problem/H

/*
Algorithm/Techniques:
- Union-Find (Disjoint Set Union) to manage cycles in the permutation
- Modular arithmetic with precomputed factorials and inverse factorials for combinatorial calculations
- Dynamic programming approach to compute the number of valid ways to complete the permutation

Time Complexity: O(n * α(n) + n * log(n)) where α is the inverse Ackermann function (nearly constant)
Space Complexity: O(n) for storing parent, size arrays, and auxiliary arrays

The problem involves maintaining a permutation and after each update, determining how many ways
we can fill the remaining entries such that all cycle lengths in the resulting permutation are multiples of 3.

We use Union-Find to track connected components and their sizes. For each component, we track how many
cycles have length 0, 1, or 2 modulo 3. When two components are merged, we update these counts.
We also precompute factorial and inverse factorial values to allow fast computation of combinations.
Finally, we use a dynamic programming or recurrence relation approach to compute the number of valid configurations.

The recurrence approach uses two variables u and v to track intermediate results based on the number
of cycles of certain sizes, and adjusts them with functions f and g depending on the number of cycles available.
*/

#include <assert.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long int LLI;
#define MOD 998244353
int parent[300000], siz[300000];
int find(int n) {
  if (parent[n] != n)
    parent[n] = find(parent[n]); // Path compression
  return parent[n];
}
int queries[600000][3], ans[600000];
int fact[300000], invfact[300000], invn[300000];
int inv(int n) {
  int e = MOD - 2, r = 1;
  while (e > 0) {
    if (e & 1)
      r = ((LLI)r * n) % MOD;
    e >>= 1;
    n = ((LLI)n * n) % MOD;
  }
  return r;
}
int main() {
  int i;
  int n, x, y, bad = 1e9;
  int num[3];
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    parent[i] = i, siz[i] = 1; // Initialize Union-Find structure
  num[0] = 0, num[1] = n, num[2] = 0;
  for (i = 0; i < n; i++) {
    scanf("%d %d", &x, &y);
    x--, y--;
    if (find(x) != find(y)) {
      // If x and y are in different components, merge them
      num[siz[find(x)] % 3]--;
      num[siz[find(y)] % 3]--;
      siz[find(y)] += siz[find(x)];
      parent[find(x)] = find(y);
      num[siz[find(y)] % 3]++;
    } else if ((siz[find(x)] % 3) == 0)
      // If merging creates a cycle of length divisible by 3, this is invalid
      num[0]--;
    else if (bad == 1e9)
      // First invalid update found
      bad = i;
    copy(num, num + 3, queries[i]); // Store state after the update
  }
  fact[0] = 1;
  for (i = 1; i < n; i++)
    fact[i] = ((LLI)i * fact[i - 1]) % MOD; // Precompute factorials
  invfact[n - 1] = inv(fact[n - 1]);
  for (i = n - 2; i >= 0; i--)
    invfact[i] = ((LLI)(i + 1) * invfact[i + 1]) % MOD; // Precompute inverse factorials
  for (i = 1; i < n; i++)
    invn[i] = ((LLI)invfact[i] * fact[i - 1]) % MOD; // Precompute invn[i] = fact[i-1]/fact[i]

  int m = n;
  while (num[1] + num[2] > 0) {
    // Process remaining cycles to reach a state where only multiples of 3 are valid
    int a = (num[1] > 0) ? 1 : 2;
    num[a]--;
    int b = (num[1] > 0) ? 1 : 2;
    num[b]--;
    num[(a + b) % 3]++;
    copy(num, num + 3, queries[m++]);
  }
  x = 1, y = 1;
  int u = 1, v = 8; // Initialize recurrence variables
  auto f = [&]() {
    assert(x > 0);
    int nu =
        (((v - (((LLI)(y + 1) * (x + y + 1)) % MOD) * u) % MOD) * invn[x]) %
        MOD;
    int nv = ((((LLI)x * (x + y + 2)) % MOD) * nu + (LLI)(y + 2) * v) % MOD;
    x--, y += 2, u = nu, v = nv; // Update variables using recurrence
    if (u < 0)
      u += MOD;
    if (v < 0)
      v += MOD;
  };
  auto g = [&]() {
    assert(y > 0);
    int nu =
        (((v - (((LLI)(x + 1) * (x + y + 1)) % MOD) * u) % MOD) * invn[y]) %
        MOD;
    int nv = ((((LLI)y * (x + y + 2)) % MOD) * nu + (LLI)(x + 2) * v) % MOD;
    x += 2, y--, u = nu, v = nv; // Update variables using recurrence
    if (u < 0)
      u += MOD;
    if (v < 0)
      v += MOD;
  };
  for (i = m - 1; i >= 0; i--) {
    int a = queries[i][1], b = queries[i][2], c = queries[i][0];
    // Based on current values of a,b,c determine correct recurrence parameters
    if ((a == 0) && (b == 0))
      ans[i] = 1;
    else if ((a == x) && (b == y))
      ans[i] = u;
    else if ((a == x - 1) && (b == y + 2))
      f(), ans[i] = u;
    else if ((a == x + 2) && (b == y - 1))
      g(), ans[i] = u;
    else if ((a == x + 1) && (b == y + 1)) {
      if (x > 0)
        f(), g(), ans[i] = u;
      else
        g(), f(), ans[i] = u;
    } else
      assert(0); // If none of the above matches, input is inconsistent

    // Finish computing final answer using combinatorics
    ans[i] = ((LLI)ans[i] * fact[a + b + c]) % MOD;
    ans[i] = ((LLI)ans[i] * invfact[a + b]) % MOD;
  }
  for (i = 0; i < n; i++)
    printf("%d\n", (i >= bad) ? 0 : ans[i]); // Output results or 0 if invalid update occurred
  return 0;
}


// https://github.com/VaHiX/CodeForces/