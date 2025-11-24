// Problem: CF 1839 C - Insert Zero and Invert Prefix
// https://codeforces.com/contest/1839/problem/C

/*
Purpose: This code solves the problem of determining whether a sequence of
operations can transform an empty binary sequence 'b' into a given binary
sequence 'a'. The operations involve inserting a zero at a certain position and
inverting the prefix up to that position.

Algorithms/Techniques:
- Greedy approach with pattern recognition
- Grouping consecutive identical elements in 'a'
- Reverse reconstruction of operations based on grouped patterns

Time Complexity: O(n), where n is the length of the input sequence 'a'.
                 We process the array once to group elements and once to
generate the answer.

Space Complexity: O(n), for storing the grouped elements and the result
operations.
*/

#include <algorithm>
#include <iostream>
#include <math.h>
#include <random>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;
#define cio                                                                    \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0)
#define cases                                                                  \
  int _;                                                                       \
  cin >> _;                                                                    \
  while (_--)
#define pb push_back
#define eb emplace_back
#define space << " " <<
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define Unique(v) v.erase(unique(all(v)), v.end())
#define mset(x) memset(x, 0, sizeof(x))
#define sflush fflush(stdout)
#define cflush cout.flush()
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define lyes cout << "Yes\n"
#define lno cout << "No\n"
#define nl cout << "\n";
#define binary(len, num) bitset<len>(num)
#define vt vector
#define ar array
#define Mat vt<vt<int>>
#define uid uniform_int_distribution<int>
template <typename T> istream &operator>>(istream &in, vector<T> &a) {
  for (auto &x : a)
    in >> x;
  return in;
};
template <typename T> ostream &operator<<(ostream &out, vector<T> &a) {
  for (auto &x : a)
    out << x << ' ';
  return out;
};
int read() {
  int w = 1, c, ret;
  while ((c = getchar()) > '9' || c < '0') {
    w = (c == '-' ? -1 : 1);
  }
  ret = c - '0';
  while ((c = getchar()) >= '0' && c <= '9') {
    ret = ret * 10 + c - '0';
  }
  return ret * w;
}
int rd() {
  int in;
  cin >> in;
  return in;
}
void write(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) {
    write(x / 10);
  }
  putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5, MAXM = 2e5 + 5, INF = 1e9 + 5, MOD = 1e9 + 7;
const ll LINF = 1e18 + 5;
const ld ep = 1e-8, Pi = acos(-1.0);
int n, m, k, x;
int a[MAXN];
string s;
void clear() {}
int main() {
  cio;
  cases {
    cin >> n;
    vt<pii> rec; // Store pairs of (value, count) for consecutive elements
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      if (i == 1)
        ++cnt;
      else {
        if (a[i] == a[i - 1])
          ++cnt;
        else {
          rec.eb(a[i - 1], cnt); // Record the group
          cnt = 1;
        }
      }
    }
    rec.eb(a[n], cnt); // Record last group
    if (a[n]) {
      no; // If last element is 1, it's impossible to reach a[n] = 1
      continue;
    }
    yes;
    m = (int)rec.size();
    vt<int> ans; // Stores operations to perform

    // Process groups from the end to the beginning, alternating pattern
    for (int i = m - 2; i >= 0; i -= 2) {
      // For each pair of adjacent groups, add operations for the first one
      for (int j = 1; j <= rec[i].S + rec[i + 1].S - 1; ++j) {
        ans.pb(0); // Operation: insert at position 0
      }
      ans.pb(rec[i].S); // Operation: insert at position rec[i].S
    }

    // Handle the first group if it is 0
    if (rec[0].F == 0) {
      for (int i = 1; i <= rec[0].S; ++i) {
        ans.pb(0); // Operation: insert at position 0
      }
    }

    cout << ans << "\n";
    clear();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/