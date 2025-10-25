// Problem: CF 1619 C - Wrong Addition
// https://codeforces.com/contest/1619/problem/C

/*
C. Wrong Addition
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

The problem is to reverse-engineer a "wrong addition" process where two numbers are added digit by digit from right to left, but the carry propagation doesn't follow normal arithmetic rules.

Algorithm:
- Process digits from right to left.
- At each step:
  - If the current digit of s is >= current digit of a, then b's digit = s-digit - a-digit.
  - Otherwise, check if we can carry from next digit in s.
    - We can only carry if there's a next digit in s and that digit is > 0.
    - Then calculate: (s-digit + 10) - a-digit
    - If this value is valid (i.e., between 0 and 9), proceed; else, impossible.
- When a runs out of digits, we may still have some digits left in s.
  - If remaining digits are all zeros or if s has no more digits, then b = remaining part of s.
  - Otherwise, impossible.

Time Complexity: O(log(s)) per test case, since we process each digit once.
Space Complexity: O(log(s)) for storing the result vector.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, s;
    scanf("%lld %lld", &a, &s);
    std::vector<ll> v; // Stores digits of b in reverse order
    bool possible(true); // Flag to track if solution exists
    
    while (possible && a > 0) {
      ll x = (a % 10);   // Current digit of a
      a /= 10;
      ll y = (s % 10);   // Current digit of s (this is part of the sum)
      s /= 10;
      
      if (x <= y) {
        // Normal case: no carry needed
        v.push_back(y - x);
      } else if (s > 0) {
        // Try to carry from next digit in s, if available
        y += 10 * (s % 10);  // Add carry
        s /= 10;
        if (y < x || y > 9 + x) {
          possible = false;  // Invalid carry case
        } else {
          v.push_back(y - x);
        }
      } else {
        possible = false; // No more digits in s to handle the carry
      }
    }
    
    if (possible) {
      v.push_back(s); // Add any remaining digits from s as part of b
      ll b(0);
      for (ll p = v.size() - 1; p >= 0; p--) {
        b = 10 * b + v[p]; // Reconstruct number b from vector
      }
      printf("%lld\n", b);
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/