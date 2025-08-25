/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/F1
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
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
  F(i, 1, n) if (s[i] != t[i]) {
    if (i > 1 && s[i] == s[i - 1] && t[i] != t[i - 1])
      return cout << "-1\n", void();
    int j = i, k = i, cnt = 0, tmp = 0;
    while (j < n && t[j + 1] == t[i])
      ++j;
    while (k < n && cnt < j - i + 1) {
      cnt += s[++k] == t[i];
      if (s[k] == t[i] && s[k - 1] != t[i])
        ++tmp;
    }
    if (cnt < j - i + 1)
      return cout << "-1\n", void();
    if (k < n && s[k + 1] == t[i])
      return cout << "-1\n", void();
    ans += tmp;
    F(w, i, j) s[w] = t[i];
    F(w, j + 1, k) s[w] = (t[i] == '1' ? '0' : '1');
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