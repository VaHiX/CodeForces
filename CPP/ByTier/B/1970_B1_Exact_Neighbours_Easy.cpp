// Problem: CF 1970 B1 - Exact Neighbours (Easy)
// https://codeforces.com/contest/1970/problem/B1

#include <iostream>

using namespace std;
#define OPTM                                                                   \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);
#define INF int(1e9 + 7)
#define ln '\n'
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define us unsigned short
#define FOR(i, s, n) for (int i = s; i < n; i++)
#define FORR(i, n, s) for (int i = n; i > s; i--)
#define FORX(u, arr) for (auto u : arr)
#define PB push_back
#define F first
#define S second
#define PII pair<int, int>
#define PLL pair<ll, ll>
#define UM unordered_map
#define US unordered_set
#define PQ priority_queue
#define ALL(v) v.begin(), v.end()
const ll LLINF = 1e18 + 1;
const int MAXN = 2e5 + 5;
int n;
int a[MAXN];
signed main() {
  OPTM;
  cin >> n;
  FOR(i, 1, n + 1) cin >> a[i];
  cout << "YES" << ln;
  FOR(i, 1, n + 1) cout << i << " " << i << ln;
  FOR(i, 1, n + 1)
      cout << (i - a[i] / 2 < 1 ? i + a[i] / 2 : i - a[i] / 2) << " ";
}


// https://github.com/VaHiX/CodeForces/