/*
 * Problem URL : https://codeforces.com/contest/993/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int x1[4], x2[4], y1[4], y2[4];
  for (int i = 0; i < 4; i++)
    cin >> x1[i] >> y1[i];
  for (int i = 0; i < 4; i++)
    cin >> x2[i] >> y2[i];
  sort(x1, x1 + 4);
  sort(y1, y1 + 4);
  sort(x2, x2 + 4);
  sort(y2, y2 + 4);
  for (int i = x1[0]; i <= x1[3]; i++)
    for (int j = y1[0]; j <= y1[3]; j++)
      if (i + j <= x2[3] + y2[2])
        if (i + j >= x2[0] + y2[2])
          if (i - j >= -y2[3] + x2[2])
            if (i - j <= x2[3] - y2[2]) {
              cout << "YES";
              return 0;
            }
  cout << "NO";
  return 0;
}