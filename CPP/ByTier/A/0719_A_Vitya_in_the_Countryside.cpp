/*
 * Problem URL : https://codeforces.com/contest/719/problem/A
 * Submit Date : 2025-09-02
 */



#include <bits/stdc++.h>
using namespace std;
int main() {
  int i, j, k;
  int n;
  bool f = false;

  cin >> n;

  int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];

  if (n == 1 && a[n - 1] != 15 && a[n - 1] != 0) {
    cout << "-1";
    return 0;
  }

  if (a[n - 1] > a[n - 2] && a[n - 1] != 15)
    cout << "UP";

  else if (a[n - 1] > a[n - 2] && a[n - 1] == 15)
    cout << "DOWN";

  else if (a[n - 1] < a[n - 2] && a[n - 1] != 0)
    cout << "DOWN";

  else if (a[n - 1] < a[n - 2] && a[n - 1] == 0)
    cout << "UP";

  return 0;
}
