// Problem: CF 1249 C2 - Good Numbers (hard version)
// https://codeforces.com/contest/1249/problem/C2

/*
C2. Good Numbers (hard version)
Algorithms/Techniques: Base-3 representation with carry propagation
Time Complexity: O(log n) per query, where n is the input number
Space Complexity: O(log n) for storing the base-3 digits

The problem asks to find the smallest "good number" >= n, where a good number 
is one that can be represented as a sum of distinct powers of 3.

Approach:
1. Convert the number to base-3 representation
2. Process each digit from least significant to most significant
3. If any digit is > 1, we "carry" to the next position and reset all previous digits to 0
4. After processing, convert back to decimal

This works because the base-3 representation directly corresponds to sum of powers,
and by carrying whenever we have a digit > 1, we ensure no duplicates in powers.
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
    std::vector<ll> b; // Store base-3 digits
    while (n > 0) {
      b.push_back(n % 3); // Extract least significant digit in base 3
      n /= 3; // Move to next digit
    }
    bool carry(0); // Carry flag for propagation
    for (ll p = 0; p < b.size(); p++) {
      b[p] += carry; // Add carry from previous position
      carry = 0;
      if (b[p] <= 1) {
        continue; // No carry needed, proceed to next digit
      }
      // If current digit is 2 or more, we need carry propagation
      for (ll u = 0; u <= p; u++) {
        b[u] = 0; // Reset all digits up to current position to 0
      }
      carry = 1; // Set carry for next position
    }
    if (carry) {
      b.push_back(1); // Add new digit if carry remains after processing all positions
    }
    ll m(0); // Result number in decimal
    for (ll p = 0, cur = 1; p < b.size(); p++, cur *= 3) {
      m += b[p] * cur; // Convert from base-3 back to decimal
    }
    printf("%lld\n", m);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/