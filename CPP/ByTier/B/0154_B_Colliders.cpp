/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
#include <set>
#include <vector>

std::vector<long> getFactors(long x, std::vector<long> primes) {

  std::vector<long> ans;
  for (long p = 0; p < primes.size(); p++) {
    if (x % primes[p] == 0) {
      ans.push_back(primes[p]);
    }
  }

  if (ans.empty()) {
    ans.push_back(x);
  }
  return ans;
}

int main() {
  long n, m;
  std::cin >> n >> m;

  std::vector<bool> isPrime(n + 1, 1);
  isPrime[0] = 0;
  isPrime[1] = 0;
  for (long p = 2; p * p <= n; p++) {
    if (!isPrime[p]) {
      continue;
    }
    for (long q = 2 * p; q <= n; q += p) {
      isPrime[q] = 0;
    }
  }

  std::vector<long> primeList;
  for (long p = 2; p <= n; p++) {
    if (!isPrime[p]) {
      continue;
    }
    primeList.push_back(p);
  }

  std::vector<long> active(n + 1, 0);
  std::set<long> on;

  while (m--) {
    std::string s;
    long collider;
    std::cin >> s >> collider;

    std::vector<long> factors = getFactors(collider, primeList);

    if (s == "+") {
      if (on.count(collider) > 0) {
        puts("Already on");
      } else {
        long conflicted = 0;
        for (long p = 0; p < factors.size(); p++) {
          if (active[factors[p]] > 0) {
            conflicted = active[factors[p]];
            break;
          }
        }

        if (conflicted) {
          std::cout << "Conflict with " << conflicted << std::endl;
        } else {
          puts("Success");
          on.insert(collider);
          for (long p = 0; p < factors.size(); p++) {
            active[factors[p]] = collider;
          }
        }
      }
    }

    else if (s == "-") {
      if (on.count(collider) > 0) {
        std::cout << "Success" << std::endl;
        on.erase(collider);
        for (long p = 0; p < factors.size(); p++) {
          active[factors[p]] = 0;
        }
      } else {
        std::cout << "Already off" << std::endl;
      }
    }
  }

  return 0;
}
