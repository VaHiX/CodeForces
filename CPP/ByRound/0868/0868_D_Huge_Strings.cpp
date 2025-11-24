// Problem: CF 868 D - Huge Strings
// https://codeforces.com/contest/868/problem/D

/*
Algorithm: String Concatenation with Substring Coverage
- We maintain a list of strings that are formed by concatenating previous strings.
- For each new string, we determine the maximum length k such that all binary strings of length k appear as substrings.
- To do this, for each k from 1 to 10, we check all 2^k possible binary strings of that length to see if they all appear in the current string.
- We optimize by truncating strings longer than 1000 characters to avoid excessive computation.
- The maximum k is updated based on the previous operations, allowing us to avoid recomputing everything from scratch each time.

Time Complexity: O(m * 10 * 2^10 * L) where m is number of operations, L is average string length
Space Complexity: O(n * L) where n is initial number of strings and L is average string length

Techniques:
- Bit manipulation to generate all binary strings of a given length
- String concatenation and substring search
- Truncation of long strings to avoid exponential time blowup
*/

#include <iostream>
#include <string>

std::string s[2000]; // Array to store all strings (including concatenated ones)
int n, m, ans[2000]; // n: number of initial strings, m: number of operations, ans: answers for each string

// Function to compute the maximum k such that all binary strings of length k are substrings
long solve() {
  for (long b = 1; b <= 10; b++) { // Check for k from 1 to 10
    for (long t = 0; t < (1 << b); t++) { // Generate all 2^b binary strings of length b
      std::string v;
      for (int k = 0; k < b; k++) {
        v += (t >> k & 1 ? "1" : "0"); // Build binary string from bit representation
      }
      if (s[n].find(v) == std::string::npos) { // If this string is not found
        return b - 1; // Return the previous k that worked
      }
    }
  }
  return 10; // If all 2^10 strings were found, return 10 (though constraints limit this)
}

int main() {
  std::cin >> n;
  for (long p = 1; p <= n; p++) {
    std::cin >> s[p]; // Read initial strings
  }
  std::cin >> m;
  while (m--) {
    long a, b;
    std::cin >> a >> b;
    s[++n] = s[a] + s[b]; // Concatenate strings a and b to form new string n
    int len = s[n].length();
    if (len > 1000) {
      s[n] = s[n].substr(0, 500) + s[n].substr(len - 500, 500); // Truncate long strings
    }
    long m1 = ans[a] > ans[b] ? ans[a] : ans[b]; // Get maximum answer from operands
    long m2 = solve(); // Compute the answer for current string
    ans[n] = (m1 > m2) ? m1 : m2; // Store the larger of the two
    std::cout << ans[n] << std::endl; // Output the result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/