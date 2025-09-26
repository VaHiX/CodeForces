/*
 * Problem URL : https://codeforces.com/contest/521/problem/A
 * Submit Date : 2025-09-06
 */

// #pragma GCC target ("sse4.2")

#include <bits/stdc++.h>

#define lli long long
#define x first
#define y second
#define maxi(a, b) a = max(a, b)
#define mize(a, b) a = min(a, b)
#define getbit(a, i) ((a) >> (i) & 1)

#define FOR(i, a, b) for (int i = a, _n = b; i <= _n; ++i)
#define FORD(i, a, b) for (int i = a, _n = b; i >= _n; --i)
#define REP(i, _n) for (int i = 0; i < _n; ++i)

#define sz(a) ((int)(a).size())
#define all(a) a.begin(), a.end()
#define pb push_back
#define mp make_pair

using namespace std;

int n;
string s, ACGT = "ACGT";
int cnt[256];
const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  // freopen("a.inp","r",stdin);

  cin >> n;
  cin >> s;

  REP(i, n) cnt[s[i]] += 1;

  int ma = 0, ans = 0;
  for (char &c : ACGT)
    if (cnt[c] >= ma) {
      if (cnt[c] > ma)
        ma = cnt[c], ans = 1;
      else
        ans += 1;
    }

  lli res = 1;
  REP(i, n) res = (res * ans) % MOD;
  cout << res;
}
