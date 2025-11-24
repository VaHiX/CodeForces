// Problem: CF 2061 F1 - Kevin and Binary String (Easy Version)
// https://codeforces.com/contest/2061/problem/F1

/*
F1. Kevin and Binary String (Easy Version)
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm/Techniques: Greedy + Simulation with Block Manipulation

Time Complexity: O(n) amortized per test case, where n is the length of string s.
Space Complexity: O(n) for storing strings s and t.

This problem involves transforming a binary string s into a target string t using adjacent block swaps,
where each block is a maximal substring of identical characters. The greedy approach processes
the string from left to right, matching blocks in s to desired values in t based on certain conditions.
If transformation is not possible, -1 is returned.
*/
#include <iostream>
#include <string.h>
#include <utility>
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define dF(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> pii;
const int N = 4e5 + 5;
int n, ans;
char s[N], t[N];
void mian() {
  cin >> (s + 1) >> (t + 1), n = strlen(s + 1), ans = 0;
  F(i, 1, n) if (s[i] != t[i]) {   // When current character does not match target
    if (i > 1 && s[i] == s[i - 1] && t[i] != t[i - 1])
      return cout << "-1\n", void();  // Inconsistent case that makes it impossible
    int j = i, k = i, cnt = 0, tmp = 0;
    while (j < n && t[j + 1] == t[i])   // Extend j to include all consecutive similar characters in target
      ++j;
    while (k < n && cnt < j - i + 1) {  // Count how many matches we get as we go right through s
      cnt += s[++k] == t[i];
      if (s[k] == t[i] && s[k - 1] != t[i])  // If start of a new match
        ++tmp;
    }
    if (cnt < j - i + 1)   // Not enough matches => impossible to convert this section
      return cout << "-1\n", void();
    if (k < n && s[k + 1] == t[i])   // If after matching, next char also equals target => conflict
      return cout << "-1\n", void();
    ans += tmp;
    F(w, i, j) s[w] = t[i];        // Update s in range [i,j] to match target character
    F(w, j + 1, k) s[w] = (t[i] == '1' ? '0' : '1'); // Flip the rest to make correct alignment
  }
  cout << ans << "\n";
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    mian();
  return 0;
}


// https://github.com/VaHiX/codeForces/