// Problem: CF 2131 H - Sea, You & copriMe
// https://codeforces.com/contest/2131/problem/H

/*
 * Problem: H. Sea, You & copriMe
 * Purpose: Find four distinct indices p, q, r, s such that gcd(a[p], a[q]) == 1 and gcd(a[r], a[s]) == 1.
 * Algorithm:
 * - Sieve of Euler to precompute smallest prime factor (minp) for all numbers up to m.
 * - For each number, compute its divisors using minp.
 * - Count occurrences of each number in array a.
 * - Use inclusion-exclusion principle to count how many elements in the array are divisible by a given number.
 * - Compute degree of each node (number of other elements it's coprime with).
 * - Try to find a valid 4-tuple based on degrees and GCD conditions.
 *
 * Time Complexity: O(m log log m + n * d(a[i]) + n^2), where d(x) is number of divisors of x
 * Space Complexity: O(m + n)
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
const int MAXN = 1000 << 10;
vector<int> primes, minp;
int cnt[MAXN];

void sieve() {
  minp.assign(MAXN, 0);
  for (int i = 2; i < MAXN; i++) {
    if (!minp[i]) { // If i is a prime number
      minp[i] = i;
      primes.push_back(i);
    }
    for (int p : primes) { // Iterate through all smaller primes
      if (p > minp[i] || 1LL * i * p >= MAXN)
        break;
      minp[i * p] = p; // Mark smallest prime factor of i*p
    }
  }
}

vector<int> getDivisors(int x) {
  vector<int> res = {1};
  while (x > 1) {
    int p = minp[x]; // Get smallest prime factor of x
    int sz = res.size();
    for (int i = 0; i < sz; i++)
      res.push_back(res[i] * p); // Multiply all existing divisors by p
    while (x % p == 0)
      x /= p; // Remove p from x
  }
  return res;
}

void solve() {
  int n, u;
  cin >> n >> u;
  fill(cnt, cnt + u + 1, 0);
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
    cnt[x]++; // Count occurrences of each element
  }

  // For each prime p, propagate count to all multiples of p
  for (int p : primes) {
    if (p > u)
      break;
    for (int i = u / p; i >= 1; i--)
      cnt[i] += cnt[i * p];
  }

  vector<int> deg(n, 0); // Degree of each vertex (how many elements it's coprime with)
  for (int i = 0; i < n; i++) {
    if (a[i] == 1) {
      deg[i] = n - 1; // All other elements are coprime to 1
      continue;
    }
    auto divs = getDivisors(a[i]); // Get all divisors of a[i]
    int c = 0;
    for (int idx = 0; idx < (int)divs.size(); idx++) {
      if (__builtin_popcount(idx) & 1)
        c -= cnt[divs[idx]]; // Use inclusion-exclusion: subtract terms with odd number of primes
      else
        c += cnt[divs[idx]]; // Add terms with even number of primes
    }
    deg[i] = c;
  }

  ll sumDeg = accumulate(deg.begin(), deg.end(), 0LL); // Total degree
  int mx = *max_element(deg.begin(), deg.end());
  if (sumDeg < 4 || mx * 2 == sumDeg) { // Check invalid configurations
    cout << 0 << endl;
    return;
  }
  int x = 0, y = 0;
  for (int i = 0; i < n && !x; i++)
    if (deg[i]) {
      for (int j = 0; j < n; j++)
        if (j != i) {
          if (gcd(a[i], a[j]) == 1 && (deg[i] + deg[j] - 1) * 2 != sumDeg) { // Valid pair with good degree
            x = i + 1;
            y = j + 1;
            break;
          }
        }
    }

  if (!x) {
    cout << 0 << endl;
    return;
  }

  for (int i = 0; i < n; i++)
    if (i != x - 1 && i != y - 1) {
      int c = deg[i];
      c -= (gcd(a[x - 1], a[i]) == 1);
      c -= (gcd(a[y - 1], a[i]) == 1); // Reduce degree as those pairs are used
      if (!c)
        continue;
      for (int j = 0; j < n; j++)
        if (j != x - 1 && j != y - 1 && j != i && gcd(a[i], a[j]) == 1) {
          cout << x << " " << y << " " << i + 1 << " " << j + 1 << endl;
          return;
        }
    }

  cout << 0 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve();
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/