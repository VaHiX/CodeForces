// Problem: CF 2171 G - Sakura Adachi and Optimal Sequences
// https://codeforces.com/contest/2171/problem/G

/*
 * Problem: Sakura Adachi and Optimal Sequences
 * 
 * Purpose: 
 *   Given two arrays 'a' and 'b' of length n where a[i] <= b[i], 
 *   compute the minimum number of operations to transform array 'a' to array 'b'.
 *   The operations are:
 *     1. Increment any element of 'a' by 1.
 *     2. Double all elements of 'a'.
 *   
 *   Additionally, count how many sequences of exactly 'x' operations can achieve this transformation.
 * 
 * Algorithms/Techniques:
 *   - Greedy approach combined with combinatorics:
 *     - First, we reduce 'b' by halving all elements while possible (to minimize operations),
 *       counting how many 1-increments are needed at each step.
 *     - Then, we process the remaining difference between 'a' and 'b' using combinatorics.
 *   - Modular arithmetic with precomputed factorials for efficient combination calculations.
 * 
 * Time Complexity:
 *   O(n + max(b_i)) for processing each element, and O(1) per test case for factorial precomputation.
 *   Overall: O(n + max_b * t) where t is number of test cases.
 *   
 * Space Complexity:
 *   O(max_b) for storing precomputed factorials (jc array).
 * 
 */


#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define ull unsigned long long
#define PII pair<int, int>
#define PLL pair<ll, ll>
const ll mod = 1e6 + 3;
vector<ll> jc(1e6 + 4); // Precomputed factorials modulo (1e6 + 3)

// Initialize factorials up to 1e6 + 3
void init() {
  jc[0] = 1;
  for (ll i = 1; i <= 1e6 + 3; i++)
    jc[i] = jc[i - 1] * i % mod;
}

// Fast exponentiation: a^b mod p
long long qpow(long long a, long long b, long long p) {
  if (b == 0)
    return 1;
  long long res = qpow(a, b / 2, p);
  if (b % 2)
    return res * res % p * a % p;
  else
    return res * res % p;
}

// Solves one test case
void solve() {
  int n;
  cin >> n;
  vector<ll> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  
  ll x = 0, cnt = 1; // x: minimal operations, cnt: number of ways
  vector<ll> nextb(n);

  // Reduce 'b' using doubles when possible, and count 1-adds needed
  while (true) {
    bool f = 1;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
      nextb[i] = b[i] >> 1; // Integer division by 2
      if (b[i] % 2)
        cur++; // Odd bits need 1-add
      if (nextb[i] < a[i])
        f = 0; // Can't halve if it becomes less than 'a[i]'
    }
    if (f) {
      for (int i = 0; i < n; i++)
        b[i] = nextb[i];
      x++; // One operation for halving (count as 1)
      x += cur; // Add 1-increments needed at this step
      cnt = cnt * jc[cur] % mod; // Combinations for arrangement of 1-increments
    } else
      break; // Cannot halve further
  }

  // Add up remaining 1-adds needed
  ll csum = 0;
  for (int i = 0; i < n; i++) {
    csum += b[i] - a[i];
  }
  x += csum;

  // Use multinomial coefficients for counting sequences
  for (int i = 0; i < n; i++) {
    ll diff = b[i] - a[i];
    cnt = cnt * jc[min(csum, (ll)1e6 + 3)] % mod *
          qpow(jc[min(csum - diff, (ll)1e6 + 3)], mod - 2, mod) % mod *
          qpow(jc[diff], mod - 2, mod) % mod;
    csum -= diff;
  }
  cout << x << ' ' << cnt << endl;
}

int main() {
  init(); // Precompute factorials
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/