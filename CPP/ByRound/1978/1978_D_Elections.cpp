// Problem: CF 1978 D - Elections
// https://codeforces.com/contest/1978/problem/D

/*
Code Purpose:
This code solves the election problem where candidates can be excluded to ensure a specific candidate wins.
It computes for each candidate the minimum number of candidates to exclude so that this candidate wins.
The key idea is to simulate the voting process: when a candidate is removed, all their fans become undecided and vote for the lowest-numbered candidate with sufficient votes.

Algorithms/Techniques:
- Prefix sums for efficient calculation of cumulative votes.
- Greedy approach to determine minimum exclusion count per candidate.
- Simulation of vote distribution when candidates are removed.

Time Complexity: O(n) per test case, where n is the number of candidates.
Space Complexity: O(n) for storing prefix sums and auxiliary arrays.

*/

#include <stdint.h>
#include <iostream>

#define ll long long
#define x first
#define y second
#define pb push_back
#define all(u) begin(u), end(u)
#define watch(x) cout << '\n' << (#x) << " is " << (x) << '\n';
using namespace std;
const int N = 3e5 + 1;
int n;
ll a[N], c, pref[N], suf[N], mx, mxi;
void solve() {
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  a[1] += c;  // Add undecided voters to first candidate
  mx = a[1];  // Track maximum votes initially
  mxi = 1;    // Track index of maximum votes
  for (int i = 1; i <= n; i++) {
    pref[i] = pref[i - 1] + a[i];  // Build prefix sum of votes
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] > mx) {
      mx = a[i];
      mxi = i;
    }
  }
  if (mxi == 1) {
    cout << "0 ";  // First candidate already wins
  } else {
    cout << "1 ";  // Need to remove one candidate (candidate 1)
  }
  for (int i = 2; i <= n; i++) {
    if (i == mxi) {
      cout << "0 ";  // Candidate already wins
    } else {
      if (pref[i] >= mx) {
        cout << i - 1 << ' ';  // Need to remove previous candidates
      } else {
        cout << i << ' ';  // Need to remove current candidate
      }
    }
  }
  cout << '\n';
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/