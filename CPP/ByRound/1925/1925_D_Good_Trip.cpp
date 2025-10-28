// Problem: CF 1925 D - Good Trip
// https://codeforces.com/contest/1925/problem/D

/*
Purpose:
This code computes the expected sum of friendship values over k excursions, where each excursion randomly selects a pair of children, and if they are friends, their friendship value increases by 1 for all future excursions.

Algorithms/Techniques:
- Modular arithmetic for large numbers
- Fermat's little theorem for modular inverse
- Mathematical expectation calculation using linearity of expectation
- Precomputing base values to avoid redundant calculations

Time Complexity: O(m + k)
Space Complexity: O(m)

Where:
- m is the number of friend pairs
- k is the number of excursions
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int mod = 1e9 + 7;
int a[200005];
int b[200005];
int f[200005];
char buf[100005];
int vis[200];
long long quick_mod(long long a, long long b) {
  long long ans = 1;
  a %= mod;
  while (b) {
    if (b & 1) {
      ans = ans * a % mod;
      b--;
    }
    b >>= 1;
    a = a * a % mod;
  }
  return ans;
}
int sovle() {
  int i, j, l;
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  long long sum = 0;
  for (i = 1; i <= m; i++) {
    scanf("%d%d%d", &a[i], &b[i], &f[i]);
    sum += f[i];
  }
  long long ans = 0;
  // Compute modular inverse of total possible pairs (n*(n-1)/2)
  long long inv = quick_mod((long long)n * (n - 1) / 2 % mod, mod - 2);
  long long d = m * inv % mod; // Contribution per excursion for friend pairs
  long long base = sum % mod;  // Initial total sum of friendship values
  for (i = 1; i <= k; i++) {
    ans += base * inv % mod; // Add expected value for current excursion
    base += d;               // Increment base for next iteration
    base %= mod;
  }
  printf("%d\n", (int)(ans % mod));
  return 0;
}
int main() {
  int t = 1;
  scanf("%d", &t);
  while (t--) {
    sovle();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/