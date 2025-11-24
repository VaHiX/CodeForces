// Problem: CF 2036 F - XORificator 3000
// https://codeforces.com/contest/2036/problem/F

/*
F. XORificator 3000
Purpose: Compute XOR of all integers x in range [l, r] such that x % (2^i) != k.
Algorithm: 
  - Uses a mathematical property of XOR over ranges:
    For any number n, f(n) = XOR(0..n) can be computed efficiently using a pattern based on modulo 4.
  - Then for interval [l, r], the result is f(r) ^ f(l-1).
  - The main logic adjusts l and r using bit shifts (>> x), then recomputes XOR of adjusted range.
  - Handles special cases like negative l after shifting.
Time Complexity: O(1) per query
Space Complexity: O(1)
*/

#include <stdio.h>

// Function to compute XOR from 0 to x efficiently using pattern-based approach
inline long long f(long long x) {
  switch (x & 3) {        // Check last two bits of x
    case 0:               // If x % 4 == 0
      return x;
    case 1:               // If x % 4 == 1
      return 1;
    case 2:               // If x % 4 == 2
      return x + 1;
    default:              // If x % 4 == 3 (case 3)
      return 0;
  }
}

long long l, r, ans;   // Input and intermediate variables
int T, x, y;           // Number of queries, shift amount and k value

int main() {
  scanf("%d", &T);     // Read number of test cases
  while (T--) {
    scanf("%lld%lld%d%d", &l, &r, &x, &y);   // Read l, r, x (shift), y (k)
    
    // Compute XOR of interesting numbers in [l, r]
    ans = f(r) ^ f(l - 1);        // XOR prefix of range [0..r] and [0..l-1]

    // Adjust l and r using bit shifting based on x
    r = r - y >> x;               // Right shift (r - k) by x bits
    l = (l - y - 1 >> x) + 1;     // Right shift (l - k - 1) by x bits, then add 1

    if (l < 0)                    // Ensure l doesn't go negative
      l = 0;

    // If the count of adjusted numbers is odd, toggle y in answer
    if (r - l + 1 & 1)
      ans ^= y;

    // XOR with contribution from new range [l, r] shifted back by x bits
    ans ^= (f(r) ^ f(l - 1)) << x;

    printf("%lld\n", ans);        // Output final result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/