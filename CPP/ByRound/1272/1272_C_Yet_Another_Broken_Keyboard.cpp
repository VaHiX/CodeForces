// Problem: CF 1272 C - Yet Another Broken Keyboard
// https://codeforces.com/contest/1272/problem/C

/*
C. Yet Another Broken Keyboard
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithm: 
- Use a boolean vector to mark which characters are available on the keyboard.
- Traverse the string and group consecutive valid characters (those in the keyboard).
- For each group of length `cnt`, the number of substrings it contributes is `cnt * (cnt + 1) / 2`.
- Sum up contributions from all such groups.

Time Complexity: O(n + k)
Space Complexity: O(1)

Examples:
Input
7 2
abacaba
a b
Output
12

Input
10 3
sadfaasdda
f a d
Output
21

Input
7 1
aaaaaaa
b
Output
0
*/

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  const int N = 26; // Number of lowercase English letters
  std::ios_base::sync_with_stdio(false);
  ll n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  std::vector<bool> f(N, 0); // Boolean vector to mark available characters
  for (ll p = 0; p < k; p++) {
    char c;
    std::cin >> c;
    f[c - 'a'] = 1; // Mark character as available
  }
  std::vector<ll> b; // Vector to store lengths of valid consecutive sequences
  ll cnt(0); // Counter for current sequence length
  for (ll p = 0; p < n; p++) {
    if (f[s[p] - 'a']) { // If character is available
      ++cnt;
      continue;
    }
    b.push_back(cnt); // Store the length of current valid sequence
    cnt = 0; // Reset counter
  }
  ll total(cnt * (cnt + 1) / 2); // Add contribution from last valid sequence
  for (ll p = 0; p < b.size(); p++) {
    total += b[p] * (b[p] + 1) / 2; // Add contributions from previous sequences
  }
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/