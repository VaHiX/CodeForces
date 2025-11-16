// Problem: CF 716 B - Complete the Word
// https://codeforces.com/contest/716/problem/B

/*
Algorithm: Sliding Window with Character Frequency Counting
Approach:
1. Use a sliding window of size 26 to check all possible substrings of length 26.
2. For each window, maintain a frequency map of characters.
3. If a window has exactly 26 unique characters and the number of '?' matches the number of missing characters,
   we can fill the '?' with the remaining letters.
4. Use a stack to store unused characters for filling '?'.
5. If no valid window is found, return -1.

Time Complexity: O(n), where n is the length of the string. Each character is processed at most twice (once in window and once for replacement).
Space Complexity: O(1), since we use a fixed-size map for 26 characters.

The algorithm efficiently finds a valid substring of length 26 where all letters from A-Z appear exactly once, with optional '?' characters that can be replaced.
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define N 50
using namespace std;
int main() {
  int i, j, k;
  int n, m, sum;
  string s, t;
  map<char, int> mp;
  cin >> s;
  if (s.length() < 26) {
    cout << "-1";
    return 0;
  }
  i = 0, j = 25;
  for (k = 0; k < 26; k++)
    mp[s[k]]++;
  bool f;
  while (j < s.length()) {
    f = 1;
    sum = 0;
    for (k = 'A'; k <= 'Z'; k++) {
      if (mp[k] > 1) {
        f = 0;
        break;
      } else if (mp[k] == 0)
        sum++;
    }
    if (!f) {
      mp[s[i]]--;
      i++;
      j++;
      mp[s[j]]++;
      continue;
    }
    if (sum == mp['?']) {
      stack<char> v;
      for (k = 'A'; k <= 'Z'; k++) {
        if (!mp[k])
          v.push(k);
      }
      for (k = i; k <= j; k++) {
        if (s[k] == '?')
          s[k] = v.top(), v.pop();
      }
      for (k = 0; k < s.length(); k++) {
        if (s[k] == '?')
          s[k] = 'A';
      }
      cout << s;
      return 0;
    }
  }
  cout << "-1";
  return 0;
}


// https://github.com/VaHiX/CodeForces/