/*
 * Problem URL : https://codeforces.com/contest/2137/problem/C
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

int t;
ll a, b;

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%lld %lld", &a, &b);
    if (a & 1 && b & 1)
      printf("%lld\n", a * b + 1ll);
    else if (a * b % 4 || b & 1)
      puts("-1");
    else
      printf("%lld\n", a * b / 2 + 2);
  }
  return 0;
}
