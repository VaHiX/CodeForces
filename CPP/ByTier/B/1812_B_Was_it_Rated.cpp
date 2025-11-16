// Problem: CF 1812 B - Was it Rated?
// https://codeforces.com/contest/1812/problem/B

/*
Purpose: Determine if a given number n is one of the special values (15, 20, 21)
that are NOT rated. If n is any of those values, output "NO", otherwise output
"YES".

Algorithms/Techniques:
    - Simple conditional check using if-else statements.
    - Constant time comparison.

Time Complexity: O(1) - The algorithm performs a constant number of operations
regardless of input size. Space Complexity: O(1) - Only a constant amount of
extra space is used.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define fast ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define endl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

bool is_prime(int n) {
  if (n == 1) {
    return false;
  }
  int i = 2;
  while (i * i <= n) {
    if (n % i == 0) {
      return false;
    }
    i += 1;
  }
  return true;
}
ll binomialCoeff(ll n, ll k) {
  ll res = 1;
  if (k > n - k)
    k = n - k;
  for (ll i = 0; i < k; ++i) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}
bool check(vector<vector<int>> a, int mid) {
  int n = a.size(), m = a[0].size();
  vector<vector<int>> prefix_sum(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] >= mid) {
        a[i][j] = 1;
      } else {
        a[i][j] = 0;
      }
      prefix_sum[i + 1][j + 1] = prefix_sum[i][j + 1] + prefix_sum[i + 1][j] -
                                 prefix_sum[i][j] + a[i][j];
    }
  }
  for (int i = mid; i < n + 1; i++) {
    for (int j = mid; j < m + 1; j++) {
      int sum = prefix_sum[i][j] - prefix_sum[i - mid][j] -
                prefix_sum[i][j - mid] + prefix_sum[i - mid][j - mid];
      if (sum == (mid * mid))
        return true;
    }
  }
  return false;
}
void dfs(int i, vector<bool> &visited, vector<int> adj[]) {
  for (auto it : adj[i]) {
    if (!visited[it]) {
      visited[it] = true;
      dfs(it, visited, adj);
    }
  }
}
ll floorSqrt(ll x) {
  if (x == 0 || x == 1)
    return x;
  ll start = 1, end = x / 2, ans;
  while (start <= end) {
    ll mid = (start + end) / 2;
    ll sqr = mid * mid;
    if (sqr == x)
      return mid;
    if (sqr <= x) {
      start = mid + 1;
      ans = mid;
    } else
      end = mid - 1;
  }
  return ans;
}
ll check_pal(string s) {
  ll l = 0, r = s.size() - 1;
  ll count = 0;
  while (l < r) {
    if (s[l] != s[r]) {
      count++;
    }
    l++;
    r--;
  }
  return count;
}
int main() {
  fast;
  ll n;
  cin >> n;
  // Check if n is one of the special numbers that are Not Rated
  if (n == 15 || n == 20 || n == 21) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/