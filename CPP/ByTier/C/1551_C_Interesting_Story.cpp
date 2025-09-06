/*
 * Problem URL : https://codeforces.com/contest/1551/problem/C
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int q;
  cin >> q;
  while(q--) {
    int n;
    cin >> n;
    vector<string> words(n);
    for(string& s: words)
      cin >> s;
    
    int ans = 0;
    for(char l = 'a'; l <= 'e'; l++) {
      vector<int> cnt(n, 0);
      for(int i = 0; i < n; i++) for(char c: words[i]) {
        cnt[i] += (c == l ? 1 : -1);
      }
      sort(cnt.rbegin(), cnt.rend());
      int x = 0, y = 0;
      for(int i: cnt)
        if(y + i > 0)
          x++, y += i;
      ans = max(ans, x);
    }

    cout << ans << "\n";
  }
}

