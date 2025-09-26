/*
 * Problem URL : https://codeforces.com/contest/597/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
long double a, b, k;
int main() {
  cin >> k >> a >> b;
  ll x = ceil(a / k);
  ll y = floor(b / k);
  cout << y - x + 1;
}
