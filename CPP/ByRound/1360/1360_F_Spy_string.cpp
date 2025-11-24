// Problem: CF 1360 F - Spy-string
// https://codeforces.com/contest/1360/problem/F

/*
Algorithm: Brute Force
Approach:
- For each position in the string (m positions), we try all possible lowercase letters ('a' to 'z') as the character at that position.
- For each candidate string formed by replacing one character at a time, we check if this string differs from each given string in at most one position.
- If such a string is found, we output it.
- If no such string exists after trying all possibilities, we output -1.

Time Complexity: O(m * 26 * n * m) = O(m^2 * n)
Space Complexity: O(n * m) for storing input strings

Techniques:
- Brute force with early termination using goto for efficiency
- Character-by-character comparison to count differences
*/

#include <iostream>
#include <string>

using namespace std;
string a[20];
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    string s;
    for (int x = 0; x < n; x++)
      cin >> a[x];
    for (int x = 0; x < m; x++) // Iterate through each position
      for (char y = 'a'; y <= 'z'; y++) { // Try each letter at current position
        s = a[0]; // Start with first string
        s[x] = y; // Replace character at position x
        for (int z = 0; z < n; z++) { // Check against all input strings
          int c = 0;
          for (int u = 0; u < m; u++) // Count differences
            if (s[u] != a[z][u])
              c++;
          if (c > 1) // If more than one different character, skip this candidate
            goto none;
        }
        cout << s << endl; // Found valid string
        goto done; // Exit early
      none:;
      }
    cout << -1 << endl; // No valid string found
  done:;
  }
}


// https://github.com/VaHiX/CodeForces/