// Problem: CF 1994 G - Minecraft
// https://codeforces.com/contest/1994/problem/G

/*
Algorithm: Dynamic Programming with Bit Manipulation
Time Complexity: O(n * k) where n is the length of array and k is the bit length
Space Complexity: O(k) for storing counts and result string

This solution uses dynamic programming to determine the bits of x such that 
the XOR of all array elements with x equals the given target s. 
For each bit position from most significant to least significant, 
we calculate how many times that bit contributes to the final sum and 
determine whether setting that bit in x would lead to a valid solution.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;
template <class T> int len(T &a) { return a.size(); }
using ll = long long;
using pii = pair<int, int>;
#define all(a) (a).begin(), (a).end()
#define ff first
#define ss second
string fileio = "";
const int MOD = 1e9 + 7;
const int inf = 1e9;
const ll infl = 1e18;
const int maxn = 1e5 + 1;
#define Tests
void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  vector<int> cnt(k);
  for (int i = 0; i < n; i++) {
    string ss;
    cin >> ss;
    for (int j = 0; j < k; j++)
      cnt[j] += ss[j] - '0';
  }
  string res = "";
  auto calc = [&](auto &calc, int i, int j) -> int {
    if (i == -1) {
      return j == 0;
    }
    int b = s[i] - '0';
    int k = cnt[i] + j;
    if (k % 2 == b) {
      if (calc(calc, i - 1, k / 2)) {
        res += '0';
        return true;
      }
    }
    k = j + n - cnt[i];
    if (k % 2 == b) {
      if (calc(calc, i - 1, k / 2)) {
        res += '1';
        return true;
      }
    }
    return false;
  };
  if (calc(calc, k - 1, 0)) {
    cout << res;
  } else
    cout << -1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int testcases = 1;
  cin >> testcases;
  while (testcases--) {
    solve();
    if (testcases)
      cout << '\n';
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/