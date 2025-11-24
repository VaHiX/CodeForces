// Problem: CF 2153 E - Zero Trailing Factorial
// https://codeforces.com/contest/2153/problem/E

/*
E. Zero Trailing Factorial
Purpose:
This code computes the sum of f_m(x, n) over all x in [1, n-1], where f_m(a, b) is defined as 
the minimum weight w_k(a, b) across all k in [2, m]. The weight w_k(a, b) is defined as:
- min(v_k(a!), v_k(b!)) if v_k(a!) != v_k(b!)
- 10^100 otherwise

Algorithms/Techniques:
- Sieve of Eratosthenes to compute smallest prime factors (spf)
- Prime factorization using spf
- For each query, process all numbers from P+1 to n,
  where P is the largest prime <= n
- For each number, compute its prime factorization and update a delta map
- For each x in [P, n-1], calculate best value using vpfact and flogp functions
- Efficiently remove prime factors of x+1 from delta

Time Complexity: O(N log log N + T * N * sqrt(N))
Space Complexity: O(N + T)

*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;
static inline long long vpfact(int x, int p) {
  // Computes the exponent of prime p in x!
  long long v = 0;
  while (x) {
    x /= p;
    v += x;
  }
  return v;
}
static inline int flogp(int m, int p) {
  // Calculates the largest e such that p^e <= m
  int e = 0;
  while (m >= p) {
    m /= p;
    ++e;
  }
  return e;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  if (!(cin >> t))
    return 0;
  vector<pair<int, int>> qs(t);
  int maxM = 0;
  for (int i = 0; i < t; ++i) {
    cin >> qs[i].first >> qs[i].second;
    maxM = max(maxM, qs[i].second);
  }
  int N = maxM;
  vector<int> spf(N + 1, 0), primes;
  spf[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (spf[i] == 0) {
      spf[i] = i;
      primes.push_back(i);
    }
    for (int p : primes) {
      long long v = 1LL * i * p;
      if (v > N || p > spf[i])
        break;
      spf[(int)v] = p;
    }
  }
  auto isPrime = [&](int x) { return x >= 2 && spf[x] == x; };
  auto prevPrime = [&](int x) {
    while (x >= 2 && !isPrime(x))
      --x;
    return x;
  };
  auto factor = [&](int y, vector<pair<int, int>> &out) {
    out.clear();
    while (y > 1) {
      int p = spf[y], c = 0;
      while (y % p == 0) {
        y /= p;
        ++c;
      }
      out.push_back({p, c});
    }
  };
  for (auto [n, m] : qs) {
    int P = prevPrime(n);
    if (P == n) {
      cout << 0 << '\n';
      continue;
    }
    unordered_map<int, int> delta;
    delta.reserve(1024);
    vector<pair<int, int>> tmp;
    for (int y = P + 1; y <= n; ++y) {
      factor(y, tmp);
      for (auto [p, c] : tmp)
        delta[p] += c;
    }
    vector<int> keys;
    keys.reserve(delta.size());
    for (auto &kv : delta)
      if (kv.second > 0)
        keys.push_back(kv.first);
    unordered_map<int, int> rc;
    rc.reserve(keys.size());
    unsigned long long ans = 0;
    for (int x = P; x < n; ++x) {
      unsigned long long best = (unsigned long long)(-1);
      for (int p : keys) {
        auto itc = delta.find(p);
        if (itc == delta.end() || itc->second <= 0)
          continue;
        int D = itc->second;
        int r;
        auto itr = rc.find(p);
        if (itr == rc.end()) {
          r = flogp(m, p);
          rc[p] = r;
        } else
          r = itr->second;
        long long A = vpfact(x, p);
        if (r >= A + 1) {
          best = 0;
          break;
        }
        int emax = (int)min<long long>(r, A);
        for (int e = emax; e >= 1; --e) {
          if ((A % e) + D >= e) {
            unsigned long long cand = (unsigned long long)(A / e);
            if (cand < best)
              best = cand;
            break;
          }
        }
      }
      if (best == (unsigned long long)(-1))
        best = 0;
      ans += best;
      int y = x + 1;
      factor(y, tmp);
      for (auto [p, c] : tmp) {
        auto it = delta.find(p);
        if (it != delta.end())
          it->second -= c;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/