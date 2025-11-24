// Problem: CF 1878 F - Vasilije Loves Number Theory
// https://codeforces.com/contest/1878/problem/F

/*
Algorithm: Number theory, Prime factorization, Divisor function
Time Complexity: O(MAX_VAL * log(log(MAX_VAL)) + q * sqrt(n)) where MAX_VAL = 1e5
Space Complexity: O(MAX_VAL + q * log(n)) for sieve, primes, and factor maps

The problem involves determining whether there exists a positive integer `a` such that 
gcd(a, n) = 1 and d(n * a) = n, where d(n) is the number of divisors of n.
We precompute primes using sieve of Eratosthenes and then use factorization to 
analyze the divisor count and conditions for existence of `a`.

For a solution to exist, we must find if there's a way to choose a = product of primes
not dividing n such that d(n * a) = n. This translates to checking if the prime powers 
in n * a allow for total divisors to be exactly n.
*/

#include <stddef.h>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
vector<int> primes;
namespace sieve {
const int MAX_VAL = 1e5 + 1;
bitset<MAX_VAL> mark;
void init() {
  mark.set();
  for (int i = 4; i < MAX_VAL; i += 2)
    mark[i] = 0;
  for (int i = 3; i * i < MAX_VAL; i += 2) {
    if (mark[i]) {
      for (int j = i * i; j < MAX_VAL; j += i)
        mark[j] = 0;
    }
  }
  for (int i = 2; i < MAX_VAL; i++) {
    if (mark[i])
      primes.push_back(i);
  }
}
} // namespace sieve
using namespace sieve;
map<int, int> factorize(int num) {
  map<int, int> facts;
  for (auto p : primes) {
    if (1LL * p * p > num)
      break;
    int exp = 0;
    while (num % p == 0) {
      exp++;
      num /= p;
    }
    if (exp)
      facts[p] = exp;
  }
  if (num > 1)
    facts[num] = 1;
  return facts;
}
void update(map<int, int> &facts, int num) {
  for (auto p : primes) {
    if (1LL * p * p > num)
      break;
    int exp = 0;
    while (num % p == 0) {
      exp++;
      num /= p;
    }
    if (exp)
      facts[p] += exp;
  }
  if (num > 1)
    facts[num] += 1;
}
int d(map<int, int> &facts) {
  int ret = 1;
  for (auto [p, exp] : facts) {
    ret *= (exp + 1);
  }
  return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  init();
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int q;
    cin >> q;
    map<int, int> initf = factorize(n);
    auto curf = initf;
    int num = n;
    while (q--) {
      int op;
      cin >> op;
      if (op == 2) {
        curf = initf; // Reset to initial state
      } else {
        int x;
        cin >> x;
        update(curf, x); // Multiply n by x, update factorization
        int dn = d(curf); // Compute current number of divisors
        auto dnf = factorize(dn); // Factorize divisor count
        bool flag = true;
        // Check if every prime power in divisor count can be formed from current n*a
        for (auto [p, exp] : dnf) {
          if (curf.find(p) == curf.end() or curf[p] < exp) {
            flag = false;
            break;
          }
        }
        if (flag)
          cout << "YES\n";
        else
          cout << "NO\n";
      }
    }
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/