/*
 * Problem URL : https://codeforces.com/contest/1036/problem/D
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
typedef long long l;
using namespace std;
#define z() for (l i = 0, r; i < n; i++)
#define k(i) scanf("%lld", &i)
l n, s, q, a;
map<l, l> x;
int main() {
  k(n);
  z() {
    k(r);
    x[s += r]++;
  }
  k(n);
  z() {
    k(r);
    a += x[q += r];
  }
  cout << ((q != s) ? -1 : a);
}