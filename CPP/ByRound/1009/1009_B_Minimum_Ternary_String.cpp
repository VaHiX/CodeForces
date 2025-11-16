// Problem: CF 1009 B - Minimum Ternary String
// https://codeforces.com/contest/1009/problem/B

#include <iostream>
#include <string>

using namespace std;

/*
 * Problem: B. Minimum Ternary String
 *
 * Purpose:
 *   Given a ternary string (consisting only of '0', '1', and '2'), we are allowed to swap adjacent characters:
 *   - '0' and '1' can be swapped (e.g., "01" ↔ "10")
 *   - '1' and '2' can be swapped (e.g., "12" ↔ "21")
 *   However, '0' and '2' cannot be directly swapped.
 *
 *   Goal:
 *     Rearrange the string to obtain the lexicographically smallest possible string using allowed swaps.
 *
 * Algorithm:
 *   1. Count all '1's in the input string.
 *   2. Build a new string `f` by removing all '1's from the input string.
 *   3. Find the first occurrence of a non-zero character in `f`.
 *   4. Insert the counted number of '1's at that position to minimize lexicographically.
 *   
 * Time Complexity:
 *   O(n), where n is the length of the input string. Single pass through the string to count and build result.
 * Space Complexity:
 *   O(n), for storing the modified string `f`.
 */

int main() {
  string s;
  cin >> s;
  string f;                 // New string built without '1's
  int c = 0;                // Count of '1's in input
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '1')        // If current char is '1', increment count
      c++;
    else                    // Otherwise, append to new string f
      f += s[i];
  }
  int k = 0;                // Position to insert '1's
  while (k < f.size() && f[k] == '0')   // Find first non-'0' character
    k++;
  f.insert(k, string(c, '1'));  // Insert all '1's before the first non-'0'
  cout << f;
  return 0;
}

// https://github.com/VaHiX/codeForces/