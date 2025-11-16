// Problem: CF 1845 C - Strong Password
// https://codeforces.com/contest/1845/problem/C

/*
Algorithm: The solution uses a greedy approach to determine if a valid password exists.
It checks whether there exists a sequence of digits that satisfies the constraints on digit ranges
and does not form a subsequence in the given string s.

Time Complexity: O(m * |s|) where m is the length of the password and |s| is the length of the database string.
Space Complexity: O(1) since we use only a constant amount of extra space (vis array of size 10).

Techniques:
- Greedy selection of digits
- Subsequence checking
*/

#include <math.h>
#include <string.h>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, b, a) for (int i = b; i >= a; i--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<long long> VLL;
mt19937_64 rng(random_device{}());
template <typename... T> void debug_out(T... args) {
  ((cerr << args << " "), ...);
  cerr << '\n';
}
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mp make_pair
#define bit(x) (1ll << (x))
#define SZ(x) ((int)x.size())
#define all(x) x.begin(), x.end()
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
ll powmod(ll a, ll b, const ll p) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % p;
    b >>= 1;
    a = a * a % p;
  }
  return res;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
const int mod = 1e9 + 7;
const int inf = 1ll << 29;
const double pi = acosl(-1);
const double eps = 1e-12;
const int maxn = 3e5 + 105;
const int N = 205;
ll n, m, k;
char s[maxn], L[101], R[101], vis[20];
void solve() {
  cin >> (s + 1) >> n;
  m = strlen(s + 1);
  cin >> (L + 1) >> (R + 1);
  int cnt = 1;
  rep(i, 0, 10) vis[i] = 0;
  for (int i = 1; cnt <= n && i <= m; i++) {
    vis[s[i] - '0'] = 1;  // Mark current character in database as seen
    bool flag = 1;
    for (char j = L[cnt]; j <= R[cnt]; j++) {
      if (!vis[j - '0']) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      cnt++;  // A valid digit is found for current position
      rep(j, 0, 10) vis[j] = 0;  // Reset for next digit
    }
  }
  cout << ((cnt <= n) ? "YES" : "NO") << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/