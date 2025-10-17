/*
 * Problem URL : https://codeforces.com/contest/1071/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int a, b;
  cin >> a >> b;

  int n = 0, k = 1;
  while (a > 0) {
    a -= k++;
    ++n;
  }
  if (a != 0) {
    --n;
    a = -a;
  }

  cout << n << '\n';
  for (int i = 1; i < k; i++)
    if (i != a)
      cout << i << ' ';
  cout << '\n';

  n = 0;
  int tmp = k;
  if (b < a) {
    cout << "0\n";
    return 0;
  }

  if (a != 0) {
    b -= a;
    ++n;
  }
  while (b > 0) {
    b -= k;
    ++k;
    ++n;
  }
  if (b != 0) {
    --k;
    --n;
  }

  cout << n << '\n';
  if (a != 0)
    cout << a << ' ';
  for (int i = tmp; i < k; i++)
    cout << i << ' ';
  cout << '\n';
}