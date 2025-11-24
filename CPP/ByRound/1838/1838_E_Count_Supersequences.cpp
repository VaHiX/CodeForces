// Problem: CF 1838 E - Count Supersequences
// https://codeforces.com/contest/1838/problem/E

/*
 * Problem: Count Supersequences
 * 
 * Purpose: Given an array 'a' of size n and a target array 'b' of size m, 
 *          where all elements are in range [1, k], count how many arrays 'b' 
 *          exist such that 'a' is a subsequence of 'b'. 
 * 
 * Algorithm: 
 *   - Use inclusion-exclusion principle.
 *   - First compute total number of valid arrays of length m: k^m.
 *   - Then subtract the number of arrays where 'a' is NOT a subsequence.
 *   - For each position in 'a', calculate how many ways we can place it 
 *     such that it appears as a subsequence, and apply inclusion-exclusion 
 *     with derangements.
 * 
 * Time Complexity: O(N + M + log(M) + log(k)) per test case, 
 *                  or approximately O(N) for all cases combined due to 
 *                  preprocessing of inverse modulars.
 * Space Complexity: O(N) for storing inverse modulars and input arrays.
 */

#include <cstdio>
#include <iostream>

#define A puts("Yes")
#define B puts("No")
#define fo(i, a, b) for (int(i) = (a); (i) <= (b); (i)++)
#define fd(i, b, a) for (int(i) = (b); (i) >= (a); (i)--)
#define mk(x, y) make_pair((x), (y))
#define lc (o << 1)
#define rc (o << 1 | 1)
using namespace std;
typedef long long ll;
typedef double db;
const ll mo = 1e9 + 7;
const ll inf = 1ll << 30;
const int N = 2e5 + 5;
ll n, a[N], inv[N], m, k, ans, t, z;

// Fast exponentiation to compute a^b mod mo
ll power(ll a, ll b) {
  ll t = 1, y = a % mo;
  while (b) {
    if (b & 1)
      t = t * y % mo;
    y = y * y % mo;
    b /= 2;
  }
  return t;
}

void solve() {
  scanf("%lld %lld %lld", &n, &m, &k);
  fo(i, 1, n) scanf("%lld", &a[i]);
  
  // Precompute inverse of (k-1) modulo mo
  z = power(k - 1, mo - 2);
  
  // Initial value: number of ways to place array 'a' in 'b' such that no element 
  // of 'a' matches exactly at its position (i.e., derangements of 'a').
  // This is initialized to (k-1)^m
  ans = t = power(k - 1, m);
  
  // Apply inclusion-exclusion principle step by step,
  // calculating the number of cases where subsequence is missing
  fo(i, 1, n - 1) {
    // Multiply by binomial coefficient C(m, i) and adjust for derangements
    t = t * (m - i + 1ll) % mo * inv[i] % mo * z % mo;
    ans = (ans + t) % mo;
  }
  
  // Use inclusion-exclusion to get final result:
  // Total = k^m - [bad arrangements where 'a' is not subsequence]
  ans = power(k, m) - ans;
  ans = (ans % mo + mo) % mo;
  printf("%lld\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  
  // Precompute modular inverses using the formula inv[i] = -(mo/i) * inv[mo%i] mod mo
  inv[1] = 1;
  fo(i, 2, N - 1) {
    inv[i] = -(mo / i) * inv[mo % i] % mo;
    inv[i] = (inv[i] % mo + mo) % mo;
  }
  
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/