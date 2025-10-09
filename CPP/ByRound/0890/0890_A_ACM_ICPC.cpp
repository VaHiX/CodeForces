/*
 * Problem URL : https://codeforces.com/contest/890/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int i, j, k, a[10], sum = 0, s;
  for (i = 1; i <= 6; i++) {
    cin >> a[i];
    sum += a[i];
  }
  for (i = 1; i <= 4; i++)
    for (j = i + 1; j <= 5; j++)
      for (k = j + 1; k <= 6; k++) {
        s = a[i] + a[j] + a[k];
        if (s == sum - s) {
          cout << "YES";
          exit(0);
        }
      }
  cout << "NO";
}
