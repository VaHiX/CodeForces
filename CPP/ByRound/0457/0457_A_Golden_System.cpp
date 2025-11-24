// Problem: CF 457 A - Golden System
// https://codeforces.com/contest/457/problem/A

/*
Purpose: Compare two numbers in the "golden system" (based on the golden ratio φ, where φ² = φ + 1).
         The golden system uses only 0s and 1s, but has special rules for normalization:
         Any two consecutive 1s are replaced by a single 1 in the next higher position,
         similar to how binary numbers work in some canonical forms.

Algorithms/Techniques:
- Normalization of golden system representation using the rule that 11 → 100 (in a carry-like manner)
- Padding zeros to make strings equal length for comparison
- Direct lexicographical comparison after normalization

Time Complexity: O(n) where n is the maximum length of the two input strings.
Space Complexity: O(n) for storing the normalized strings.

*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>

#define MOD 1000000007
#define MAX 200000
using namespace std;

// Function to normalize a golden system number
// This performs the operation: 11 -> 100, recursively, from left to right
string nrml(string s) {
  s = "000" + s;  // Add leading zeros to avoid boundary checks
  for (int i = 0; i + 1 < s.size(); ++i) {
    if (s[i] == '1' && s[i + 1] == '1') {  // Found consecutive 1s
      int j = i + 1;
      // Perform recursive transformation to normalize the 11s
      while (s[j - 1] == s[j]) {
        s[j - 2] = '1';  // Carry 1 to the left
        s[j - 1] = s[j] = '0';  // Set current positions to 0
        j -= 2;  // Move back 2 positions
      }
    }
  }
  return s;
}

// Function to pad zeros to make two strings of equal length
void addZeros(string &a, string &b) {
  int mx = max(a.size(), b.size());
  string az(mx - a.size(), '0');  // Create zero padding for 'a'
  string bz(mx - b.size(), '0');  // Create zero padding for 'b'
  a = az + a;
  b = bz + b;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string a, b;
  cin >> a >> b;

  // Normalize both numbers
  a = nrml(a);
  b = nrml(b);

  // Pad to same length
  addZeros(a, b);

  // Compare normalized forms directly
  if (a == b)
    cout << "=" << endl;
  else if (a > b)
    cout << ">" << endl;
  else
    cout << "<" << endl;

  return 0;
}


// https://github.com/VaHiX/CodeForces/