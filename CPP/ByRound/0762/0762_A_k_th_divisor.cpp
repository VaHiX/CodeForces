// Problem: CF 762 A - k-th divisor
// https://codeforces.com/contest/762/problem/A

/*
 * Problem: Find the k-th smallest divisor of a given number n.
 *
 * Approach:
 * - Iterate through all numbers from 1 to sqrt(n).
 * - For each number p that divides n, add both p and n/p to the list of divisors.
 * - If p == n/p (i.e., p is the square root of n), avoid adding n/p twice.
 * - Sort the list of divisors and return the k-th element.
 *
 * Time Complexity: O(sqrt(n) + d*log(d)) where d is the number of divisors.
 *                  In worst case, d can be up to 2*sqrt(n), so overall O(sqrt(n)*log(sqrt(n))).
 * Space Complexity: O(d) where d is the number of divisors, which is at most 2*sqrt(n).
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int64_t n, k;
  std::cin >> n >> k;
  std::vector<int64_t> v;
  for (int64_t p = 1; p * p <= n; p++) {
    if (n % p != 0) {
      continue;
    }
    v.push_back(p);
    if (p * p != n) {
      v.push_back(n / p);
    }
  }
  if (k > v.size()) {
    std::cout << "-1" << std::endl;
  } else {
    sort(v.begin(), v.end()); // Sort the divisors to find the k-th smallest
    std::cout << v[k - 1] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/