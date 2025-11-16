// Problem: CF 2048 C - Kevin and Binary Strings
// https://codeforces.com/contest/2048/problem/C

/*
Algorithm: Greedy approach to maximize XOR of two substrings
Approach:
1. The maximum XOR value is achieved when we have two binary strings differing in the most significant bit.
2. Since the first character is always '1', we want to maximize the XOR result by choosing:
   - One substring starting from the first character (to ensure the most significant bit is 1)
   - One substring with as many leading zeros as possible, to make the XOR result as large as possible

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a constant amount of extra space
*/

#include <stdint.h>
#include <iostream>
#include <string>

using namespace std;
#define endl '\n'
#define int long long
#define mod 998244353
#define mod2 1000000007
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
int ans;
void solve() {
  string s;
  cin >> s;
  int n = s.size();
  cout << 1 << " " << n << " "; // First substring covers entire string (from index 1)
  for (int i = 0; i < n; i++) {
    if (s[i] == '0') { // If we find a '0', try to place second substring such that it maximizes XOR
      int j = i - 1, idx = i;
      while (i < n && s[i] == '0') {
        i++; // Move past all consecutive 0s
        j--; // j moves to the left
        if (j < 0) { // Check if we went out of bounds
          cout << 1 << " " << n - idx << endl; // Second substring from 1 to end of remaining part
          return;
        }
      }
      cout << j + 2 << " " << idx + n - i << endl; // Output the positions of the second substring
      return;
    }
  }
  cout << 1 << " " << 1 << endl; // All characters are '1', so choose one character as second substring
}
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/