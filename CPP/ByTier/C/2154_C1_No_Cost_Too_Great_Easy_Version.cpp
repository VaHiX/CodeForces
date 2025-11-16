// Problem: CF 2154 C1 - No Cost Too Great (Easy Version)
// https://codeforces.com/contest/2154/problem/C1

/*
 * Problem: C1. No Cost Too Great (Easy Version)
 * Purpose: Find the minimum cost to make the GCD of some pair of elements in array 'a' greater than 1.
 * Algorithm: 
 *   - Precompute smallest prime factor (SPF) for numbers up to 2*10^5 using Sieve of Eratosthenes.
 *   - For each element in 'a', find its unique prime factors.
 *   - Check if any two elements share a common prime factor; if so, cost is 0.
 *   - Otherwise, try to increase one element by 1 and check if it shares a prime factor with any other element.
 *   - If yes, cost is 1; otherwise, cost is 2.
 * Time Complexity: O(n * log(max(a))) due to prime factorization and sieve preprocessing.
 * Space Complexity: O(LIM + n) for SPF array and temporary vectors.
 */

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int LIM = 200001 + 5;
static int spf[LIM]; // Smallest Prime Factor array

// Build SPF array using sieve of Eratosthenes
void build_spf() {
  for (int i = 2; i < LIM; ++i)
    if (!spf[i]) {
      spf[i] = i;
      if (1LL * i * i < LIM)
        for (long long j = 1LL * i * i; j < LIM; j += i)
          if (!spf[j])
            spf[j] = i;
    }
  spf[1] = 1;
}

// Get unique prime factors of x and store them in out
inline void unique_primes(int x, vector<int> &out) {
  out.clear();
  while (x > 1) {
    int p = spf[x];
    out.push_back(p);
    while (x % p == 0)
      x /= p;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  build_spf();
  static int seen_ai[LIM]; // Mark which primes were seen in current test case
  int cur_id = 1; // ID to track when primes were last seen
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    for (int i = 0, x; i < n; ++i)
      cin >> x;
    bool ans0 = false, ans1 = false;
    vector<int> fac;
    for (int i = 0; i < n; ++i) {
      unique_primes(a[i], fac);
      for (int p : fac) {
        if (seen_ai[p] == cur_id) {
          ans0 = true;
          break;
        }
        seen_ai[p] = cur_id;
      }
      if (ans0)
        break;
    }
    // If we found two elements sharing a prime factor, cost = 0
    if (ans0) {
      cout << 0 << '\n';
      ++cur_id;
      continue;
    }
    // Try increasing one element by 1 and look for shared prime
    for (int i = 0; i < n && !ans1; ++i) {
      unique_primes(a[i] + 1, fac);
      for (int p : fac)
        if (seen_ai[p] == cur_id) {
          ans1 = true;
          break;
        }
    }
    // If such element found, cost = 1, else cost = 2
    cout << (ans1 ? 1 : 2) << '\n';
    ++cur_id;
    // Reset seen_ai if necessary to avoid overflow
    if (cur_id == INT_MAX) {
      memset(seen_ai, 0, sizeof(seen_ai));
      cur_id = 1;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/