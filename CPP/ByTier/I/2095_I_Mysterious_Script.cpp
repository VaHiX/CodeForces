// Problem: CF 2095 I - Mysterious Script
// https://codeforces.com/contest/2095/problem/I

/*
I. Mysterious Script
time limit per test1 second
memory limit per test256 megabytes

The Balikons are an extraterrestrial species that communicate using a special script.
Their language has a base-9 encoding system, where each symbol maps to a digit from 0 to 8.
The mapping is given by:
{"la", "le", "lon", "sha", "she", "shon", "ta", "te", "ton"} -> digits 0 through 8 respectively.

This program:
1. Converts input Balikon strings into decimal numbers using base-9.
2. Sums the two converted numbers.
3. Converts the sum back into the Balikon script using base-9 representation and mapping.

Algorithms:
- Base-9 numeral system conversion
- String matching for decoding
- Reverse string building for encoding

Time Complexity: O(n + m) where n and m are lengths of input strings s and t respectively.
Space Complexity: O(1) — fixed-size lookup array, string operations use linear space.

*/
#include <iostream>
#include <string>

using namespace std;
string s, t, oo,
    ss[] = {"la", "le", "lon", "sha", "she", "shon", "ta", "te", "ton"}; // Mapping of Balikon symbols to digits 0-8
long long o;

// Convert Balikon string to decimal number using base-9 encoding
long long trans(string s) {
  long long o = 0;
  for (int i = 0; i < s.length() - 1;) { // Iterate through input string
    o *= 9; // Shift base-9 value left by one digit
    for (int j = 0; j <= 9; ++j) // Try all possible symbols
      if (s.find(ss[j], i) == i) { // Check if symbol matches at current position
        o += j; // Add corresponding digit
        i += ss[j].length(); // Move past matched symbol
        break;
      }
  }
  return o;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> s >> t; // Read input strings
  o = trans(s) + trans(t); // Convert to numbers and sum
  oo = "s"; // Initialize output string
  while (o) { // While there are digits left in the sum
    oo = ss[o % 9] + oo; // Prepend the symbol for current digit
    o /= 9; // Move to next digit
  }
  cout << oo << "\n"; // Print result
  return 0;
}


// https://github.com/VaHiX/codeForces/