/*
 * Problem URL : https://codeforces.com/problemset/problem/1713/D
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
#define _ ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
using namespace std;
int t, n, ar[1 << 17], x, a, b, c, d;

void ask(int a, int b) {
  cout << "? " << a << " " << b << "\n\n";
  cout.flush();
  cin >> x;
}

int main() {
  _ cin >> t;
  while (t--) {
    cin >> n;
    n = (1 << n);
    for (int i = 0; i < n; i++)
      ar[i] = i + 1;
    while (n >= 4) {
      for (int i = 0; i < n; i += 4) {
        a = ar[i], b = ar[i + 1], c = ar[i + 2], d = ar[i + 3];
        ask(a, c);
        if (x == 0)
          ar[i / 2] = b, ar[i / 2 + 1] = d;
        if (x == 1)
          ar[i / 2] = a, ar[i / 2 + 1] = d;
        if (x == 2)
          ar[i / 2] = c, ar[i / 2 + 1] = b;
      }
      n /= 2;
    }
    ask(ar[0], ar[1]);
    cout << "! " << ar[x - 1] << "\n";
    cout.flush(); /// !!!!!
  }
  return 0;
}