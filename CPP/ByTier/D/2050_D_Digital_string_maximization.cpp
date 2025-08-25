/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int T;
string n;
int main() {
  scanf("%d", &T);
  while (T--) {
    cin >> n;
    for (int i = 1; i < n.length(); i++) {
      if (n[i] == '0')
        continue;
      int tmp = i;
      while (tmp && n[tmp] - n[tmp - 1] > 1) {
        n[tmp]--;
        swap(n[tmp], n[tmp--]);
      }
    }
    cout << n << '\n';
  }
  return 0;
}