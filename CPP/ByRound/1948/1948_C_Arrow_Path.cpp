// Problem: CF 1948 C - Arrow Path
// https://codeforces.com/contest/1948/problem/C

/*
Algorithm/Technique: Simulation with string construction and path validation
Time Complexity: O(n) where n is the length of the string (number of columns)
Space Complexity: O(n) for storing the constructed result string

This problem simulates a robot moving through a 2-row grid, where each cell
contains an arrow. The robot can move in four directions (up, down, left, right)
based on the arrow in its current cell. The key insight is to determine a valid
path from (1,1) to (2,n) by considering only the movements along the arrows and
checking for conflicts in consecutive moves.

We construct a string representing the direction of the path the robot can take:
- For even indices: use the arrow from the second row (t[i])
- For odd indices: use the arrow from the first row (s[i])

Then, we validate that no two consecutive positions in this path cause a
conflict (i.e., a < followed by another < which would block movement).
*/

#include <iostream>
#include <random>
#include <stdio.h>
#include <string>

using namespace std;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define pi pair<ll, ll>
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define alll(x) ((x).begin() + 1), (x).end()
#define clean(v) (v).resize(distance((v).begin(), unique(all(v))));
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define mod mod
#define endl '\n'
const ll mod = 998244353;
void io() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
}
template <class T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template <class T> bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
void nop() {
  cout << -1 << endl;
  return;
}
void solve() {
  int n;
  cin >> n;
  string s, t;
  cin >> s >> t;
  string res = "";
  // Construct the path string by alternating between rows based on index parity
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0)
      res += t[i]; // Use second row for even indices
    else
      res += s[i]; // Use first row for odd indices
  }
  // Validate that no two consecutive steps are both '<'
  // This would imply that the robot gets stuck
  for (int i = 1; i < n; i++) {
    if (res[i] == '<' && res[i] == res[i - 1]) {
      no;
      return;
    }
  }
  yes;
}
int main() {
  io();
  ll tt = 1;
  cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/