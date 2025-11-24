// Problem: CF 2161 A - Round Trip
// https://codeforces.com/contest/2161/problem/A

/*
Problem: Maximum Rated Rounds
Algorithms/Techniques: Greedy approach
Time Complexity: O(n) where n is the number of rounds
Space Complexity: O(1) - only using a few variables regardless of input size

The solution uses a greedy strategy:
- For each round, determine if Vasya can participate rated
- If it's a div.1 round, he can always participate rated
- If it's a div.2 round, he can participate rated only if his rating < X
- For each rated round, decrease his rating by D (minimum possible rating is 0)
- Count total rated rounds

Key observations:
- Vasya wants to maximize rated rounds
- He can choose any rating between [R-D, R+D] after a rated round
- So we should aim to keep his rating as low as possible to allow more div.2 rounds
- But if rating is already < X, he can participate in div.2 rated
- Greedy: always participate in rated rounds possible, decrease rating by D
*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <stdio.h>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define vi(a, n)                                                               \
  vector<int> a(n);                                                            \
  rep(i, 0, n) cin >> a[i]
#define yes cout << "YES" << "\n"
#define no cout << "NO" << "\n"
#define ff(ans) cout << ans << '\n'
#define sz(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define sum(v) accumulate(v.begin(), v.end(), 0ll)
#define PQ(T) priority_queue<T, vector<T>, greater<T>>
#define mn(a) *min_element(all(a))
#define mx(a) *max_element(all(a))
#define rsort(v)                                                               \
  sort(all(v), [](const pll &a, const pll &b) { return a.S < b.S; });
typedef long double lld;
#ifndef ONLINE_JUDGE
#define debug(x)                                                               \
  cerr << #x << " ";                                                           \
  _print(x);                                                                   \
  cerr << endl;
#else
#define debug(x)
#endif
void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
template <class T, class V> void _print(pair<T, V> p);
template <class T> void _print(vector<T> v);
template <class T> void _print(set<T> v);
template <class T, class V> void _print(map<T, V> v);
template <class T> void _print(multiset<T> v);
template <class T, class V> void _print(pair<T, V> p) {
  cerr << "{";
  _print(p.ff);
  cerr << ",";
  _print(p.ss);
  cerr << "}";
}
template <class T> void _print(vector<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(set<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(multiset<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T, class V> void _print(map<T, V> v) {
  cerr << "[ ";
  for (auto i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
const ll INF = 1e18;
const int MOD = 998244353;
const int MAX = 2e5 + 2;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename ForwardIterator, typename T>
ForwardIterator first_less_than(ForwardIterator first, ForwardIterator last,
                                T value) {
  auto it = upper_bound(first, last, value);
  return (it == first ? last : --it);
}
inline ll ceil0(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }
void solve() {
  int r0, x, d, n, res = 0;
  cin >> r0 >> x >> d >> n;
  string s;
  cin >> s;
  for (char c : s) {
    if (c == '1') {
      // Div.1 round - always rated
      res++;
      r0 = max(0, r0 - d);  // Decrease rating by D (greedy)
    } else {
      // Div.2 round - rated only if rating < X
      if (r0 < x) {
        res++;
        r0 = max(0, r0 - d);  // Decrease rating by D (greedy)
      }
    }
  }
  ff(res);
}
int main() {
#ifndef ONLINE_JUDGE
  FILE *f = freopen("Error.txt", "w", stderr);
  if (!f) {
    perror("freopen failed");
  }
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/