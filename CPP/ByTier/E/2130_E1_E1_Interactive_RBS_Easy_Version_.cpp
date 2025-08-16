/*
 * Problem URL : https://codeforces.com/problemset/problem/2130/E1
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int t, n;
void ask() {
  cin >> n;
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    printf("? %d", mid);
    for (int i = 1; i <= mid; i++) {
      printf(" %d", i);
    }
    cout << endl;
    int y;
    cin >> y;
    if (y) {
      r = mid - 1;
    } else
      l = mid + 1;
  }
  if (l == n + 1) {
    l = 1;
  }
  string s;
  for (int i = 1; i < n; i += 2) {
    printf("? 12");
    for (int j = 1; j <= 3; j++) {
      printf(" %d %d %d", i, l, l);
    }
    printf(" %d %d %d\n", i + 1, l, l);
    int y;
    cin >> y;
    if (y == 4) {
      s += "((";
    } else if (y == 3) {
      s += "()";
    } else if (y == 1) {
      s += ")(";
    } else
      s += "))";
  }
  if (n % 2 == 1) {
    printf("? 2 %d %d\n", n, l);
    int y;
    cin >> y;
    if (y)
      s += "(";
    else
      s += ")";
  }
  cout << "! " << s << endl;
  return;
}
int main() {
  cin >> t;
  while (t--) {
    ask();
  }
  return 0;
}