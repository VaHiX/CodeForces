// Problem: CF 1866 D - Digital Wallet
// https://codeforces.com/contest/1866/problem/D

/*
Purpose: Solve the Digital Wallet problem where we select elements from arrays to maximize the total sum,
         with constraints on how elements can be selected in sequence.

Algorithm: Dynamic Programming with sliding window optimization.
           - For each position in the arrays, we maintain a DP table where dp[i][j] represents the maximum
             sum we can achieve up to the i-th operation with exactly j elements selected from the current
             window of size K.
           - We pre-sort each column (array) in descending order to always pick the largest available element.
           - At each step, we try all valid combinations of selecting elements from the current window.

Time Complexity: O(M * K * N), where M is the number of operations, K is the window size, and N is the number of arrays.
Space Complexity: O(M * K), for the DP table.

*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std;
namespace debug {
template <class c> struct rge {
  c b, e;
};
template <class c> rge<c> range(c i, c j) { return rge<c>{i, j}; }
template <class c> char spk(...);
template <class c> auto spk(c *a) -> decltype(cerr << *a, 0);
struct stream {
  ~stream() { cerr << endl; }
  template <class c>
  typename enable_if<sizeof spk<c>(0) != 1, stream &>::type operator<<(c i) {
    cerr << boolalpha << i;
    return *this;
  }
  template <class c>
  typename enable_if<sizeof spk<c>(0) == 1, stream &>::type operator<<(c i) {
    return *this << range(begin(i), end(i));
  }
  template <class a, class b> stream &operator<<(pair<a, b> p) {
    return *this << "(" << p.first << ", " << p.second << ")";
  }
  template <class c> stream &operator<<(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; it++)
      *this << ", " + 2 * (it == d.b) << *it;
    return *this << "]";
  }
  stream &_dbg(const string &s, int i, int b) { return *this; }
  template <class c, class... cs>
  stream &_dbg(const string &s, int i, int b, c arg, cs... args) {
    if (i == (int)(s.size()))
      return (*this << ": " << arg);
    b += (s[i] == '(') + (s[i] == '[') + (s[i] == '{') - (s[i] == ')') -
         (s[i] == ']') - (s[i] == '}');
    return (s[i] == ',' && b == 0)
               ? (*this << ": " << arg << "     ")._dbg(s, i + 1, b, args...)
               : (s[i] == ' ' ? *this : *this << s[i])
                     ._dbg(s, i + 1, b, arg, args...);
  }
};
} // namespace debug
#ifdef DEBUG
#define dout debug::stream()
#define dbg(...)                                                               \
  ((dout << "line:" << __LINE__ << " >> ")                                     \
       ._dbg(#__VA_ARGS__, 0, 0, __VA_ARGS__))
#else
#define dout
#define dbg(...)
#endif
#define rep(a, b) for (int a = 0; a < (b); a++)
#define all(a) (a).begin(), (a).end()
using ll = long long;
const int MAXN = 11;
const int MAXM = 1e5 + 7;
const ll INF = 1e18;
int A[MAXM][MAXN];
ll dp[MAXM][MAXN];
int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  int n, m, k;
  cin >> n >> m >> k;
  rep(i, n) rep(j, m) cin >> A[j + 1][i]; // Read input elements
  rep(i, m) sort(A[i + 1], A[i + 1] + n, greater<int>()); // Sort each column in descending order to maximize benefit
  rep(i, m) rep(j, k + 1) dp[i + 1][j] = -INF; // Initialize DP table with negative infinity
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < min(i + 1, k); j++) {
      if (j > 0 && dp[i - 1][j - 1] != -INF) {
        dp[i][j] = dp[i - 1][j - 1];
      }
      ll s = 0;
      for (int l = 1; l <= min({k - j, n, i - j}); l++) {
        s += A[i][l - 1]; // Accumulate sum of the selected elements
        dp[i][j] = max(dp[i][j], s + dp[i - 1][j - 1 + l]); // Update DP state
      }
    }
    dbg(debug::range(dp[i], dp[i] + k + 1));
  }
  cout << dp[m][k - 1] << '\n'; // Output the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/