// Problem: CF 2039 B - Shohag Loves Strings
// https://codeforces.com/contest/2039/problem/B

/*
Code Purpose:
This code solves the problem of finding a substring of a given string such that the number of distinct non-empty substrings of that substring is even. 
The solution leverages the observation that:
1. If there are two consecutive identical characters, then the substring formed by these two characters will have exactly 3 distinct substrings: the first character, the second character, and the two-character substring. Since 3 is odd, we try to pick a longer substring.
2. If we have three characters with the first and third being the same (i.e., s[i-2] == s[i]), then we can pick that substring (s[i-2]s[i-1]s[i]) which will have 7 distinct substrings (odd), so we need to be more careful.
3. The key insight is that for any string, we can pick a substring with a pattern that ensures even distinct substrings, especially when we find certain repeated or symmetric patterns.
The algorithm uses a greedy approach:
- First, check for two consecutive identical characters.
- Then, check for a pattern of three characters where first and third are the same.
If neither case is caught, then return -1.

Algorithms/Techniques:
Greedy approach with pattern matching on substrings

Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(1) - uses only a fixed amount of extra space regardless of input size.

*/
#include <time.h>
#include <iostream>
#include <string>

using namespace std;
#define fi first
#define se second
typedef long long ll;
bool a1;
string s;
int n, cnt[26];
void solve() {
  cin >> s;
  n = s.size();
  // Check for two consecutive identical characters
  for (int i = 1; i < n; ++i) {
    if (s[i] == s[i - 1]) {
      cout << s[i] << s[i] << '\n';
      return;
    }
  }
  // Check for pattern where first and third char are same
  for (int i = 2; i < n; ++i) {
    if (s[i] != s[i - 2]) {
      cout << s[i - 2] << s[i - 1] << s[i] << '\n';
      return;
    }
  }
  cout << "-1\n";
}
bool a2;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cerr << "static memory::" << &a1 - &a2 << '\n';
  int t;
  cin >> t;
  while (t--)
    solve();
  cerr << "time::" << clock() << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/