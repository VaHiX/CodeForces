// Problem: CF 1848 D - Vika and Bonuses
// https://codeforces.com/contest/1848/problem/D

/*
 * Problem: Vika and Bonuses
 * 
 * Algorithms/Techniques:
 * - Mathematical optimization and case analysis
 * - Greedy approach with precomputed bounds
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * The problem involves maximizing total discount over k purchases
 * using a bonus system where:
 * - A customer can either take a discount equal to current bonuses
 * - Or accumulate additional bonuses equal to the last digit of current bonuses
 * 
 * The solution analyzes the last digit of current bonuses (s % 10) and
 * determines optimal strategy based on patterns and mathematical bounds.
 */

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <random>
#include <iterator>
#include <string>
#include <type_traits>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
const int MOD = 1e9 + 7;
const ll INF = 1e18;
#define ff first
#define ss second
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define setbits(x) __builtin_popcountll(x)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sum(x) (accumulate((x).begin(), (x).end(), 0ll))
#define mine(x) (*min_element((x).begin(), (x).end()))
#define maxe(x) (*max_element((x).begin(), (x).end()))
inline void fastio() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '{';
  string sep;
  for (const T &x : v)
    os << sep << x, sep = ", ";
  return os << '}';
}

void solve(int tc) {
  ll s, k;
  cin >> s >> k;
  if (s % 10 == 0) {
    // If last digit is 0, no accumulation possible, just take discount
    cout << s * k << '\n';
    return;
  }
  if (s % 10 == 5) {
    // If last digit is 5, compute optimal cases
    cout << max(s * k, (s + 5) * (k - 1)) << '\n';
    return;
  }
  // Lambda function to compute total discount for a given accumulation
  auto func = [&](ll x) -> ll { return (k - 4 * x) * (s + 20 * x); };
  ll mx = s * k; // Initialize maximum with direct discount
  if ((s % 10) & 1) {
    // If last digit is odd, accumulate once and reduce k
    s += s % 10;
    --k;
  }
  // Iterate over at most 4 steps to find maximum discount
  for (int i = 0; k > 0 && i < 4; i++) {
    // Compute bounds to try
    ll a = max(0LL, (5 * k - s) / 40), b = min(a + 1, k / 4);
    mx = max({mx, func(a), func(b)});
    s += s % 10; // Accumulate bonuses
    --k; // Reduce purchase count
  }
  cout << mx << '\n';
}
int main() {
  fastio();
  cout << setprecision(15) << fixed;
  int tc = 1;
  cin >> tc;
  for (int i = 1; i <= tc; i++) {
    solve(i);
  }

  return 0;
}


// https://github.com/VaHiX/CodeForces/