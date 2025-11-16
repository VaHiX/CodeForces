// Problem: CF 1979 D - Fixing a Binary String
// https://codeforces.com/contest/1979/problem/D

/*
Algorithm/Technique: Simulation and Pattern Recognition
Time Complexity: O(n) for each test case, where n is the length of the string
Space Complexity: O(n) for storing the input string

This code solves the problem of finding a value of p such that applying the given operations makes the binary string k-proper.
The approach checks for valid positions to perform the reversal and cyclic shift operations that result in a k-proper string.

Key idea:
- For a string to be k-proper, the first k characters must be identical and the pattern should repeat every k characters.
- We simulate the transformation for possible values of p and check if the result satisfies the k-proper condition.
- The key insight is to identify transitions in the string and how reversing and shifting affects those transitions.
*/
#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define ll long long
using namespace std;
const int Max = 2 * (int)1e5 + 10, mod = (int)1e9 + 7;
ll a[Max], ans[Max];
queue<int> q;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int tmpnum = s[0] - '0';
    int ans = 0;
    int weilength = 1;
    bool succeed = 1, weishu = s[n - 1] - '0';
    for (int i = n - 1; i > 0 && s[i] == s[i - 1]; i--)
      weilength++;
    int tmplength = 1;
    for (int i = 1; i < n; i++) {
      if (s[i] == s[i - 1])
        tmplength++;
      else {
        if (tmplength < k) {
          if (ans)
            succeed = 0;
          else if (tmplength + weilength != k || s[i - 1] - '0' != weishu)
            succeed = 0;
          else
            ans = i;
        } else if (tmplength > k) {
          tmplength -= k;
          if (ans)
            succeed = 0;
          else if ((tmplength + weilength == k && s[i - 1] - '0' == weishu) ||
                   (weilength == k && tmplength == k &&
                    s[i - 1] - '0' != weishu))
            ans = i - k;
          else
            succeed = 0;
        }
        tmplength = 1;
      }
      if (i == n - 1 && tmplength != k && ans == 0)
        succeed = 0;
    }
    if (succeed) {
      if (ans)
        cout << ans << "\n";
      else
        cout << n << "\n";
    } else
      cout << "-1\n";
  }
}


// https://github.com/VaHiX/CodeForces/