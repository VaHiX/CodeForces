// Problem: CF 2081 A - Math Division
// https://codeforces.com/contest/2081/problem/A

/*
Code Purpose:
This code calculates the expected number of operations to reduce a binary number x to 1,
where each operation is either floor(x/2) or ceil(x/2), both with equal probability (1/2).
It uses dynamic programming with reverse iteration and modular arithmetic.
Time Complexity: O(n) per test case, where n is the length of the binary string.
Space Complexity: O(n) for storing the input string.

Algorithms/Techniques:
- Dynamic Programming
- Modular Arithmetic
- Bit Manipulation
- Inverse modulo using Fermat's little theorem

*/

#include <stdio.h>
#include <iostream>

using namespace std;
typedef long long ll;
const ll inv2 = 5e8 + 4, mod = 1e9 + 7; // inv2 is modular inverse of 2 (mod 1e9+7)
ll t, n;
char s[1000009]; // Input binary string, 1-indexed

int main() {
  cin >> t; // Read number of test cases
  while (t--) {
    cin >> n; // Read length of binary string
    scanf("%s", s + 1); // Read binary string into s[1..n]
    ll ans = 0;
    // Iterate backwards from n down to 2
    for (ll i = n; i > 1; i -= 1) {
      // If current bit is '1', add 1 to answer, then multiply by inverse of 2 (modular)
      ans = (ans + (s[i] == '1')) * inv2 % mod;
    }
    // Final result: (n - 1) + ans, modulo 1e9+7
    printf("%lld\n", (n - 1 + ans) % mod);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/