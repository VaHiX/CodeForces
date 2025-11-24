// Problem: CF 2159 C - Twin Polynomials
// https://codeforces.com/contest/2159/problem/C

/*
 * Problem: C. Twin Polynomials
 * 
 * Algorithm: Dynamic Programming with memoization and combinatorics
 * 
 * Time Complexity: O(N) where N is the degree of the polynomial
 * Space Complexity: O(N) for the DP array and auxiliary arrays
 * 
 * Approach:
 * 1. Parse the input polynomial coefficients, identifying which are determined and which are not.
 * 2. For each determined coefficient a[i], validate constraints:
 *    - If a[i] = i, it's consistent.
 *    - If a[i] > N, it's invalid.
 *    - If a[i] is determined and a[a[i]] is undetermined, we can assign it.
 *    - If a[a[i]] is determined but not equal to i, it's invalid.
 * 3. Count the number of undetermined values (denoted as 'zero').
 * 4. Use dynamic programming to compute valid combinations:
 *    - dp[i] represents number of ways to fill i undetermined variables.
 *    - Base cases: dp[0] = 1, dp[1] = 1.
 *    - Transition: dp[i] = dp[i-1] + dp[i-1] + dp[i-2] * (i-2)
 * 5. If the highest degree term is undetermined, subtract dp[zero-1] from result to exclude invalid cases where a_n = 0.

 * Key Observations:
 * - The problem requires that f(x) = g(x), where g(x) is defined as ∑ i * x^{a_i}.
 * - For the equality to hold, a_i = i is one possible valid configuration.
 * - We use DP to count valid assignments, leveraging Fibonacci-like recurrence.
 * - For degree term a_n, it cannot be 0, so adjust the final result if a_n is undetermined.
 */

#include <assert.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
const ll ILL = 2167167167167167167;
const int INF = 2100000000;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
template <class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
template <class T> int LB(vector<T> &v, T a) {
  return lower_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> int UB(vector<T> &v, T a) {
  return upper_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> bool chmin(T &a, T b) {
  if (b < a) {
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
bool yneos(bool a, bool upp = false) {
  if (a) {
    cout << (upp ? "YES\n" : "Yes\n");
  } else {
    cout << (upp ? "NO\n" : "No\n");
  }
  return a;
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
template <class T> T square(T a) { return a * a; }
struct mint {
  static constexpr int m = 1'000'000'007;
  int x;
  mint() : x(0) {}
  mint(long long x_) : x(x_ % m) {
    if (x < 0)
      x += m;
  }
  int val() { return x; }
  mint &operator+=(mint b) {
    if ((x += b.x) >= m)
      x -= m;
    return *this;
  }
  mint &operator-=(mint b) {
    if ((x -= b.x) < 0)
      x += m;
    return *this;
  }
  mint &operator*=(mint b) {
    x = (long long)(x)*b.x % m;
    return *this;
  }
  mint pow(long long e) const {
    mint r = 1, b = *this;
    while (e) {
      if (e & 1)
        r *= b;
      b *= b;
      e >>= 1;
    }
    return r;
  }
  mint inv() { return pow(m - 2); }
  mint &operator/=(mint b) { return *this *= b.pow(m - 2); }
  friend mint operator+(mint a, mint b) { return a += b; }
  friend mint operator-(mint a, mint b) { return a -= b; }
  friend mint operator/(mint a, mint b) { return a /= b; }
  friend mint operator*(mint a, mint b) { return a *= b; }
  friend bool operator==(mint a, mint b) { return a.x == b.x; }
  friend bool operator!=(mint a, mint b) { return a.x != b.x; }
};
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}
void solve() {
  int N;
  cin >> N;
  N++;
  vector<int> A(N);
  rep(i, 0, N) cin >> A[i];
  rep(i, 0, N) if (A[i] != -1) {
    if (A[i] == i)
      continue;
    if (A[i] == -1 || A[i] == 0)
      continue;
    if (N <= A[i]) {
      cout << "0\n";
      return;
    }
    if (A[A[i]] == -1) {
      A[A[i]] = i;
    }
    if (A[A[i]] != i) {
      cout << "0\n";
      return;
    }
  }
  int zero = 0;
  rep(i, 0, N) {
    if (A[i] == -1)
      zero++;
  }
  vector<mint> dp(zero + 1);
  dp[1] = 1;
  rep(i, 2, zero + 1) {
    dp[i] = dp[i - 1];
    dp[i] += dp[i - 1];
    dp[i] += dp[i - 2] * (i - 2);
  }
  mint ans = dp[zero];
  if (A.back() == -1)
    ans -= dp[zero - 1];
  cout << ans.val() << "\n";
}


// https://github.com/VaHiX/CodeForces/