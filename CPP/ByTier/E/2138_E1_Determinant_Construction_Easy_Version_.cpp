/*
 * Problem URL : https://codeforces.com/contest/2138/problem/E1
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 998244353;

int tc;
int x;
double phi = ((double)1 + sqrt(5)) / (double)2;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // cout << phi << "\n";
  cin >> tc;
  while (tc--) {
    cin >> x;

    if (x == 0) {
      cout << "1\n0\n";
      continue;
    }

    if (x == 1) {
      cout << "1\n1\n";
      continue;
    }

    // recurrence
    // dk = ck-1 * dk-1 + dk-2
    ll a = x, b = round((double)a / phi);
    if (b <= 0)
      b = 1;
    // cout << b << "\n";
    vector<int> c(90, 0);
    int steps = 0;
    while (true) {
      ll tmp_a = a;
      ll tmp_b = b;
      if (__gcd(a, b) == 1) {
        steps = 0;
        for (int i = 89; i >= 0; i--) {
          if (b == 0 && abs(a) == 1) {
            break;
          }

          steps++;
          // dk-2 = dk - ck-1 * dk-1
          ll x = abs(a);
          ll y = abs(a - b);
          ll z = abs(a + b);
          ll tmp;

          if (x <= y && x <= z) {
            c[i] = 0;
            tmp = a;
          } else if (y <= z) {
            c[i] = 1;
            tmp = a - b;
          } else {
            c[i] = -1;
            tmp = a + b;
          }
          a = b;
          b = tmp;
        }
        if (steps <= 80)
          break;
      }
      a = tmp_a;
      b = tmp_b;
      b--;
    }

    vector<vector<int>> ans(steps, vector<int>(steps, 0));
    int tmp = 0;
    for (int i = 0; i < steps; i++) {
      for (int j = 0; j < steps; j++) {
        if (i == j)
          ans[i][j] = c[90 + i - steps];
        else if (i == j - 1)
          ans[i][j] = 1;
        else if (i == j + 1)
          ans[i][j] = -1;
      }
    }

    if (a == -1) {
      swap(ans[0], ans[1]);
    }

    cout << steps << "\n";
    for (int i = 0; i < steps; i++) {
      for (int j = 0; j < steps; j++) {
        cout << ans[i][j] << " ";
      }
      cout << "\n";
    }
  }
  return 0;
}