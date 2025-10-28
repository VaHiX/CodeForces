// Problem: CF 1465 B - Fair Numbers
// https://codeforces.com/contest/1465/problem/B

/*
B. Fair Numbers
Algorithm: For each number n, we find the smallest fair number >= n.
A number is fair if it's divisible by all its nonzero digits.
Approach:
  - For each test case, start from n and increment until a fair number is found.
  - To check if a number is fair:
    * Extract all digits.
    * For each digit d (1-9) that appears in the number, verify that n % d == 0.
Time Complexity: O(log^2(n)) per query on average, due to checking divisibility for digits.
Space Complexity: O(1), since we use fixed-size arrays.
*/
#include <cstdio>
#include <vector>
typedef long long ll;

// Check if number x is fair
bool check(ll x) {
  std::vector<bool> digits(10); // Track which digits (1-9) are present in x
  ll m(x);
  while (m > 0) {
    digits[m % 10] = 1; // Mark the digit as present
    m /= 10;
  }
  for (ll p = 1; p <= 9; p++) {
    if (digits[p] && (x % p != 0)) { // If digit p is present and x not divisible by p
      return false;
    }
  }
  return true;
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(n);
    while (!check(res)) { // Increment until we find a fair number
      ++res;
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/