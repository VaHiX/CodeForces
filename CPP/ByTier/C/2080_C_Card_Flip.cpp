/*
 * Problem URL : https://codeforces.com/problemset/problem/2080/C
 * Submit Date : 2025-08-23
 */
#include <bits/stdc++.h>
using namespace std;

#define ll long long
typedef vector<int> vi;
typedef array<int, 2> ii;
typedef vector<ii> vii;
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define all(x) x.begin(), x.end()
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "{";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin())
      os << ", ";
    os << *it;
  }
  os << "}";
  return os;
}

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}

#ifdef GRANGER
#define dbg(...)                                                               \
  cerr << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):",             \
      dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifdef GRANGER
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug.txt", "w", stderr);
  auto start = chrono::high_resolution_clock::now();
#endif
  ll t = 1;
  // cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vii a(n + m);
    rep(i, 0, n) { cin >> a[i][0]; }
    rep(i, 0, n) { cin >> a[i][1]; }
    rep(i, 0, m) {
      cin >> a[n + i][0];
      a[n + i][1] = INT_MAX;
    }
    sort(all(a), [](const ii &x, const ii &y) { return x[0] < y[0]; });
    // rep(i,0,n+m) {
    //     cout<<a[i][0]<<" "<<a[i][1]<<endl;
    // }
    int pos = -1;
    for (int i = n + m - 1; i >= 0; i--) {
      if (a[i][1] != INT_MAX) {
        pos = i;
        break;
      }
    }
    dbg(pos, a[pos][0], a[pos][1]);
    int j = pos - 1;
    while (j >= 0) {
      if (a[j][1] != INT_MAX && a[pos][0] > a[j][1]) {
        pos = j;
      }
      j--;
    }
    dbg(pos, a[pos][0], a[pos][1]);
    cout << (pos % 2 ? "Second" : "First") << endl;
  }

#ifdef GRANGER
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed = end - start;
  cerr << "Time taken: " << elapsed.count() << " seconds\n";
#endif
}