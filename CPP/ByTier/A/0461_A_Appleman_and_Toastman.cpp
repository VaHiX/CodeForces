/*
 * Problem URL : https://codeforces.com/contest/461/problem/A
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
long long int n, p, r, f, s = 0, M[300002], c;
int main() {
  cin >> n;
  for (p = 0; p < n; p++)
    scanf("%lld", &M[p]);
  sort(M, M + n);
  for (p = 0; p < n; p++)
    c += M[p] * (p + 2);
  printf("%lld\n", c - M[n - 1]);
}
