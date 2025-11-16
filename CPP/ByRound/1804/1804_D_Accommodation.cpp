// Problem: CF 1804 D - Accommodation
// https://codeforces.com/contest/1804/problem/D

/*
Purpose: This code solves the problem of finding the minimum and maximum number of occupied apartments in a building based on a binary representation of windows (bright = '1', dark = '0'). Each floor has a specific number of one-bedroom and two-bedroom apartments that must be accounted for.

Algorithms/Techniques:
- Greedy approach to assign windows to apartments
- For maximum: try to pack as few two-bedroom apartments as possible
- For minimum: pack as many two-bedroom apartments as possible

Time Complexity: O(n * m) where n is number of floors and m is number of windows per floor
Space Complexity: O(m) for storing the string and auxiliary variables
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
const long long MOD = 998244353;
const int IINF = 2e9 + 5;
const long long LLINF = (long long)(9e18) + 5;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using pll = pair<long long, long long>;

void solve() {
  int n, m;
  cin >> n >> m;
  int mi = 0, ma = 0;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int cnt = 0;
    for (int j = 0; j < m; j++) {
      if (s[j] == '1') {
        cnt++;
      }
    }
    // For maximum occupied apartments
    if (cnt <= m / 2) {
      ma += cnt;
    } else {
      vector<bool> used(m);
      int curMa = m / 2 + m / 4; // Maximum possible apartments for this floor
      int cur = 0;
      while (cur < m) {
        if (s[cur] == '0') {
          // Skip dark windows and try to pair with next bright one
          if (cur > 0 && s[cur - 1] == '1' && used[cur - 1] == false) {
            cur++;
            continue;
          } else if (cur < m - 1 && s[cur + 1] == '1') {
            used[cur + 1] = true;
            cur++;
            continue;
          } else {
            // If we cannot pair with a neighboring bright window, then reduce count
            curMa--;
            cur = cur + 2;
            continue;
          }
        }
        cur++;
      }
      // Update maximum count of occupied apartments
      ma += min(cnt, curMa);
    }

    // Compute minimum occupied apartments
    int twoBedroom = 0;
    for (int j = 0; j < m - 1; j++) {
      if (s[j] == '1' && s[j + 1] == '1') {
        twoBedroom++;
        j++; // Increment again to skip the next window since we've used it
      }
    }
    // Limit max number of two-bedroom apartments
    twoBedroom = min(twoBedroom, m / 4);
    // Add the minimum number of occupied apartments
    mi += twoBedroom + (cnt - twoBedroom * 2);
  }
  cout << mi << ' ' << ma;
}

int main(int argc, char *argv[]) {
  cout.precision(17);
  if (argc > 1)
    freopen(argv[1], "r", stdin);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/