// Problem: CF 2150 B - Grid Counting
// https://codeforces.com/contest/2150/problem/B

/**
 * Problem: B. Grid Counting
 * 
 * Description:
 * Alice has an n×n grid where she wants to color some cells black such that:
 * - For each row k, exactly a[k] cells are black.
 * - For each k, there's exactly one black cell (x_i, y_i) such that max(x_i, y_i) = k.
 * - For each k, there's exactly one black cell (x_i, y_i) such that max(x_i, n+1-y_i) = k.
 * 
 * Algorithm:
 * The solution uses combinatorics and precomputed factorials to count valid configurations.
 * 
 * Time Complexity: O(n) per test case (precomputation is amortized over all test cases)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <iosfwd>

#define N 200005
#define mod 998244353
using namespace std;
int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1)
      res = 1ll * res * x % mod; // Fast exponentiation to compute modular inverse
    x = 1ll * x * x % mod;
    y = y / 2;
  }
  return res;
}
int n, a[N];
int fac[N], ifac[N]; // Precomputed factorials and inverse factorials

void solve() {
  scanf("%d", &n);
  long long sum = 0;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), sum += a[i];
  
  if (sum != n) { // Check if total number of black cells equals n
    puts("0");
    return;
  }

  int ans = 1, cnt = 0;
  
  // Process the first half of rows to ensure valid configuration
  for (int i = 1; i <= n / 2; i++) {
    cnt += a[i]; // Accumulate count of black cells in first half rows
    
    if (cnt < 2) { // Need at least two black cells to connect with others
      puts("0");
      return;
    }
    
    // Multiply by the number of ways to choose 2 cells from current count,
    // and then multiply by (cnt - 1) for the remaining arrangements.
    ans = 1ll * ans * cnt % mod * (cnt - 1) % mod;
    cnt -= 2; // Reduce count after two connected nodes
  }
  
  // If n is odd and last midpoint row is empty, impossible to build valid structure
  if ((n & 1) && cnt == 0 && a[(n + 1) / 2] == 0) {
    puts("0");
    return;
  }

  // Divide by factorial of count of black cells in each row for multinomial coefficient
  for (int i = 1; i <= n; i++)
    ans = 1ll * ans * ifac[a[i]] % mod;

  printf("%d\n", ans);
}

int main() {
  n = 2e5;
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = 1ll * fac[i - 1] * i % mod; // Precompute factorials
  
  ifac[n] = power(fac[n], mod - 2);
  for (int i = n; i >= 1; i--)
    ifac[i - 1] = 1ll * ifac[i] * i % mod; // Precompute inverse factorials

  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/