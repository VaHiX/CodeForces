// Problem: CF 1822 G2 - Magic Triples (Hard Version)
// https://codeforces.com/contest/1822/problem/G2

/*
Algorithm: Magic Triples Counting
Approach:
1. For each unique element, determine how many times it appears (frequency).
2. For each element `a[i]`, we look for magic triples (i,j,k) such that:
   - a[i] * b = a[j] and a[j] * b = a[k] (i.e., a[i] < a[j] < a[k] and a[j]/a[i] = a[k]/a[j])
   - Thus a[j] = a[i] * b and a[k] = a[i] * b^2 for some integer b > 1.
3. We try all possible values of b (as divisors of a[i]) and count pairs that form valid sequences.
4. To optimize: precompute small primes using sieve, then for each element factorize it and use combinations of divisors.

Time Complexity: O(n log n + n sqrt(max_a) * log(max_a))
Space Complexity: O(n + sqrt(max_a))

This version supports a[i] up to 1e9 by:
- Using prime factorization for potential b values,
- Efficiently counting combinations using frequencies of elements.
*/

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
vi primes;
vector<bool> is_prime;

// Sieve of Eratosthenes to generate primes up to 1000
void init_primes(int n) {
  is_prime.resize(n + 1, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (int prime : primes) {
      if (prime > n / i) {
        break;
      }
      is_prime[prime * i] = false;
      if (i % prime == 0) {
        break;
      }
    }
  }
}

// Initialize primes table once
void init() { init_primes(1e3); }

void solve() {
  int n = 0;
  cin >> n;
  vi a(n);
  for (int i = 0; i != n; ++i) {
    cin >> a[i];
  }

  // Sort input array to merge duplicates efficiently
  sort(a.begin(), a.end());

  // Create frequency array of unique elements
  vi a_ct;  // unique elements
  vi ct;    // their counts
  for (int i = 0; i != n; ++i) {
    if (i == 0 || a[i] != a[i - 1]) {
      a_ct.push_back(a[i]);
      ct.push_back(1);
    } else {
      ++ct.back();
    }
  }

  // Helper lambda to get count of an element
  function<int(int)> get_ct = [&](int num) {
    int i = lower_bound(a_ct.begin(), a_ct.end(), num) - a_ct.begin();
    if (i != a_ct.size() && a_ct[i] == num) {
      return ct[i];
    } else {
      return 0;
    }
  };

  ll res = 0;
  for (int i = 0; i != a_ct.size(); ++i) {
    int num = a_ct[i];
    // Case where we take 3 identical elements for triple (i,i,i)
    // No valid b exists if num == 1, skip
    res += (ll)ct[i] * (ct[i] - 1) * (ct[i] - 2);
    if (num == 1) {
      continue;
    }

    // Compute all valid divisor squares (b^2 in a[i]*b^2 = a[k])
    vi factors;
    for (int p : primes) {
      int mul = 0;
      while (num % p == 0) {
        ++mul;
        num /= p;
      }
      if (mul >= 2) {
        int prev_size = factors.size();
        int mult = 1;
        for (int m = 0; m != mul / 2; ++m) {
          mult *= p;
          factors.push_back(mult);
          for (int j = 0; j != prev_size; ++j) {
            factors.push_back(factors[j] * mult);
          }
        }
      }
    }

    // Handle case when num > 1 is a perfect square
    if (num > 1) {
      int num_sqrt = sqrt(num);
      if ((num_sqrt + 1) * (num_sqrt + 1) == num) {
        ++num_sqrt;
      }
      if (num_sqrt * num_sqrt == num) {
        int prev_size = factors.size();
        factors.push_back(num_sqrt);
        for (int j = 0; j != prev_size; ++j) {
          factors.push_back(factors[j] * num_sqrt);
        }
      }
    }

    // For each valid square factor f, check: a[i]/f and a[i]/f/f exist
    for (int f : factors) {
      res += (ll)ct[i] * get_ct(a_ct[i] / f) * get_ct(a_ct[i] / f / f);
    }
  }
  cout << res << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/