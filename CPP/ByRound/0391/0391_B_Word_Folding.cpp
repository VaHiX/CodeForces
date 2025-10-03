/*
 * Problem URL : https://codeforces.com/problemset/problem/391/B
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define FastIO                                                                 \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);                                                              \
  ios_base::sync_with_stdio(false);
#define FileIO                                                                 \
  freopen("input.txt", "r", stdin);                                            \
  freopen("output.txt", "w", stdout);
#define F first
#define S second
#define max_heap(T) priority_queue<T>
#define min_heap(T) priority_queue<T, vector<T>, greater<T>>
#define fr(i, a, b) for (int i = a; i < b; i++)
#define frr(i, a, b) for (int i = a; i > b; i--)
#define frin(i, A) for (auto &i : A)
#define frp(a, b, A) for (auto [a, b] : A)
#define SZ(x) (int)x.size()
#define all(A) A.begin(), A.end()
#define mins(a, b) a = min(a, b)
#define maxs(a, b) a = max(a, b)
#define pb push_back
#define Mp make_pair
#define kill(x) cout << x << '\n', exit(0)
#define md(a) (a % MOD + MOD) % MOD

const ll INF = 2e9;
const ll MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const int LOG = 30;

int lst[26], ans[26], n;
string s;

void solve() {
  cin >> s;
  n = SZ(s);
  fr(i, 0, 26) lst[i] = -1;
  fr(i, 0, n) if (lst[s[i] - 'A'] == -1 || (i - lst[s[i] - 'A']) & 1)
      lst[s[i] - 'A'] = i,
                 ans[s[i] - 'A']++;
  cout << *max_element(ans, ans + 26) << '\n';
}

int32_t main() {
  FastIO int T = 1;
  // cin >> T;
  while (T--)
    solve();
  return 0;
}