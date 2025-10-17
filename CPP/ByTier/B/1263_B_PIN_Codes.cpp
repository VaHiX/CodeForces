/*
 * Problem URL : https://codeforces.com/contest/1263/problem/B
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s[10];
    map<string, int> mp;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> s[i];
      mp[s[i]]++;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (mp[s[i]] > 1) {
        ans++;
        mp[s[i]]--;
        for (int j = 0; j < 10; j++) {
          s[i][0] = j + '0';
          if (mp[s[i]] == 0)
            break;
        }
        mp[s[i]]++;
      }
    }
    cout << ans << "\n";
    for (int i = 0; i < n; i++)
      cout << s[i] << "\n";
  }
  return 0;
}
