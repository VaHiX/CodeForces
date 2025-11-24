// Problem: CF 1973 D - Cat, Fox and Maximum Array Split
// https://codeforces.com/contest/1973/problem/D

/*
Purpose: Solve the interactive problem of finding the maximum value m such that an array can be split into exactly k subarrays, each having f(l,r) = m.
Algorithms/Techniques: Binary search on the answer combined with interaction queries to determine valid splits.
Time Complexity: O(n^2 * log(n)) - For each potential m value, we perform up to n queries and there are up to n possible values.
Space Complexity: O(1) - Only a constant amount of extra space is used beyond input storage.

The approach involves:
1. First finding the maximum possible value of array elements to determine search range.
2. Using binary search on the possible values of m.
3. For each m, check if it's possible to split the array into k subarrays all with value m.
4. Use the query function to determine the rightmost position for a given left position and value m.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
#define int long long
#define ll long long
#define db double
#define iter(s) for (auto &it : s)
#define loop(a, b, c) for (ll a = b; a < c; a++)
#define rloop(a, b, c) for (ll a = c - 1; a >= b; a--)
#define pb push_back
#define pf push_front
#define si size()
#define be begin()
#define en end()
#define all(v) v.be, v.en
#define le length()
#define in insert
#define er erase
#define F first
#define S second
#define get(a, b) get<b>(a)
#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define eqr equal_range
#define np next_permutation
#define nl cout << "\n"
#define P0(a) cout << a << " "
#define P1(a) cout << a << "\n"
#define P2(a, b) cout << a << " " << b << "\n"
#define P3(a, b, c) cout << a << " " << b << " " << c << "\n"
#define P4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << "\n"
#define deci(n) fixed << setprecision(n)
#define high(n) __builtin_popcountll(n)
#define parity(n) __builtin_parity(n)
#define clz(n) __builtin_clzll(n)
#define ctz(n) __builtin_ctzll(n)
#define pll pair<ll, ll>
#define vc vector<char>
#define vll vector<ll>
#define vpll vector<pll>
#define vvll vector<vll>
#define mll map<ll, ll>
#define sc set<char>
#define sll set<ll>
#define msc multiset<char>
#define msll multiset<ll>
#define M 998244353
#define PI 3.1415926535897932
#define EPS 1e-9
#define INF 1e18
ll query(ll l, ll x) {
  cout << "? " << l << " " << x << endl;
  ll ret;
  cin >> ret;
  if (ret == -1) {
    exit(0);
  }
  return ret;
}
bool check(ll m, ll k, ll n) {
  ll next = 1;
  while (k--) {
    next = query(next, m) + 1;
    if ((k && next == n + 1) || (next > n + 1)) {
      return false;
    }
  }
  if (next == n + 1) {
    return true;
  }
  return false;
}
void solve() {
  ll n, k;
  cin >> n >> k;
  ll amax = 1;
  // Find maximum element value of the array to bound search space
  rloop(i, 2, n + 1) {
    ll r = query(1, n * i);
    if (r == n) {
      amax = i;
      break;
    }
  }
  // Try all possible values of m and check if a valid split exists
  rloop(i, 1, (n / k) + 1) {
    ll m = amax * i;
    if (check(m, k, n)) {
      cout << "! " << m << endl;
      ll resp;
      cin >> resp;
      if (resp == -1) {
        exit(0);
      }
      return;
    }
  }
  cout << "! -1" << endl;
  ll resp;
  cin >> resp;
  if (resp == -1) {
    exit(0);
  }
}
int32_t main() {
  ios::sync_with_stdio(0), cin.tie(0);
  ll tc = 1;
  cin >> tc;
  while (tc--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/