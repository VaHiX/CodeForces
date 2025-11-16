// Problem: CF 1929 C - Sasha and the Casino
// https://codeforces.com/contest/1929/problem/C

/*
Code Purpose:
This code determines whether Sasha can guarantee earning an unlimited number of coins in a casino game with specific rules. 
The game involves placing bets with a win multiplier k and a maximum consecutive loss limit x.
Sasha starts with 'a' coins and must decide if there's a strategy to ensure he can accumulate any desired number of coins.

Algorithms/Techniques:
- Simulation with greedy approach to calculate maximum possible coins with optimal betting strategy
- Mathematical analysis using the constraint that after x consecutive losses, the strategy must reset
- Loop-based simulation where each iteration represents a betting cycle that includes up to x losses followed by a win

Time Complexity: O(X)
Space Complexity: O(1)

The approach simulates a betting sequence where after every x losses, a win occurs, allowing the strategy to reset and continue accumulating.
*/

#include <assert.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#pragma GCC optimize("unroll-loops")
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using ll = long long;
using ld = long double;
const ll ILL = 2167167167167167167;
const int INF = 2100000000;
const int mod = 998244353;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
template <class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
template <class T> ll LB(vector<T> &v, T a) {
  return lower_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> ll UB(vector<T> &v, T a) {
  return upper_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return 1;
  } else
    return 0;
}
template <class T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return 1;
  } else
    return 0;
}
template <class T> void So(vector<T> &v) { sort(v.begin(), v.end()); }
template <class T> void Sore(vector<T> &v) {
  sort(v.begin(), v.end(), [](T x, T y) { return x > y; });
}
void yneos(bool a, bool upp = 0) {
  if (a)
    cout << (upp ? "YES\n" : "Yes\n");
  else
    cout << (upp ? "NO\n" : "No\n");
}
template <class T> void vec_out(vector<T> &p, int ty = 0) {
  if (ty == 2) {
    cout << '{';
    for (int i = 0; i < (int)p.size(); i++) {
      if (i) {
        cout << ",";
      }
      cout << '"' << p[i] << '"';
    }
    cout << "}\n";
  } else {
    if (ty == 1) {
      cout << p.size() << "\n";
    }
    for (int i = 0; i < (int)(p.size()); i++) {
      if (i)
        cout << " ";
      cout << p[i];
    }
    cout << "\n";
  }
}
template <class T> T vec_min(vector<T> &a) {
  assert(!a.empty());
  T ans = a[0];
  for (auto &x : a)
    chmin(ans, x);
  return ans;
}
template <class T> T vec_max(vector<T> &a) {
  assert(!a.empty());
  T ans = a[0];
  for (auto &x : a)
    chmax(ans, x);
  return ans;
}
template <class T> T vec_sum(vector<T> &a) {
  T ans = T(0);
  for (auto &x : a)
    ans += x;
  return ans;
}
int pop_count(long long a) {
  int res = 0;
  while (a) {
    res += (a & 1), a >>= 1;
  }
  return res;
}
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}
void solve() {
  ll K, X, A;
  cin >> K >> X >> A;
  ll sum = 0;
  rep(i, 0, X + 1) {
    ll tmp = (sum + K - 1) / (K - 1);  // Calculate minimum bet needed to make progress
    sum += tmp;  // Add the bet amount to total spent
    if (A < sum)  // Check if we've exceeded available coins
      break;
  }
  yneos(sum <= A, 1);  // Output YES if it's possible to achieve unlimited coins
}


// https://github.com/VaHiX/CodeForces/