// Problem: CF 1249 C1 - Good Numbers (easy version)
// https://codeforces.com/contest/1249/problem/C1

/*
C1. Good Numbers (easy version)
Algorithm: This problem asks to find the smallest "good number" greater than or equal to n,
where a good number is one that can be represented as a sum of distinct powers of 3.
The approach uses base-3 representation and handles carries in a specific way:
- Convert the number to its base-3 representation.
- For each digit position, if the value is >= 2, we reset all previous digits to 0
  and increment the next higher digit (like a carry).
- This ensures only distinct powers of 3 are used, because any digit >= 2 in base 3
  would require using the same power multiple times, which violates the "distinct" requirement.
Time Complexity: O(log n) per query, since we process each digit in base-3 representation.
Space Complexity: O(log n), for storing the base-3 digits in the vector.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> b; // Store base-3 representation of n
    while (n > 0) {
      b.push_back(n % 3); // Extract least significant base-3 digit
      n /= 3;             // Move to next digit
    }
    bool carry(0);        // Flag to handle carry propagation
    for (ll p = 0; p < b.size(); p++) {
      b[p] += carry;    // Add carry from previous step
      carry = 0;
      if (b[p] <= 1) {  // No carry needed, continue
        continue;
      }
      for (ll u = 0; u <= p; u++) { // Reset all lower digits to 0
        b[u] = 0;
      }
      carry = 1; // Propagate carry to next digit
    }
    if (carry) {
      b.push_back(1); // If final carry, add a new digit
    }
    ll m(0);          // Reconstruct the result number
    for (ll p = 0, cur = 1; p < b.size(); p++, cur *= 3) {
      m += b[p] * cur; // Multiply each digit by appropriate power of 3
    }
    printf("%lld\n", m);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/