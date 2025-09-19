#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    string s;
    cin >> n >> s;
    int prev = -1;
    vector<int> ans;
    for (int i = 0; i < n - 1; i++) {
      if (s[i] != s[i + 1]) {
        int c = ans.size();
        for (int j = 0; j < 2 * (i - prev); j++)
          ans.push_back(i + 1 + c);
        prev = i;
      }
    }
    if (prev == -1) {
      cout << -1 << "\n";
      continue;
    }
    int len = n - 1 - prev;
    for (int i = 0; i < 2 * len; i++)
      ans.push_back(n + ans.size() - len);
    cout << 2 * n << "\n";
    for (auto x : ans)
      cout << x << "\n";
  }
}
