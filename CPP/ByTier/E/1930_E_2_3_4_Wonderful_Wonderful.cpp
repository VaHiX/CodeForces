// Problem: CF 1930 E - 2..3...4.... Wonderful! Wonderful!
// https://codeforces.com/contest/1930/problem/E

/*
Purpose:
This code computes, for each valid k from 1 to floor((n-1)/2), the number of distinct arrays that can be obtained by performing a specific operation on an initially ordered array a[1..n] where a[i] = i.

The operation involves selecting a subsequence of length 2*k+1 and deleting the first k and last k elements of it. The key is to determine how many unique sequences can result after repeated application of such operations.

Algorithms/Techniques:
- Modular arithmetic with precomputed factorials and inverse factorials for combination calculations
- Dynamic programming or inclusion-exclusion principles, indirectly via combinatorics
- Fast exponentiation for modular inverse computation
- Prefix sum or similar logic via direct loop iteration

Time Complexity:
O(n log n + T * n), where T is the number of test cases. Preprocessing factorial and inverse factorial tables takes O(n), and for each test case, we iterate over possible k values, leading to O(n) operations per case.
Space Complexity:
O(n) for storing factorials, inverse factorials, and answer array.
*/
#include <algorithm>
#include <cstdio>

using namespace std;
const int md = 998244353;
int n, m, k, l, t, nj[1000010], ny[1000010], ans[1000010];

// Fast modulo addition to handle negative results
inline int qmod(int x) { return x + (x >> 31 & md); }

// Compute combination C(x, y) using precomputed factorials and inverse factorials
inline int C(int x, int y) {
  if (x > y)
    return 0;
  return 1ll * nj[y] * ny[x] % md * ny[y - x] % md;
}

// Fast exponentiation for modular inverse
int ksm(int x, int y) {
  if (!y)
    return 1;
  int an4 = 1;
  for (int i = __lg(y); ~i; --i)
    an4 = 1ll * an4 * an4 % md * (y >> i & 1 ? x : 1) % md;
  return an4;
}

// Solve function for one test case
void solve() {
  scanf("%d", &n);
  for (int i = 1; i * 2 < n; ++i) {
    ans[i] = 0;
    // Loop from large j down to 1 to compute contribution of subsequences
    for (int j = n; j > 0; j -= 2 * i)
      ans[i] = qmod(ans[i] - qmod((j == n ? 0 : C(j, i * 2 + j - 1)) - C(j, n)));
  }
  for (int i = 1; i * 2 < n; ++i)
    printf("%d ", ans[i]);
  putchar('\n');
}

int main() {
  // Precompute factorials and inverse factorials
  nj[0] = 1;
  for (int i = 1; i <= 1000000; ++i)
    nj[i] = 1ll * i * nj[i - 1] % md;
  ny[1000000] = ksm(nj[1000000], md - 2);
  for (int i = 1000000; i; --i)
    ny[i - 1] = 1ll * i * ny[i] % md;

  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/