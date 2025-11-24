// Problem: CF 1473 B - String LCM
// https://codeforces.com/contest/1473/problem/B

/*
B. String LCM
Purpose: Find the shortest string that is divisible by both input strings s and t.
Algorithm:
- Compute LCM of string lengths using GCD.
- Repeat each string enough times to reach the LCM length.
- Compare resulting strings to check if they are equal.
Time Complexity: O(q * (m + n) * log(min(m,n))) where m, n are the lengths of s and t.
Space Complexity: O(m + n) for storing repeated strings.

Input:
- q: number of test cases
- For each case: two strings s and t (lengths up to 20)

Output:
- LCM string if exists, otherwise "-1"
*/

#include <iostream>
#include <string>

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  std::ios_base::sync_with_stdio(false);
  long q;
  std::cin >> q;
  while (q--) {
    std::string s, t;
    std::cin >> s >> t;
    long u(s.size()), v(t.size());
    long lcm = u * v / gcd(u, v); // Compute LCM of string lengths
    
    std::string x(""); // Build repeated s string
    for (long p = 0; p < lcm / u; p++) {
      x += s;
    }
    
    std::string y(""); // Build repeated t string
    for (long p = 0; p < lcm / v; p++) {
      y += t;
    }
    
    std::cout << (x == y ? x : "-1") << std::endl; // Output result or -1
  }
}


// https://github.com/VaHiX/codeForces/