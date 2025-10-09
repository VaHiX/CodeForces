/*
 * Problem URL : https://codeforces.com/problemset/problem/545/A
 * Submit Date : 2025-08-21
 */

#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, s = 0;
  bool a[100] = {0};
  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0, A; j < n; ++j) {
      cin >> A;
      if (A % 2 && A != -1)
        a[i] = 1;
    }
  for (int i = 0; i < n; ++i)
    if (!a[i])
      s++;
  cout << s << '\n';
  for (int i = 0; i < n; ++i)
    if (!a[i])
      cout << i + 1 << ' ';
  return 0;
}