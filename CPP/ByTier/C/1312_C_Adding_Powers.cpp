// Problem: CF 1312 C - Adding Powers
// https://codeforces.com/contest/1312/problem/C

/*
C. Adding Powers
Algorithm: Check if array can be represented as sum of powers of k with each power used at most once.
Approach:
   - For each element in the array, decompose it into base-k representation.
   - For each digit position (power), check if the digit is 0 or 1.
   - If any digit > 1, return NO.
   - If a digit is 1, we must use that power once. If we've already used a power at this position, return NO.
Time Complexity: O(n * log_k(max(a_i)) * 100) per test case, where log_k(max(a_i)) <= 60 for numbers up to 1e16
Space Complexity: O(1) as we use a fixed-size set with at most 60 elements.
*/
#include <cstdio>
#include <set>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::set<ll> s; // Stores which powers have been used
    bool res(true); // Result flag
    while (n--) {
      ll x;
      scanf("%lld", &x);
      for (long p = 0; x && res && p < 100; p++) { // Iterate through each power
        ll mod = (x % k); // Get the digit at current power in base-k representation
        if (mod > 1) {
          res = false; // If digit > 1, impossible to represent with only 0/1 coefficients
        }
        if (mod) { // If this power contributes (digit is 1)
          if (s.count(p)) { // Check if we've already used this power
            res = false;
          };
          s.insert(p); // Mark this power as used
        }
        x /= k; // Move to next power
      }
    }
    puts(res ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/