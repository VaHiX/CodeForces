/*
 * Problem URL : https://codeforces.com/problemset/problem/2129/C2
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
  for (int i = 1; i <= n; i += 7) {
    int ll = i, rr = min(n, ll + 6);
    printf("? %d", ((1 << (rr - ll + 2)) - 1) + (rr - ll));
    int num = 1;
    for (int j = 0; j < rr - ll + 1; j++) {
      for (int k = 1; k <= num; k++)
        cout << " " << i + j;
      for (int k = 1; k <= num; k++)
        cout << " " << l;
      cout << " " << l;
      num *= 2;
    }
    cout << endl;
    int y;
    cin >> y;
    int z = rr - ll + 1;
    for (; z; z--, y >>= 1) {
      if (y & 1) {
        s += "(";
      } else
        s += ")";
    }
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