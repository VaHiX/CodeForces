// Problem: CF 518 B - Tanya and Postcard
// https://codeforces.com/contest/518/problem/B

/*
Purpose: 
This program determines the optimal way to construct a message string `s` from a newspaper string `t` such that:
- Maximum number of positions match both in value and case (YAY)
- Among all such constructions, maximize the number of positions that match in value but not case (WHOOPS)

Algorithm:
1. Count the frequency of each character in the newspaper string `t`.
2. First pass through `s`:
   - If the exact character (case-sensitive) exists in `t`, use it, mark it as used, increment YAY count.
3. Second pass through `s`:
   - For unused characters, check if the opposite case version exists in `t`.
   - If so, use it, mark it as used, increment WHOOPS count.

Time Complexity: O(n + m), where n is length of s, m is length of t
Space Complexity: O(1) since there are only 52 possible distinct characters (26 lowercase + 26 uppercase)
*/

#include <stddef.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Function to return the opposite case of a given character
char opp_case(char x) {
  if (x >= 'a') {
    return (char)(x - 32);  // Convert lowercase to uppercase
  } else {
    return (char)(x + 32);  // Convert uppercase to lowercase
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s, t;
  cin >> s >> t;
  map<char, int> tt;  // Frequency map for characters in t

  // Count occurrences of each character in t
  for (char x : t)
    tt[x]++;

  int y = 0, w = 0;  // y: YAY count, w: WHOOPS count

  // First pass: try to match exact characters (case-sensitive)
  for (char &x : s) {
    if (tt[x] > 0) {
      tt[x]--;
      y++;
      x = ' ';  // Mark as used by replacing with space
    }
  }

  // Second pass: try to match characters with correct value but wrong case
  for (char x : s) {
    if (tt[opp_case(x)] > 0) {
      tt[opp_case(x)]--;
      w++;
    }
  }

  cout << y << ' ' << w << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/