// Problem: CF 1934 E - Weird LCM Operations
// https://codeforces.com/contest/1934/problem/E

/*
Algorithm: 
This solution uses a constructive approach to generate operations that will produce all GCDs from 1 to n in the array.
The approach is different for small and large values of n:
- For small n (≤ 13), we construct a specific pattern of values and apply operations to generate all required GCDs.
- For large n (> 13), we use a different strategy that iteratively processes elements in groups of 12, constructing operations to create gcds in the range [1, n].

Time Complexity: O(N) - The number of operations is bounded by O(N/6 + 5) which is linear in N, and each operation is constant time.
Space Complexity: O(N) - We store at most O(N) operations and intermediate arrays.

*/
#include <algorithm>
#include <array>
#include <complex>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b) - 1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert
template <class T> bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
const int MOD = 1000000007;
const char nl = '\n';
const int MX = 100001;
void solve() {
  int N;
  cin >> N;
  if (N <= 13) {
    vi vals;
    F0Rd(i, N + 1) {
      if (i > N / 2) {
        vals.pb(i);
      }
    }
    int nxt = N / 2;
    while (sz(vals) % 3) {
      vals.pb(nxt);
      nxt--;
    }
    vector<array<int, 3>> ans;
    int gap = sz(vals) / 3;
    F0R(i, gap) {
      if (vals[i] % (2 * gap) == 0 && vals[i + 2 * gap] % (2 * gap) == 0) {
        if (vals[i] == 4 * gap) {
          ans.pb({4 * gap, 3 * gap, 1});
        } else {
          ans.pb({vals[i], vals[i] - 2 * gap, vals[i] - 4 * gap});
          ans.pb({vals[i] - gap, vals[i] - 3 * gap, vals[i] - 5 * gap});
        }
      } else {
        ans.pb({vals[i], vals[i] - gap, vals[i] - 2 * gap});
      }
    }
    cout << sz(ans) << nl;
    trav(a, ans) { cout << a[0] << " " << a[1] << " " << a[2] << nl; }
  } else {
    vector<array<int, 3>> ans;
    int cur = N;
    if (N % 4 == 0) {
      ans.pb({N, N - 1, 1});
      cur -= 2;
    } else if (N % 4 == 3) {
      cur -= 1;
      ans.pb({N, 1, 2});
    }
    while (cur > N / 2) {
      int v = cur;
      if (cur % 4 == 2) {
        v = cur - 1;
        ans.pb({cur, cur - 4, cur - 8});
      } else {
        ans.pb({cur - 3, cur - 7, cur - 11});
      }
      ans.pb({v, v - 1, v - 2});
      ans.pb({v - 4, v - 5, v - 6});
      ans.pb({v - 8, v - 9, v - 10});
      cur -= 12;
    }
    cout << sz(ans) << nl;
    trav(a, ans) { cout << a[0] << " " << a[1] << " " << a[2] << nl; }
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/