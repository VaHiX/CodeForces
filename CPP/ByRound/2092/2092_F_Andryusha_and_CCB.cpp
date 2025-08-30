/*
 * Problem URL : https://codeforces.com/problemset/problem/2092/F
 * Submit Date : 2025-08-22
 */

#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e6 + 2;
const int MOD = 998244353;
bool cd[MAXN];
int qzc[MAXN];
char s[MAXN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int casenum;
  cin >> casenum;
  while (casenum--) {
    int n;
    cin >> n;
    cin >> s;
    int cnt = 0;
    cd[0] = 0;
    for (int i = 1; i < n; i++) {
      if (s[i] == s[i - 1])
        cd[cnt] = 1;
      else
        cnt++, cd[cnt] = 0;
    }
    for (int i = 0; i <= cnt; i++)
      qzc[i] = 0;
    for (int i = 1; i < n; i++) {
      int l = 0, r = 0;
      while (l <= cnt) {
        if (l + i > cnt)
          break;
        qzc[l + i]++;
        if (r + i + 1 <= cnt)
          qzc[r + i + 1]--;
        r += i + 1;
        if (cd[l + i])
          l += i;
        else
          l += i + 1;
      }
    }
    int cnt0 = 0;
    int now = 0;
    cout << 1 << " ";
    for (int i = 1; i < n; i++) {
      if (s[i] != s[i - 1])
        now += qzc[++cnt0];
      cout << now + i - cnt0 + 1 << ' ';
    }
    cout << endl;
  }
}