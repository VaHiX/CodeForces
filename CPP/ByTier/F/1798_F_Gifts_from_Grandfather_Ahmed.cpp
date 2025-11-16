// Problem: CF 1798 F - Gifts from Grandfather Ahmed
// https://codeforces.com/contest/1798/problem/F

/*
Purpose: This code solves the problem of distributing n gift boxes among k classes such that:
1. Each class receives exactly s[i] boxes
2. The total number of gifts in each class's boxes is divisible by s[i]
3. One additional box is needed to make it work, and we find the smallest valid number of gifts for that box.

Algorithm: 
- For each class, find a subset of boxes whose sum is divisible by the class size using dynamic programming
- Use DP with states (number of boxes selected, sum mod class_size)
- For the largest class, use remaining boxes after allocating for other classes
- Compute the size of missing box so that sum for largest class is divisible by its size

Time Complexity: O(n * k * sum of all boxes)
Space Complexity: O(n * k)
*/
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int c = 205;
int db, n, t[c], ert[c], pos, ut[c][c];
vector<int> ans[c];
bool kesz[c], jo[c][c];
int main() {
  ios_base::sync_with_stdio(false);
  cin >> db >> n;
  for (int i = 1; i <= db; i++) {
    cin >> ert[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> t[i];
    if (t[i] > t[pos]) {
      pos = i;
    }
  }
  for (int s = 1; s <= n; s++) {
    if (pos == s)
      continue;
    int cel = t[s];
    for (int i = 0; i <= cel; i++) {
      for (int j = 0; j <= cel; j++) {
        jo[i][j] = 0, ut[i][j] = c;
      }
    }
    jo[0][0] = 1;
    ut[0][0] = 0;
    for (int cnt = 0; cnt < cel; cnt++) {
      for (int mar = 0; mar < cel; mar++) {
        if (!jo[cnt][mar])
          continue;
        for (int kov = ut[cnt][mar] + 1; kov <= db; kov++) {
          if (kesz[kov])
            continue;
          int kovmar = (mar + ert[kov]) % cel;
          jo[cnt + 1][kovmar] = 1;
          ut[cnt + 1][kovmar] = min(ut[cnt + 1][kovmar], kov);
        }
      }
    }
    if (!jo[cel][0]) {
      cout << "baj\n";
      exit(0);
    }
    int mar = 0;
    for (int i = cel; i >= 1; i--) {
      int ki = ut[i][mar];
      kesz[ki] = 1;
      int val = ert[ki];
      ans[s].push_back(val);
      mar = ((mar - val) % cel + cel) % cel;
    }
  }
  int sum = 0;
  for (int i = 1; i <= db; i++) {
    if (!kesz[i]) {
      ans[pos].push_back(ert[i]);
      sum += ert[i];
    }
  }
  int ut = 69;
  while ((sum + ut) % t[pos])
    ut++;
  ans[pos].push_back(ut);
  cout << ut << "\n";
  for (int i = 1; i <= n; i++) {
    for (auto x : ans[i]) {
      cout << x << " ";
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/