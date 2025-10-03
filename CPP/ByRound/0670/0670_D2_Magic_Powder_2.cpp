/*
 * Problem URL : https://codeforces.com/contest/670/problem/D2
 * Submit Date : 2025-09-04
 */

#include <iostream>
using namespace std;

int a[100001];
int b[100001];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]);
  long long l = 0, r = 2e9 + 5, m, t;
  while (l < r) {
    m = (l + r) >> 1;
    long long temp = 0;
    for (int i = 1; i <= n; i++) {
      t = a[i] * m - b[i];
      temp += 0 > t ? 0 : t;
      if (temp > k)
        break;
    }
    if (temp > k)
      r = m;
    else
      l = m + 1;
    // cout<<"r="<<r<<" l="<<l<<endl;
  }
  cout << l - 1 << endl;

  return 0;
}